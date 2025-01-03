/* Parser implementation */

/* For a description, see the comments at end of this file */

/* XXX To do: error recovery */

#include "pgenheaders.h"
#include "assert.h"
#include "token.h"
#include "grammar_t.h"
#include "node.h"
#include "parser.h"
#include "errcode.h"
#include "tokenizer.h"
#include "parsetok.h"

#define D(x)

/* STACK DATA TYPE */

static void s_reset (stack *);

static void
s_reset(s)
	stack *s;
{
	s->s_top = &s->s_base[MAXSTACK];
}

#define s_empty(s) ((s)->s_top == &(s)->s_base[MAXSTACK])

static int s_push (stack *, dfa *, node *);

static int
s_push(s, d, parent)
	register stack *s;
	dfa *d;
	node *parent;
{
	register stackentry *top;
	if (s->s_top == s->s_base) {
		fprintf(stderr, "s_push: parser stack overflow\n");
		return -1;
	}
	top = --s->s_top;
	top->s_dfa = d;
	top->s_parent = parent;
	top->s_state = 0;
	return 0;
}

#ifdef DEBUG

#else /* !DEBUG */

#define s_pop(s) (s)->s_top++

#endif


/* PARSER CREATION */

parser_state *
newparser(g, start)
	grammar *g;
	int start;
{
	parser_state *ps;
	
	if (!g->g_accel)
		addaccelerators(g);
	ps = NEW(parser_state, 1);
	if (ps == NULL)
		return NULL;
	ps->p_grammar = g;
	ps->p_tree = newtree(start);
	if (ps->p_tree == NULL) {
		DEL(ps);
		return NULL;
	}
	s_reset(&ps->p_stack);
	(void) s_push(&ps->p_stack, finddfa(g, start), ps->p_tree);
	return ps;
}

void
delparser(ps)
	parser_state *ps;
{
	/* NB If you want to save the parse tree,
	   you must set p_tree to NULL before calling delparser! */
	freetree(ps->p_tree);
	DEL(ps);
}


/* PARSER STACK OPERATIONS */

static int shift (stack *, int, char *, int, int);

static int
shift(s, type, str, newstate, lineno)
	register stack *s;
	int type;
	char *str;
	int newstate;
	int lineno;
{
	assert(!s_empty(s));
	if (addchild(s->s_top->s_parent, type, str, lineno) == NULL) {
		fprintf(stderr, "shift: no mem in addchild\n");
		return -1;
	}
	s->s_top->s_state = newstate;
	return 0;
}

static int push (stack *, int, dfa *, int, int);

static int
push(s, type, d, newstate, lineno)
	register stack *s;
	int type;
	dfa *d;
	int newstate;
	int lineno;
{
	register node *n;
	n = s->s_top->s_parent;
	assert(!s_empty(s));
	if (addchild(n, type, (char *)NULL, lineno) == NULL) {
		fprintf(stderr, "push: no mem in addchild\n");
		return -1;
	}
	s->s_top->s_state = newstate;
	return s_push(s, d, CHILD(n, NCH(n)-1));
}


/* PARSER PROPER */

static int classify (grammar *, int, char *);

static int
classify(g, type, str)
	grammar *g;
	register int type;
	char *str;
{
	register int n = g->g_ll.ll_nlabels;
	
	if (type == NAME) {
		register char *s = str;
		register label *l = g->g_ll.ll_label;
		register int i;
		for (i = n; i > 0; i--, l++) {
			if (l->lb_type == NAME && l->lb_str != NULL &&
					l->lb_str[0] == s[0] &&
					strcmp(l->lb_str, s) == 0) {
				D(printf("It's a keyword\n"));
				return n - i;
			}
		}
	}
	
	{
		register label *l = g->g_ll.ll_label;
		register int i;
		for (i = n; i > 0; i--, l++) {
			if (l->lb_type == type && l->lb_str == NULL) {
				D(printf("It's a token we know\n"));
				return n - i;
			}
		}
	}
	
	D(printf("Illegal token\n"));
	return -1;
}

int
addtoken(ps, type, str, lineno)
	register parser_state *ps;
	register int type;
	char *str;
	int lineno;
{
	register int ilabel;
	
	D(printf("Token %s/'%s' ... ", tok_name[type], str));
	
	/* Find out which label this token is */
	ilabel = classify(ps->p_grammar, type, str);
	if (ilabel < 0)
		return E_SYNTAX;
	
	/* Loop until the token is shifted or an error occurred */
	for (;;) {
		/* Fetch the current dfa and state */
		register dfa *d = ps->p_stack.s_top->s_dfa;
		register state *s = &d->d_state[ps->p_stack.s_top->s_state];
		
		D(printf(" DFA '%s', state %d:",
			d->d_name, ps->p_stack.s_top->s_state));
		
		/* Check accelerator */
		if (s->s_lower <= ilabel && ilabel < s->s_upper) {
			register int x = s->s_accel[ilabel - s->s_lower];
			if (x != -1) {
				if (x & (1<<7)) {
					/* Push non-terminal */
					int nt = (x >> 8) + NT_OFFSET;
					int arrow = x & ((1<<7)-1);
					dfa *d1 = finddfa(ps->p_grammar, nt);
					if (push(&ps->p_stack, nt, d1,
						arrow, lineno) < 0) {
						D(printf(" MemError: push.\n"));
						return E_NOMEM;
					}
					D(printf(" Push ...\n"));
					continue;
				}
				
				/* Shift the token */
				if (shift(&ps->p_stack, type, str,
						x, lineno) < 0) {
					D(printf(" MemError: shift.\n"));
					return E_NOMEM;
				}
				D(printf(" Shift.\n"));
				/* Pop while we are in an accept-only state */
				while (s = &d->d_state
						[ps->p_stack.s_top->s_state],
					s->s_accept && s->s_narcs == 1) {
					D(printf("  Direct pop.\n"));
					s_pop(&ps->p_stack);
					if (s_empty(&ps->p_stack)) {
						D(printf("  ACCEPT.\n"));
						return E_DONE;
					}
					d = ps->p_stack.s_top->s_dfa;
				}
				return E_OK;
			}
		}
		
		if (s->s_accept) {
			/* Pop this dfa and try again */
			s_pop(&ps->p_stack);
			D(printf(" Pop ...\n"));
			if (s_empty(&ps->p_stack)) {
				D(printf(" Error: bottom of stack.\n"));
				return E_SYNTAX;
			}
			continue;
		}
		
		/* Stuck, report syntax error */
		D(printf(" Error.\n"));
		return E_SYNTAX;
	}
}

