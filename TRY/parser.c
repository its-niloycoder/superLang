// there are 3 possible thing can exist
// other then simple tokens
// multi line comment
// single line comment
// strings with myltiple definationstyle like " ' ` formated and others


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_TOKEN_LEN 1024

typedef enum {
    TOKEN_STRING,
    TOKEN_NUMBER,
    TOKEN_IDENTIFIER,
    TOKEN_OPERATOR,
    TOKEN_COMMENT,
    TOKEN_ERROR,
    TOKEN_EOF
} TokenType;

typedef struct {
    TokenType type;
    char value[MAX_TOKEN_LEN];
} Token;

// Function prototypes
Token get_next_token(FILE *file);
void print_token(const Token *token);
int is_operator(char c);

// Lexer function
Token get_next_token(FILE *file) {
    static int c = ' ';
    Token token;
    token.value[0] = '\0';

    // Skip whitespaces
    while (isspace(c)) c = fgetc(file);

    // End of file
    if (c == EOF) {
        token.type = TOKEN_EOF;
        return token;
    }

    // String literals with encoding markers
    if (c == 'u' || c == 'b' || c == 'r') {
        char prefix = c; // Encoding marker
        c = fgetc(file);

        if (c == '"') { // Start of a string
            char quote = c;
            int i = 0;
            token.type = TOKEN_STRING;

            // Store prefix
            token.value[i++] = prefix;

            c = fgetc(file); // Consume the opening quote
            while (c != quote && c != EOF) {
                if (prefix != 'r' && c == '\\') { // Handle escape sequences unless raw string
                    c = fgetc(file);
                    if (c == 'n') token.value[i++] = '\n';
                    else if (c == 't') token.value[i++] = '\t';
                    else if (c == 'u') {
                        // Unicode escape: \uXXXX
                        char unicode[5] = {0};
                        for (int j = 0; j < 4; j++) unicode[j] = fgetc(file);
                        strcat(token.value, unicode);
                        i += 4;
                    } else {
                        token.value[i++] = c;
                    }
                } else {
                    token.value[i++] = c;
                }
                c = fgetc(file);
            }
            if (c == quote) c = fgetc(file); // Consume closing quote
            token.value[i] = '\0';
            return token;
        }
    }

    // Numeric constants
    if (isdigit(c) || (c == '0' && (c = fgetc(file)) && (c == 'x' || c == 'b' || c == 'o'))) {
        int i = 0;
        token.type = TOKEN_NUMBER;
        if (c == 'x' || c == 'b' || c == 'o') {
            token.value[i++] = '0';
            token.value[i++] = c;
            c = fgetc(file); // Consume base marker
        }
        while (isalnum(c) || c == '.') {
            token.value[i++] = c;
            c = fgetc(file);
        }
        token.value[i] = '\0';
        return token;
    }

    // Identifiers
    if (isalpha(c) || c == '_') {
        int i = 0;
        token.type = TOKEN_IDENTIFIER;
        while (isalnum(c) || c == '_') {
            token.value[i++] = c;
            c = fgetc(file);
        }
        token.value[i] = '\0';
        return token;
    }

    // Operators
    if (is_operator(c)) {
        token.type = TOKEN_OPERATOR;
        token.value[0] = c;
        token.value[1] = '\0';
        c = fgetc(file);
        return token;
    }

    // Unknown token
    token.type = TOKEN_ERROR;
    snprintf(token.value, MAX_TOKEN_LEN, "Unexpected character: '%c'", c);
    c = fgetc(file);
    return token;
}

// Utility to check if a character is an operator
int is_operator(char c) {
    return strchr("+-*/=<>!&|", c) != NULL;
}

// Utility to print tokens
void print_token(const Token *token) {
    const char *type_str[] = {
        "STRING", "NUMBER", "IDENTIFIER", "OPERATOR", "COMMENT", "ERROR", "EOF"
    };
    printf("Token: %-10s Value: %s\n", type_str[token->type], token->value);
}

// Main function
int main() {
    const char *filename = "test.txt";
    FILE *file = fopen(filename, "r");

    if (!file) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    Token token;
    do {
        token = get_next_token(file);
        print_token(&token);
    } while (token.type != TOKEN_EOF);

    fclose(file);
    return EXIT_SUCCESS;
}