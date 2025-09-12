#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

int n, opcount, dist[100][100];

void floyds(int adjMat[n][n]) {
    opcount = 0;

    // Initialize dist[][] with adjMat values
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dist[i][j] = (adjMat[i][j] == -1 ? INT_MAX : adjMat[i][j]);

    // Floyd–Warshall updates
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++, opcount++)
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX &&
                    dist[i][j] > dist[i][k] + dist[k][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
}

void tester() {
    printf("Enter number of nodes: ");
    scanf("%d", &n);
    int adj[n][n];

    printf("Enter adjacency matrix (-1 for infinity):\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &adj[i][j]);

    floyds(adj);

    printf("\nShortest distances between all pairs:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INT_MAX) printf("INF\t");
            else printf("%d\t", dist[i][j]);
        }
        printf("\n");
    }
}

void plotter() {
    srand(time(NULL));
    FILE *fp = fopen("floydes.txt", "w");

    for (n = 2; n < 12; n++) {
        int adj[n][n];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                adj[i][j] = (i == j ? 0 : rand() % 100);

        floyds(adj);
        fprintf(fp, "%d\t%d\n", n, opcount);
    }
    fclose(fp);
}

int main() {
    int ch;
    printf("Enter\n1.Tester\n2.Plotter\n");
    scanf("%d", &ch);

    if (ch == 1) tester();
    else if (ch == 2) plotter();
    else printf("Invalid choice!\n");

    return 0;
}