/*

Description
-----------

The parser's interface is different than usual: the function addtoken()
must be called for each token in the input.  This makes it possible to
turn it into an incremental parsing system later.  The parsing system
constructs a parse tree as it goes.

A parsing rule is represented as a Deterministic Finite-state Automaton
(DFA).  A node in a DFA represents a state of the parser; an arc represents
a transition.  Transitions are either labeled with terminal symbols or
with non-terminals.  When the parser decides to follow an arc labeled
with a non-terminal, it is invoked recursively with the DFA representing
the parsing rule for that as its initial state; when that DFA accepts,
the parser that invoked it continues.  The parse tree constructed by the
recursively called parser is inserted as a child in the current parse tree.

The DFA's can be constructed automatically from a more conventional
language description.  An extended LL(1) grammar (ELL(1)) is suitable.
Certain restrictions make the parser's life easier: rules that can produce
the empty string should be outlawed (there are other ways to put loops
or optional parts in the language).  To avoid the need to construct
FIRST sets, we can require that all but the last alternative of a rule
(really: arc going out of a DFA's state) must begin with a terminal
symbol.

As an example, consider this grammar:

expr:	term (OP term)*
term:	CONSTANT | '(' expr ')'

The DFA corresponding to the rule for expr is:

------->.---term-->.------->
	^          |
	|          |
	\----OP----/

The parse tree generated for the input a+b is:

(expr: (term: (NAME: a)), (OP: +), (term: (NAME: b)))

*/



/* Parser-tokenizer link implementation */



/* Forward */
static int parsetok (struct tok_state *, grammar *, int, node **);


/* Parse input coming from a string.  Return error code, print some errors. */

int
parsestring(s, g, start, n_ret)
	char *s;
	grammar *g;
	int start;
	node **n_ret;
{
	struct tok_state *tok = tok_setups(s);
	int ret;
	
	if (tok == NULL) {
		fprintf(stderr, "no mem for tok_setups\n");
		return E_NOMEM;
	}
	ret = parsetok(tok, g, start, n_ret);
	if (ret == E_TOKEN || ret == E_SYNTAX) {
		fprintf(stderr, "String parsing error at line %d\n",
			tok->lineno);
	}
	tok_free(tok);
	return ret;
}


/* Parse input coming from a file.  Return error code, print some errors. */

int
parsefile(fp, filename, g, start, ps1, ps2, n_ret)
	FILE *fp;
	char *filename;
	grammar *g;
	int start;
	char *ps1, *ps2;
	node **n_ret;
{
	struct tok_state *tok = tok_setupf(fp, ps1, ps2);
	int ret;
	
	if (tok == NULL) {
		fprintf(stderr, "no mem for tok_setupf\n");
		return E_NOMEM;
	}
	ret = parsetok(tok, g, start, n_ret);
	if (ret == E_TOKEN || ret == E_SYNTAX) {
		char *p;
		fprintf(stderr, "Parsing error: file %s, line %d:\n",
						filename, tok->lineno);
		*tok->inp = '\0';
		if (tok->inp > tok->buf && tok->inp[-1] == '\n')
			tok->inp[-1] = '\0';
		fprintf(stderr, "%s\n", tok->buf);
		for (p = tok->buf; p < tok->cur; p++) {
			if (*p == '\t')
				putc('\t', stderr);
			else
				putc(' ', stderr);
		}
		fprintf(stderr, "^\n");
	}
	tok_free(tok);
	return ret;
}


/* Parse input coming from the given tokenizer structure.
   Return error code. */

static int
parsetok(tok, g, start, n_ret)
	struct tok_state *tok;
	grammar *g;
	int start;
	node **n_ret;
{
	parser_state *ps;
	int ret;
	
	if ((ps = newparser(g, start)) == NULL) {
		fprintf(stderr, "no mem for new parser\n");
		return E_NOMEM;
	}
	
	for (;;) {
		char *a, *b;
		int type;
		int len;
		char *str;
		
		type = tok_get(tok, &a, &b);
		if (type == ERRORTOKEN) {
			ret = tok->done;
			break;
		}
		len = b - a;
		str = NEW(char, len + 1);
		if (str == NULL) {
			fprintf(stderr, "no mem for next token\n");
			ret = E_NOMEM;
			break;
		}
		strncpy(str, a, len);
		str[len] = '\0';
		ret = addtoken(ps, (int)type, str, tok->lineno);
		if (ret != E_OK) {
			if (ret == E_DONE) {
				*n_ret = ps->p_tree;
				ps->p_tree = NULL;
			}
			else if (tok->lineno <= 1 && tok->done == E_EOF)
				ret = E_EOF;
			break;
		}
	}
	
	delparser(ps);
	return ret;
}
