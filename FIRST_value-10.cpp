#include <stdio.h>
#include <ctype.h>
#include <string.h>

int n;
char prod[20][20];
char FIRST[26][20];
int firstCount[26];
int visited[26];

void addFirst(char nt, char ch) {
    int idx = nt - 'A';
    for (int i = 0; i < firstCount[idx]; i++)
        if (FIRST[idx][i] == ch)
            return;

    FIRST[idx][firstCount[idx]++] = ch;
}

void findFirst(char nt);

void processRHS(char nt, char *rhs) {
    int i = 0;
    int epsilonFound = 1;

    while (rhs[i] != '\0' && epsilonFound) {
        epsilonFound = 0;

        // Terminal
        if (!isupper(rhs[i])) {
            addFirst(nt, rhs[i]);
            return;
        }

        // Non-terminal
        findFirst(rhs[i]);
        int idx = rhs[i] - 'A';

        for (int j = 0; j < firstCount[idx]; j++) {
            if (FIRST[idx][j] == '#')
                epsilonFound = 1;
            else
                addFirst(nt, FIRST[idx][j]);
        }

        i++;
    }

    if (epsilonFound)
        addFirst(nt, '#');
}

void findFirst(char nt) {
    int idx = nt - 'A';
    if (visited[idx])
        return;

    visited[idx] = 1;

    for (int i = 0; i < n; i++) {
        if (prod[i][0] == nt) {

            char rhs[20];
            strcpy(rhs, prod[i] + 3);  // skip A->

            char *token = strtok(rhs, "|");
            while (token != NULL) {
                processRHS(nt, token);
                token = strtok(NULL, "|");
            }
        }
    }
}

int main() {
    // 🔹 IMPORTANT INITIALIZATION
    memset(FIRST, 0, sizeof(FIRST));
    memset(firstCount, 0, sizeof(firstCount));
    memset(visited, 0, sizeof(visited));

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (use # for epsilon):\n");
    for (int i = 0; i < n; i++)
        scanf("%s", prod[i]);

    for (int i = 0; i < n; i++)
        findFirst(prod[i][0]);

    printf("\nFIRST sets:\n");

    int printed[26] = {0};
    for (int i = 0; i < n; i++) {
        char nt = prod[i][0];
        int idx = nt - 'A';

        if (printed[idx])
            continue;

        printed[idx] = 1;

        printf("FIRST(%c) = { ", nt);
        for (int j = 0; j < firstCount[idx]; j++)
            printf("%c ", FIRST[idx][j]);
        printf("}\n");
    }

    return 0;
}
