#include <stdio.h>
#include <string.h>

#define MAX 20

int n;
char lhs[MAX];                   // LHS symbols
char rhs[MAX][10][50];           // RHS alternatives
int altCount[MAX];               // number of alternatives per production
int ntIndex = 0;                 // counter for new non-terminals

// Find longest common prefix of multiple strings
void commonPrefix(char arr[][50], int count, char *prefix) {
    if(count == 0) { prefix[0]='\0'; return; }
    strcpy(prefix, arr[0]);
    for(int i=1;i<count;i++) {
        int j=0;
        while(prefix[j] && arr[i][j] && prefix[j]==arr[i][j]) j++;
        prefix[j]='\0';
    }
}

// Left factoring function (recursive)
void leftFactor(char A, char arr[][50], int count) {
    if(count <= 1) {
        printf("%c->", A);
        for(int i=0;i<count;i++) {
            if(i>0) printf("|");
            printf("%s", arr[i]);
        }
        printf("\n");
        return;
    }

    char prefix[50];
    commonPrefix(arr, count, prefix);

    if(strlen(prefix)==0) { // no common prefix
        printf("%c->", A);
        for(int i=0;i<count;i++) {
            if(i>0) printf("|");
            printf("%s", arr[i]);
        }
        printf("\n");
        return;
    }

    // Create new non-terminal
    char newNT = A;
    newNT += '\'' + ntIndex++;  // e.g., A', B' etc.

    printf("%c->%s%c", A, prefix, newNT);

    // Print alternatives that do not start with prefix
    int firstPrinted = 1;
    for(int i=0;i<count;i++) {
        if(strncmp(arr[i], prefix, strlen(prefix)) !=0) {
            if(firstPrinted) { printf("|"); firstPrinted=0; }
            else printf("|");
            printf("%s", arr[i]);
        }
    }
    printf("\n");

    // Collect suffixes for new non-terminal
    char suffixes[10][50];
    int suffixCount=0;
    for(int i=0;i<count;i++) {
        if(strncmp(arr[i], prefix, strlen(prefix))==0) {
            char *suf = arr[i]+strlen(prefix);
            if(strlen(suf)==0) strcpy(suf,"#"); // epsilon
            strcpy(suffixes[suffixCount++], suf);
        }
    }

    leftFactor(newNT, suffixes, suffixCount);
}

int main() {
    printf("Enter number of productions: ");
    scanf("%d",&n);

    printf("Enter productions (format A->α|β):\n");
    for(int i=0;i<n;i++) {
        char prod[50];
        scanf("%s",prod);
        lhs[i]=prod[0];

        char *ptr=strchr(prod,'>');
        ptr++; // skip '>'
        int j=0;
        char *token=strtok(ptr,"|");
        while(token) {
            strcpy(rhs[i][j++],token);
            token=strtok(NULL,"|");
        }
        altCount[i]=j;
    }

    printf("\nLeft factored grammar:\n");
    ntIndex=0;
    for(int i=0;i<n;i++) {
        leftFactor(lhs[i], rhs[i], altCount[i]);
    }

    return 0;
}
