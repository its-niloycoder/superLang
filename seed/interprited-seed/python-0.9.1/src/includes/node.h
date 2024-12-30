/* Parse tree node interface */

#include <stdio.h>

typedef struct _node {
	int		n_type;
	char		*n_str;
	int		n_lineno;
	int		n_nchildren;
	struct _node	*n_child;
} node;

extern node *newtree (int type);
extern node *addchild (node *n, int type, char *str, int lineno);
extern void freetree (node *n);

/* Node access functions */
#define NCH(n)		((n)->n_nchildren)
#define CHILD(n, i)	(&(n)->n_child[i])
#define TYPE(n)		((n)->n_type)
#define STR(n)		((n)->n_str)

/* Assert that the type of a node is what we expect */
#ifndef DEBUG
#define REQ(n, type) { /*pass*/ ; }
#endif

extern void listtree (node *);
extern void listnode (FILE *, node *);
