#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int opcount; // global counter

// ------------------- Prim's Algorithm -------------------
int prims(int cost[50][50], int n)
{
    int visited[50] = {0};
    int edges = 0, min_cost = 0;
    int a = -1, b = -1, min;

    visited[0] = 1; // start from A
    opcount = 0;

    while (edges < n - 1)
    {
        min = 9999;
        for (int i = 0; i < n; i++)
        {
            if (visited[i])
            {
                for (int j = 0; j < n; j++)
                {
                    // ✅ Count comparison only for visited → unvisited pairs
                    if (!visited[j])
                    {
                        opcount++;
                        if (cost[i][j] < min)
                        {
                            min = cost[i][j];
                            a = i;
                            b = j;
                        }
                    }
                }
            }
        }

        printf("%c --> %c | Cost: %d\n", a + 65, b + 65, min);
        visited[b] = 1;
        min_cost += min;
        edges++;
    }

    return min_cost;
}

// ------------------- Tester -------------------
void tester()
{
    int n, cost[50][50];
    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    printf("Enter cost matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &cost[i][j]);
            if (cost[i][j] == 0)
                cost[i][j] = 9999;
        }
    }

    int min_cost = prims(cost, n);

    printf("Minimum Cost: %d\n", min_cost);
    printf("Operation Count (opcount): %d\n", opcount);
}

// ------------------- Plotter -------------------
void plotter()
{
    FILE *fp = fopen("prims.dat", "w");
    if (!fp)
    {
        printf("Error opening file!\n");
        return;
    }

    srand(time(NULL));

    for (int n = 5; n <= 10; n++)
    {
        int cost[50][50];
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i == j)
                    cost[i][j] = 9999;
                else
                    cost[i][j] = rand() % 20 + 1;
            }
        }

        prims(cost, n);
        fprintf(fp, "%d\t%d\n", n, opcount);
    }

    fclose(fp);
    printf("Plotter output saved to prims.dat\n");
}

// ------------------- Main -------------------
int main()
{
    int ch;
    printf("Enter\n1. Tester\n2. Plotter\nChoice: ");
    scanf("%d", &ch);

    switch (ch)
    {
    case 1:
        tester();
        break;
    case 2:
        plotter();
        break;
    default:
        printf("Invalid choice!\n");
    }

    return 0;
}
