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

    visited[0] = 1; // start from vertex A
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
                    // ✅ count only when we check a valid edge
                    if (!visited[j])  
                    {
                        opcount++; // only meaningful comparisons
                        if (min > cost[i][j])
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

// ------------------- Tester Function -------------------
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
                cost[i][j] = 9999; // treat 0 as infinity
        }
    }

    int min_cost = prims(cost, n);

    printf("Minimum Cost: %d\n", min_cost);
    printf("Operation Count (opcount): %d\n", opcount);
}

// ------------------- Plotter Function -------------------
void plotter()
{
    FILE *fp = fopen("prims.dat", "w");
    if (!fp)
    {
        printf("Error opening file!\n");
        return;
    }

    srand(time(NULL));

    for (int n = 5; n <= 10; n++) // test for graphs of size 5 to 10
    {
        int cost[50][50];
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i == j)
                    cost[i][j] = 9999;
                else
                    cost[i][j] = rand() % 20 + 1; // random weights
            }
        }

        prims(cost, n);
        fprintf(fp, "%d\t%d\n", n, opcount);
    }

    fclose(fp);
    printf("Plotter output saved to prims.dat\n");
}

// ------------------- Main Function -------------------
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
