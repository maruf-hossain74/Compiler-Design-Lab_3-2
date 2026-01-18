#include <stdio.h>
#include <ctype.h>
#include <string.h>

int isKeyword(char str[]) {
    char keywords[6][10] = {"int", "float", "if", "else", "while", "return"};
    for (int i = 0; i < 6; i++) {
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int main() {
    char ch, buffer[50];
    int i = 0;

    printf("Enter the source code (end with $):\n");

    while ((ch = getchar()) != '$') {

        /* Ignore spaces, tabs, newlines */
        if (ch == ' ' || ch == '\t' || ch == '\n')
            continue;

        /* Ignore single-line comments */
        if (ch == '/') {
            char next = getchar();
            if (next == '/') {
                while (getchar() != '\n'); // skip comment
                continue;
            } else {
                printf("Operator: /\n");
                ungetc(next, stdin);
                continue;
            }
        }

        /* Identifier or Keyword */
        if (isalpha(ch) || ch == '_') {
            buffer[i++] = ch;
            while (isalnum(ch = getchar()) || ch == '_')
                buffer[i++] = ch;

            buffer[i] = '\0';
            i = 0;
            ungetc(ch, stdin);

            if (isKeyword(buffer))
                printf("Keyword: %s\n", buffer);
            else
                printf("Identifier: %s\n", buffer);
        }

        /* Constant */
        else if (isdigit(ch)) {
            buffer[i++] = ch;
            while (isdigit(ch = getchar()))
                buffer[i++] = ch;

            buffer[i] = '\0';
            i = 0;
            ungetc(ch, stdin);

            printf("Constant: %s\n", buffer);
        }

        /* Operator */
        else {
            printf("Operator: %c\n", ch);
        }
    }

    return 0;
}
