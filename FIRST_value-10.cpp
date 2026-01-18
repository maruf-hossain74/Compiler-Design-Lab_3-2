#include <stdio.h>
#include <ctype.h>
#include <string.h>

void addToResult(char result[], char val) {
    int i;
    for (i = 0; result[i] != '\0'; i++) {
        if (result[i] == val)
            return;
    }
    result[i] = val;
    result[i + 1] = '\0';
}

void first(char result[], char symbol) {
    if (!isupper(symbol)) {
        addToResult(result, symbol);
        return;
    }

    switch (symbol) {
        case 'A':
            addToResult(result, 'a');
            addToResult(result, 'e'); // e represents ε
            break;

        case 'B':
            addToResult(result, 'b');
            addToResult(result, 'e');
            break;

        case 'C':
            addToResult(result, 'c');
            break;

        case 'S': {
            char temp[10] = "";
            first(temp, 'A');

            for (int i = 0; temp[i] != '\0'; i++) {
                if (temp[i] != 'e')
                    addToResult(result, temp[i]);
            }

            if (strchr(temp, 'e')) {
                first(temp, 'B');
                for (int i = 0; temp[i] != '\0'; i++) {
                    if (temp[i] != 'e')
                        addToResult(result, temp[i]);
                }
            }

            if (strchr(temp, 'e')) {
                first(temp, 'C');
                for (int i = 0; temp[i] != '\0'; i++)
                    addToResult(result, temp[i]);
            }
            break;
        }
    }
}

int main() {
    char result[10] = "";

    first(result, 'S');
    printf("FIRST(S) = { ");
    for (int i = 0; result[i] != '\0'; i++)
        printf("%c ", result[i]);
    printf("}\n");

    return 0;
}
