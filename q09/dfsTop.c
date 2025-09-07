#include <stdio.h>
#include <stdlib.h>

int n, opcount = 0, top = -1;

// DFS to detect cycle + build stack for topological sort
int dfs(int mat[n][n], int *vis, int *recStack, int src, int *stack) {
    vis[src] = 1;
    recStack[src] = 1;

    for (int i = 0; i < n; i++) {
        opcount++;
        if (mat[src][i]) {
            // Back edge → cycle found
            if (recStack[i]) return 1;
            // Explore unvisited
            if (!vis[i] && dfs(mat, vis, recStack, i, stack)) return 1;
        }
    }

    stack[++top] = src;  // push to stack
    recStack[src] = 0;   // backtrack
    return 0;
}

// Check connectivity + return stack (NULL if cycle exists)
int* topoSort(int mat[n][n]) {
    int vis[n], recStack[n];
    int *stack = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) vis[i] = recStack[i] = 0;

    for (int i = 0; i < n; i++) {
        if (!vis[i] && dfs(mat, vis, recStack, i, stack)) {
            free(stack);
            return NULL;
        }
    }
    return stack;
}

// Manual tester (input graph + run topological sort)
void tester() {
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    int mat[n][n];

    printf("Enter adjacency matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &mat[i][j]);

    int *stack = topoSort(mat);
    if (!stack) {
        printf("Cycle exists! Cannot perform topological sort.\n");
        return;
    }

    printf("Topological Order:\n");
    while (top >= 0) printf("%d ", stack[top--]);
    free(stack);
}

// Auto plotter (best-case opcount for DAG)
void plotter() {
    FILE *f1 = fopen("bfsMatTopSort.txt", "w");

    for (int k = 1; k <= 10; k++) {
        n = k;
        int mat[n][n];

        // Fill adjacency matrix (upper triangular)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                mat[i][j] = (j > i);

        opcount = 0, top = -1;
        topoSort(mat);
        fprintf(f1, "%d\t%d\n", n, opcount);
    }

    fclose(f1);
}

int main() {
    int choice;
    printf("Enter\n1. Tester\n2. Plotter\nChoice: ");
    scanf("%d", &choice);

    if (choice == 1) tester();
    else if (choice == 2) plotter();
    else printf("Invalid choice\n");

    return 0;
}
