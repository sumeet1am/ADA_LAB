#include <stdio.h>
#include <stdlib.h>

int n, opcount = 0, top = -1;

int dfs(int mat[n][n], int vis[], int track[], int src, int stack[]) {
    vis[src] = track[src] = 1;

    for (int i = 0; i < n; i++, opcount++) {
        if (mat[src][i]) {
            if (track[i]) return 1;                // cycle found
            if (!vis[i] && dfs(mat, vis, track, i, stack)) return 1;
        }
    }

    stack[++top] = src;
    track[src] = 0;
    return 0;
}

int* checkConnectivity(int mat[n][n]) {
    int vis[n], track[n];
    int *stack = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) vis[i] = track[i] = 0;

    for (int i = 0; i < n; i++)
        if (!vis[i] && dfs(mat, vis, track, i, stack))
            return NULL;   // cycle → not a DAG

    return stack;
}

void tester() {
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    int adj[n][n];

    printf("Enter adjacency matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &adj[i][j]);

    int *stack = checkConnectivity(adj);

    if (!stack) {
        printf("Cycle exists.. Cannot perform topological sorting!!!\n");
        exit(0);
    }

    printf("Topological sorting order:\n");
    while (top != -1) printf("%d ", stack[top--]);
    free(stack);
}

void plotter() {
    FILE *fp = fopen("bfsMatTopSort.txt", "w");

    for (n = 1; n <= 10; n++) {
        int adj[n][n];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                adj[i][j] = (i < j);   // upper triangular edges

        opcount = 0; top = -1;
        checkConnectivity(adj);
        fprintf(fp, "%d\t%d\n", n, opcount);
    }
    fclose(fp);
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
