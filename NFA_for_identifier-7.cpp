#include <stdio.h>
#include <ctype.h>
#include <string.h>

/* List of keywords */
const char *keywords[] = {
    "int", "float", "double", "char", "if", "else", "for", "while",
    "do", "break", "continue", "return", "void", "static", "struct",
    "switch", "case", "default", "long", "short", "signed", "unsigned",
    "sizeof", "typedef", "union", "const", "enum", "extern", "register",
    "volatile", "goto"
};

int isKeyword(char *str) {
    int n = sizeof(keywords) / sizeof(keywords[0]);
    for (int i = 0; i < n; i++) {
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int main() {
    char input[100];
    int i = 0;

    printf("Enter a string: ");
    scanf("%s", input);

    /* Check keyword */
    if (isKeyword(input)) {
        printf("Invalid Identifier (Keyword)\n");
        return 0;
    }

    /* NFA start state */
    if (isalpha(input[i]) || input[i] == '_') {
        i++;  // move to accepting state

        while (input[i] != '\0') {
            if (isalnum(input[i]) || input[i] == '_') {
                i++;
            } else {
                printf("Invalid Identifier\n");
                return 0;
            }
        }

        printf("Valid Identifier\n");
    } else {
        printf("Invalid Identifier\n");
    }

    return 0;
}
