#include <stdio.h>
#include <stdlib.h>

int n, isCycle = 0, components = 0, opcount = 0, isTester = 0;

void bfs(int mat[n][n], int vis[], int src) {
    int q[n], par[n], f = -1, r = -1;
    vis[src] = 1; q[++r] = src; par[r] = -1;

    while (f != r) {
        int cur = q[++f], p = par[f];
        if (isTester) printf("%d ", cur);

        for (int i = 0; i < n; i++, opcount++) {
            if (mat[cur][i]) {
                if (i != p && vis[i]) isCycle = 1;
                else if (!vis[i]) {
                    vis[i] = 1;
                    q[++r] = i; par[r] = cur;
                }
            }
        }
    }
}

void checkConnectivity(int mat[n][n]) {
    int vis[n], comp = 1;
    for (int i = 0; i < n; i++) vis[i] = 0;

    for (int i = 0; i < n; i++)
        if (!vis[i]) {
            components++;
            if (isTester) printf("\nComponent %d: ", comp++);
            bfs(mat, vis, i);
        }
}

void tester() {
    isTester = 1;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    int adj[n][n];
    printf("Enter adjacency matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &adj[i][j]);

    checkConnectivity(adj);

    printf("\nConnected components: %d", components);
    printf("\nCycle %s\n", isCycle ? "exists" : "does not exist");
}

void plotter() {
    isTester = 0;
    FILE *fp = fopen("bfsadjMat.txt", "w");

    for (n = 1; n <= 10; n++) {
        int adj[n][n];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                adj[i][j] = (i != j);

        opcount = components = isCycle = 0;
        checkConnectivity(adj);
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
    else printf("Invalid choice");
    return 0;
}
