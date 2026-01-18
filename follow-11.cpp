#include <stdio.h>
#include <string.h>
#include <ctype.h>

int n;
char prod[20][20];       // Productions
char FIRST[26][20];      // FIRST sets
int firstCount[26];
char FOLLOW[26][20];     // FOLLOW sets
int followCount[26];

// Add character to FIRST set
void addFirst(char nt, char ch) {
    int idx = nt - 'A';
    for(int i = 0; i < firstCount[idx]; i++)
        if(FIRST[idx][i] == ch) return;
    FIRST[idx][firstCount[idx]++] = ch;
}

// Add character to FOLLOW set, return 1 if added new
int addFollow(char nt, char ch) {
    int idx = nt - 'A';
    for(int i = 0; i < followCount[idx]; i++)
        if(FOLLOW[idx][i] == ch) return 0;
    FOLLOW[idx][followCount[idx]++] = ch;
    return 1;
}

// ----------------- Compute FIRST recursively -----------------
int visitedFirst[26];
void computeFirst(char nt) {
    int idx = nt - 'A';
    if(visitedFirst[idx]) return;
    visitedFirst[idx] = 1;

    for(int i = 0; i < n; i++) {
        if(prod[i][0] != nt) continue;
        char rhs[20];
        strcpy(rhs, prod[i]+3);

        char *token = strtok(rhs, "|");
        while(token) {
            int j = 0;
            int epsilonFlag = 1;
            while(token[j] && epsilonFlag) {
                epsilonFlag = 0;
                char sym = token[j];
                if(!isupper(sym)) { // terminal
                    addFirst(nt, sym);
                    break;
                } else { // non-terminal
                    computeFirst(sym);
                    int symIdx = sym - 'A';
                    for(int k = 0; k < firstCount[symIdx]; k++) {
                        if(FIRST[symIdx][k] != '#') 
                            addFirst(nt, FIRST[symIdx][k]);
                        else 
                            epsilonFlag = 1;
                    }
                }
                j++;
            }
            if(epsilonFlag) addFirst(nt, '#');
            token = strtok(NULL, "|");
        }
    }
}

// ----------------- Compute FOLLOW iteratively -----------------
void computeFollow() {
    // Start symbol
    addFollow(prod[0][0], '$');

    int changed;
    do {
        changed = 0;
        for(int i = 0; i < n; i++) {
            char lhs = prod[i][0];
            char rhs[20];
            strcpy(rhs, prod[i]+3);

            int len = strlen(rhs);
            for(int j = 0; j < len; j++) {
                char B = rhs[j];
                if(!isupper(B)) continue;

                int epsilonFlag = 1;
                int k = j+1;

                // Symbols after B
                while(k < len && epsilonFlag) {
                    epsilonFlag = 0;
                    char sym = rhs[k];
                    if(!isupper(sym)) {
                        if(addFollow(B, sym)) changed = 1;
                        break;
                    } else {
                        int symIdx = sym - 'A';
                        for(int x = 0; x < firstCount[symIdx]; x++) {
                            if(FIRST[symIdx][x] != '#') {
                                if(addFollow(B, FIRST[symIdx][x])) changed = 1;
                            } else epsilonFlag = 1;
                        }
                    }
                    k++;
                }

                // If all symbols after B can be epsilon, add FOLLOW(lhs)
                if(k == len || epsilonFlag) {
                    int lhsIdx = lhs - 'A';
                    for(int x = 0; x < followCount[lhsIdx]; x++) {
                        if(addFollow(B, FOLLOW[lhsIdx][x])) changed = 1;
                    }
                }
            }
        }
    } while(changed);
}

// ----------------- MAIN -----------------
int main() {
    memset(FIRST, 0, sizeof(FIRST));
    memset(firstCount, 0, sizeof(firstCount));
    memset(FOLLOW, 0, sizeof(FOLLOW));
    memset(followCount, 0, sizeof(followCount));
    memset(visitedFirst, 0, sizeof(visitedFirst));

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (use # for epsilon, format A->α|β):\n");
    for(int i = 0; i < n; i++)
        scanf("%s", prod[i]);

    // Compute FIRST
    for(int i = 0; i < n; i++)
        computeFirst(prod[i][0]);

    // Print FIRST
    printf("\nFIRST sets:\n");
    int printed[26] = {0};
    for(int i = 0; i < n; i++) {
        char nt = prod[i][0];
        int idx = nt - 'A';
        if(printed[idx]) continue;
        printed[idx] = 1;

        printf("FIRST(%c) = { ", nt);
        for(int j = 0; j < firstCount[idx]; j++)
            printf("%c ", FIRST[idx][j]);
        printf("}\n");
    }

    // Compute FOLLOW iteratively
    computeFollow();

    // Print FOLLOW
    memset(printed, 0, sizeof(printed));
    printf("\nFOLLOW sets:\n");
    for(int i = 0; i < n; i++) {
        char nt = prod[i][0];
        int idx = nt - 'A';
        if(printed[idx]) continue;
        printed[idx] = 1;

        printf("FOLLOW(%c) = { ", nt);
        for(int j = 0; j < followCount[idx]; j++)
            printf("%c ", FOLLOW[idx][j]);
        printf("}\n");
    }

    return 0;
}
