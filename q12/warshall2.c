#include <stdio.h>
#include <stdlib.h>

int n, opcount, paths[100][100];

// Warshall’s Algorithm – Transitive Closure
void warshall(int adjMat[n][n], int n) {
    opcount = 0;

    // Step 1: Initialize paths matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            paths[i][j] = adjMat[i][j];

    // Step 2: Update paths using each node as intermediate
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (paths[i][k]) {  // only if path exists from i → k
                for (int j = 0; j < n; j++) {
                    opcount++;
                    paths[i][j] = paths[i][j] || (paths[i][k] && paths[k][j]);
                }
            }
        }
    }
}

// Manual testing
void tester() {
    printf("Enter number of nodes: ");
    scanf("%d", &n);

    int adjMat[n][n];
    printf("Enter adjacency matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &adjMat[i][j]);

    warshall(adjMat, n);

    printf("Transitive closure matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d\t", paths[i][j]);
        printf("\n");
    }
}

// Automated test – write opcount to files
void plotter() {
    FILE *fBest = fopen("warshallbest.txt", "w");
    FILE *fWorst = fopen("warshallworst.txt", "w");

    for (int k = 1; k <= 10; k++) {
        n = k;
        int adjMat[n][n];

        // Worst case: complete graph (except diagonals)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                adjMat[i][j] = (i != j) ? 1 : 0;

        warshall(adjMat, n);
        fprintf(fWorst, "%d\t%d\n", n, opcount);

        // Best case: simple cycle graph
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                adjMat[i][j] = 0;

        for (int i = 0; i < n - 1; i++)
            adjMat[i][i + 1] = 1;
        adjMat[n - 1][0] = 1;

        warshall(adjMat, n);
        fprintf(fBest, "%d\t%d\n", n, opcount);
    }

    fclose(fBest);
    fclose(fWorst);
}

int main() {
    int ch;
    printf("Enter\n1. Tester\n2. Plotter\nChoice: ");
    scanf("%d", &ch);

    if (ch == 1) tester();
    else if (ch == 2) plotter();
    else printf("Invalid choice!!\n");

    return 0;
}
