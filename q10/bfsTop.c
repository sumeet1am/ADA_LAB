#include <stdio.h>
#include <stdlib.h>

int n, indeg[20], queue[20], front = -1, rear = -1, opcount = 0;

// BFS (Kahn's Algorithm) for Topological Sort
int bfs(int mat[n][n]) {
    int visited = 0;
    front = rear = -1;

    // push all vertices with indegree 0
    for (int i = 0; i < n; i++) {
        if (indeg[i] == 0) queue[++rear] = i;
    }

    while (front != rear) {
        int curr = queue[++front]; // pop front
        visited++;

        for (int i = 0; i < n; i++) {
            opcount++;
            if (mat[curr][i]) {
                indeg[i]--;             // reduce indegree
                if (indeg[i] == 0) {    // if no more incoming edges
                    queue[++rear] = i;
                }
            }
        }
    }

    // if visited != n → cycle exists
    return visited != n;
}

// Manual test
void tester() {
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    int mat[n][n];

    // reset indegree
    for (int i = 0; i < n; i++) indeg[i] = 0;

    printf("Enter adjacency matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &mat[i][j]);
            if (mat[i][j]) indeg[j]++; // calculate indegree
        }
    }

    if (bfs(mat)) {
        printf("Cycle exists! Cannot perform topological sort.\n");
    } else {
        printf("Topological Order:\n");
        for (int i = 0; i <= rear; i++) {
            printf("%d ", queue[i]);
        }
    }
}

// Auto plotter for opcount analysis
void plotter() {
    FILE *f1 = fopen("srcrmMatTopSort.txt", "w");

    for (int k = 1; k <= 10; k++) {
        n = k;
        int mat[n][n];

        // reset indegree and adjacency
        for (int i = 0; i < n; i++) indeg[i] = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                mat[i][j] = 0;

        // create upper triangular DAG
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                mat[i][j] = 1;
                indeg[j]++;
            }
        }

        opcount = 0;
        bfs(mat);
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
