import ply.lex as lex
import ply.yacc as yacc


# --- 1. Lexer ---

# Tokens
tokens = (
    'NUMBER', 'IDENTIFIER', 'TYPE', 'EQUALS', 'COLON', 'LPAREN', 'RPAREN', 'SEMICOLON', 'FUNC_CALL',
)

# Token definitions
t_TYPE = r'i|str'  # 'i' for int, 'str' for string
t_NUMBER = r'\d+'  # Integer numbers
t_IDENTIFIER = r'[a-zA-Z_][a-zA-Z0-9_]*'  # Variable names
t_EQUALS = r'='
t_COLON = r':'  # Define token for colon
t_LPAREN = r'\('
t_RPAREN = r'\)'
t_SEMICOLON = r';'
t_FUNC_CALL = r'puts|intTOStr'  # Function names (e.g., puts, intTOStr)

# Ignore spaces and tabs
t_ignore = ' \t'

# Handle newlines
def t_newline(t):
    r'\n+'
    t.lexer.lineno += len(t.value)

# Handle errors in input
def t_error(t):
    print(f"Illegal character '{t.value[0]}'")
    t.lexer.skip(1)

# Build the lexer
lexer = lex.lex()

# --- 2. Parser ---

# Variable storage
variables = {}

# Grammar rules

# Start rule
def p_program(p):
    '''program : declaration statement'''
    pass

# Variable declaration
def p_declaration(p):
    '''declaration : TYPE COLON NUMBER IDENTIFIER EQUALS NUMBER SEMICOLON'''
    var_type = p[1]  # 'i' or 'str'
    size = p[3]  # Variable size (not currently used in the execution)
    var_name = p[4]  # Variable name
    value = p[6]  # Variable value

    if var_type == 'i':
        variables[var_name] = int(value)
    elif var_type == 'str':
        variables[var_name] = str(value)

    print(f"Declared {var_type} variable '{var_name}' with value {value}")

# Function call (puts or intTOStr)
def p_statement(p):
    '''statement : FUNC_CALL LPAREN FUNC_CALL LPAREN IDENTIFIER RPAREN RPAREN SEMICOLON'''
    func_name = p[1]
    inner_func = p[3]
    var_name = p[5]

    # Handling function calls
    if inner_func == "intTOStr":
        result = str(variables.get(var_name, "undefined"))
        print(f"Function {func_name}({inner_func}({var_name})) => {result}")
    elif func_name == "puts":
        print(f"Function {func_name}({inner_func}) with value: {variables.get(var_name, 'undefined')}")

# Error rule
def p_error(p):
    print(f"Syntax error at '{p.value}'")

# --- 3. Execution ---

# Build the parser
parser = yacc.yacc()

# Example input code
input_data = '''
i:32 age = 18;
str:256 name = 18;
puts(intTOStr(age));
'''

# Tokenize and parse
lexer.input(input_data)

# Parse the input and execute
parser.parse(input_data)
