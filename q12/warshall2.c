#include <stdio.h>
#include <stdlib.h>

int n, opcount, paths[100][100];

void warshall(int n, int adjMat[n][n]) {
    opcount = 0;

    // Initialize paths matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            paths[i][j] = adjMat[i][j];

    // Warshall’s algorithm
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            if (paths[i][k]) {
                for (int j = 0; j < n; j++) {
                    opcount++;
                    paths[i][j] = paths[i][j] || (paths[i][k] && paths[k][j]);
                }
            }
}

void tester() {
    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    int adjMat[n][n];
    printf("Enter the adjacency matrix: \n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &adjMat[i][j]);

    warshall(n, adjMat);

    printf("Transitive closure matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d\t", paths[i][j]);
        printf("\n");
    }
}

void plotter() {
    FILE *best = fopen("warshallbest.txt", "w");
    FILE *worst = fopen("warshallworst.txt", "w");

    for (int k = 1; k <= 10; k++) {
        n = k;
        int adjMat[n][n];

        // Worst case: complete graph (dense)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                adjMat[i][j] = (i != j);

        warshall(n, adjMat);
        fprintf(worst, "%d\t%d\n", n, opcount);

        // Best case: simple chain/cycle (sparse)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                adjMat[i][j] = 0;

        for (int i = 0; i < n - 1; i++)
            adjMat[i][i + 1] = 1;
        adjMat[n - 1][0] = 1; // close cycle

        warshall(n, adjMat);
        fprintf(best, "%d\t%d\n", n, opcount);
    }

    fclose(best);
    fclose(worst);
}

int main() {
    int ch;
    printf("Enter\n1. Tester\n2. Plotter\n");
    scanf("%d", &ch);

    switch (ch) {
    case 1:
        tester();
        break;
    case 2:
        plotter();
        break;
    default:
        printf("Invalid choice!! ");
    }
    return 0;
}
