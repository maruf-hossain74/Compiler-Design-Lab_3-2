#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 20

int n; // number of productions
char prod[MAX][50]; // productions
char lhs[MAX]; // left-hand side
char rhs[MAX][10][50]; // right-hand side alternatives
int altCount[MAX]; // number of alternatives per production

// Function to find production index of a non-terminal
int findLHS(char nt) {
    for (int i = 0; i < n; i++)
        if (lhs[i] == nt) return i;
    return -1;
}

// Perform leftmost derivation
void leftmostDerivation(char start[]) {
    char current[100];
    strcpy(current, start);
    printf("Step: %s\n", current);

    while (1) {
        int changed = 0;
        for (int i = 0; i < strlen(current); i++) {
            char c = current[i];
            if (isupper(c)) { // leftmost non-terminal
                int idx = findLHS(c);
                if (idx == -1) {
                    printf("Error: Non-terminal %c not found.\n", c);
                    return;
                }

                // For simplicity, choose the **first production**
                char newStr[100] = "";
                strncpy(newStr, current, i); // copy before non-terminal
                newStr[i] = '\0';
                strcat(newStr, rhs[idx][0]); // replace non-terminal with first alternative
                strcat(newStr, current+i+1); // append remaining
                strcpy(current, newStr);
                printf("Step: %s\n", current);
                changed = 1;
                break; // only replace **leftmost** non-terminal
            }
        }
        if (!changed) break; // only terminals left
    }
}

int main() {
    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (format A->α|β):\n");
    for (int i = 0; i < n; i++) {
        scanf("%s", prod[i]);
        lhs[i] = prod[i][0];

        char *ptr = strchr(prod[i], '>');
        ptr++; // skip '>'
        char *token = strtok(ptr, "|");
        int j = 0;
        while (token) {
            strcpy(rhs[i][j++], token);
            token = strtok(NULL, "|");
        }
        altCount[i] = j;
    }

    char start[10];
    printf("Enter start symbol: ");
    scanf("%s", start);

    printf("\nLeftmost derivation:\n");
    leftmostDerivation(start);

    return 0;
}
