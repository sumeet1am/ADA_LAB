#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

int n, opcount, dist[100][100];

// Floyd–Warshall Algorithm
void floydWarshall(int adjMat[n][n], int n) {
    opcount = 0;

    // Step 1: Initialize distance matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (adjMat[i][j] == -1)  // -1 means infinity
                dist[i][j] = INT_MAX;
            else
                dist[i][j] = adjMat[i][j];
        }
    }

    // Step 2: Relax paths using every vertex as an intermediate
    for (int k = 0; k < n; k++) {        // pick intermediate node
        for (int i = 0; i < n; i++) {    // pick source
            for (int j = 0; j < n; j++) { // pick destination
                opcount++;
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX &&
                    dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
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
    printf("Enter adjacency matrix (-1 for infinity):\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &adjMat[i][j]);

    floydWarshall(adjMat, n);

    printf("Shortest distances between all pairs:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INT_MAX)
                printf("INF\t");
            else
                printf("%d\t", dist[i][j]);
        }
        printf("\n");
    }
}

// Automated test for opcount
void plotter() {
    srand(time(NULL));
    FILE *fp = fopen("floyd.txt", "w");

    for (int k = 2; k <= 10; k++) {
        n = k;
        int adjMat[n][n];

        // generate random weights (except diagonals = 0)
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j)
                    adjMat[i][j] = 0;
                else
                    adjMat[i][j] = rand() % 20 + 1; // weights 1–20
            }
        }

        floydWarshall(adjMat, n);
        fprintf(fp, "%d\t%d\n", n, opcount);
    }

    fclose(fp);
}

int main() {
    int ch;
    printf("Enter\n1. Tester\n2. Plotter\nChoice: ");
    scanf("%d", &ch);

    if (ch == 1) tester();
    else if (ch == 2) plotter();
    else printf("Invalid choice!\n");

    return 0;
}
