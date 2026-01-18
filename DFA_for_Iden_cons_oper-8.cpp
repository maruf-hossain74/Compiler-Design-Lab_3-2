#include <stdio.h>
#include <ctype.h>
#include <string.h>

int isIdentifier(char str[]) {
    int i = 0;

    if (isalpha(str[i]) || str[i] == '_') {
        i++;
        while (str[i] != '\0') {
            if (isalnum(str[i]) || str[i] == '_')
                i++;
            else
                return 0;
        }
        return 1;
    }
    return 0;
}

int isConstant(char str[]) {
    int i = 0, dot = 0;

    while (str[i] != '\0') {
        if (isdigit(str[i])) {
            i++;
        }
        else if (str[i] == '.' && dot == 0) {
            dot = 1;
            i++;
        }
        else {
            return 0;
        }
    }
    return 1;
}

int isOperator(char str[]) {
    char *operators[] = {
        "+", "-", "*", "/", "%", "=", "<", ">", 
        "==", "<=", ">=", "!=", "++", "--"
    };

    int n = sizeof(operators) / sizeof(operators[0]);
    for (int i = 0; i < n; i++) {
        if (strcmp(str, operators[i]) == 0)
            return 1;
    }
    return 0;
}

int main() {
    char input[50];

    printf("Enter a token: ");
    scanf("%s", input);

    if (isIdentifier(input))
        printf("Valid Identifier\n");
    else if (isConstant(input))
        printf("Valid Constant\n");
    else if (isOperator(input))
        printf("Valid Operator\n");
    else
        printf("Invalid Token\n");

    return 0;
}
