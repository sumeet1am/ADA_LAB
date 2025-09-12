#include <stdio.h>
#include <stdlib.h>

int isCycle = 0, components = 0, n, opcount = 0, isTester = 0;

void dfs(int mat[n][n], int vis[], int src, int par) {
    vis[src] = 1;
    if (isTester) printf("%d ", src);

    for (int i = 0; i < n; i++) {
        opcount++;
        if (mat[src][i]) {
            if (vis[i] && i != par) isCycle = 1;
            else if (!vis[i]) dfs(mat, vis, i, src);
        }
    }
}

void checkConnectivity(int mat[n][n]) {
    int vis[n], k = 1;
    for (int i = 0; i < n; i++) vis[i] = 0;

    for (int i = 0; i < n; i++)
        if (!vis[i]) {
            components++;
            if (isTester) printf("\nComponent %d: ", k++);
            dfs(mat, vis, i, -1);
        }
}

void tester() {
    isTester = 1;
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    int adjMat[n][n];
    printf("Enter adjacency matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &adjMat[i][j]);

    checkConnectivity(adjMat);
    printf("\nConnected components: %d\n", components);
    printf(isCycle ? "Cycle exists\n" : "Cycle does not exist\n");
}

void plotter() {
    FILE *f1 = fopen("dfsadjMat.txt", "w");
    isTester = 0;

    for (n = 1; n <= 10; n++) {
        int adjMat[n][n];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                adjMat[i][j] = (i != j);

        opcount = components = isCycle = 0;
        checkConnectivity(adjMat);
        fprintf(f1, "%d\t%d\n", n, opcount);
    }
    fclose(f1);
}

int main() {
    int choice;
    printf("Enter\n1.Tester\n2.Plotter\n");
    scanf("%d", &choice);
    if (choice == 1) tester();
    else if (choice == 2) plotter();
    else printf("Invalid choice\n");
    return 0;
}
