#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int c; // operation counter

void dijkstra(int n, int cost[n][n], int s, int dist[n])
{
    int i, v = 0, count = 1, min, visited[n];

    // initialize
    for (i = 0; i < n; i++)
    {
        visited[i] = 0;
        dist[i] = cost[s][i];
    }

    visited[s] = 1;
    dist[s] = 0;

    while (count < n)
    {
        min = 9999;

        for (i = 0; i < n; i++)
        {
            c++; // count comparison
            if (dist[i] < min && !visited[i])
            {
                min = dist[i];
                v = i;
            }
        }

        visited[v] = 1;
        count++;

        for (i = 0; i < n; i++)
        {
            if (dist[i] > dist[v] + cost[v][i])
                dist[i] = dist[v] + cost[v][i];
        }
    }
}

void tester()
{
    int i, j, n, s;
    printf("Enter the total number of nodes: ");
    scanf("%d", &n);

    int cost[n][n], dist[n];

    printf("Read the cost matrix:\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &cost[i][j]);
            if (cost[i][j] == 0)
                cost[i][j] = 9999;
        }
    }

    printf("Enter the source vertex (0 to %d): ", n - 1);
    scanf("%d", &s);

    c = 0;
    dijkstra(n, cost, s, dist);

    printf("Shortest path from %d is:\n", s);
    for (i = 0; i < n; i++)
    {
        if (s != i)
            printf("%d -> %d = %d\n", s, i, dist[i]);
    }

    printf("The count for %d number of vertices is %d\n", n, c);
}

void plotter()
{
    srand(time(NULL));
    FILE *fp = fopen("dijkstra.dat", "w");

    for (int n = 5; n <= 50; n += 5) // test sizes
    {
        int cost[n][n], dist[n];

        // generate random weighted graph
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i == j)
                    cost[i][j] = 0;
                else
                    cost[i][j] = rand() % 20 + 1; // random weight 1..20
            }
        }

        c = 0;
        dijkstra(n, cost, 0, dist); // run from source = 0

        fprintf(fp, "%d\t%d\n", n, c);
    }

    fclose(fp);
    printf("Plot data saved to dijkstra.dat\n");
}

int main()
{
    int ch;
    printf("\nEnter:\n1. Tester\n2. Plotter\nChoice: ");
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
