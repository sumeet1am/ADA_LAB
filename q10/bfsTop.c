#include <stdio.h>
#include <stdlib.h>

int n, indeg[20], opcount = 0, queue[20], front, rear;

int bfs(int mat[n][n]) {
    int count = 0;
    front = rear = -1;

    for (int i = 0; i < n; i++)
        if (indeg[i] == 0) queue[++rear] = i;

    while (front != rear) {
        int cur = queue[++front];
        count++;
        for (int i = 0; i < n; i++, opcount++)
            if (mat[cur][i] && --indeg[i] == 0)
                queue[++rear] = i;
    }
    return count != n; // if not all processed → cycle
}

void tester() {
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    int adj[n][n];

    for (int i = 0; i < n; i++) indeg[i] = 0;

    printf("Enter adjacency matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            scanf("%d", &adj[i][j]);
            if (adj[i][j]) indeg[j]++;
        }

    if (bfs(adj)) {
        printf("Cycle exists.. Cannot perform topological sorting!!!\n");
        exit(0);
    }

    printf("Topological sorting order:\n");
    for (int i = 0; i <= rear; i++) printf("%d ", queue[i]);
}

void plotter() {
    FILE *fp = fopen("srcrmMatTopSort.txt", "w");

    for (n = 1; n <= 10; n++) {
        int adj[n][n];
        for (int i = 0; i < n; i++) indeg[i] = 0;

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                adj[i][j] = (i < j ? (indeg[j]++, 1) : 0);

        opcount = 0;
        bfs(adj);
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
    else printf("Invalid choice\n");

    return 0;
}
