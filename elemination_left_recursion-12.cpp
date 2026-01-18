#include <stdio.h>
#include <string.h>

int main() {
    int n;
    printf("Enter number of productions: ");
    scanf("%d", &n);

    char prod[20][50];
    char lhs[20];
    char rhs[20][10][50]; // rhs[i][j] = j-th alternative of i-th production
    int altCount[20] = {0};

    printf("Enter productions in format A->α|β:\n");
    for (int i = 0; i < n; i++) {
        scanf("%s", prod[i]);
        lhs[i] = prod[i][0]; // LHS

        char *ptr = strchr(prod[i], '>');
        ptr++; // move past '>'
        char *token = strtok(ptr, "|");
        int j = 0;
        while (token) {
            strcpy(rhs[i][j++], token);
            token = strtok(NULL, "|");
        }
        altCount[i] = j;
    }

    printf("\nAfter eliminating left recursion:\n");

    for (int i = 0; i < n; i++) {
        char direct[10][50];
        char indirect[10][50];
        int dCount = 0, indCount = 0;

        // Split direct (starts with lhs) and indirect alternatives
        for (int j = 0; j < altCount[i]; j++) {
            if (rhs[i][j][0] == lhs[i]) {
                strcpy(direct[dCount++], rhs[i][j]+1); // remove lhs from start
            } else {
                strcpy(indirect[indCount++], rhs[i][j]);
            }
        }

        // No direct left recursion
        if (dCount == 0) {
            printf("%c->", lhs[i]);
            for (int j = 0; j < altCount[i]; j++) {
                printf("%s", rhs[i][j]);
                if (j != altCount[i]-1) printf("|");
            }
            printf("\n");
        } else {
            // Create new non-terminal
            char newNT = lhs[i] + '\''; // e.g., A'
            printf("%c->", lhs[i]);
            for (int j = 0; j < indCount; j++) {
                printf("%s%c", indirect[j], newNT);
                if (j != indCount-1) printf("|");
            }
            printf("\n");

            printf("%c->", newNT);
            for (int j = 0; j < dCount; j++) {
                printf("%s%c", direct[j], newNT);
                printf("|");
            }
            printf("#\n"); // epsilon
        }
    }

    return 0;
}
