#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 100

int t[MAX][MAX], v[MAX], w[MAX], n, m, count;

int max(int a, int b) {
    return (a > b) ? a : b;
}

// Dynamic Programming Knapsack
int Knap() {
    count = 0;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (i == 0 || j == 0)
                t[i][j] = 0;
            else {
                count++;
                if (j < w[i-1])
                    t[i][j] = t[i-1][j];
                else
                    t[i][j] = max(t[i-1][j], v[i-1] + t[i-1][j - w[i-1]]);
            }
        }
    }
    return t[n][m];
}

// Tester function
void tester() {
    printf("Number of items: "); scanf("%d", &n);
    printf("Sack capacity: "); scanf("%d", &m);
    printf("Weight\tValue\n");
    for (int i = 0; i < n; i++) scanf("%d%d", &w[i], &v[i]);

    int maxValue = Knap();
    printf("Max value: %d\n", maxValue);

    printf("DP Table:\n");
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++)
            printf("%d ", t[i][j]);
        printf("\n");
    }

    printf("Selected items: ");
    int temp = m;
    for (int i = n; i > 0; i--) {
        if (t[i][temp] != t[i-1][temp]) {
            printf("%d ", i);
            temp -= w[i-1];
        }
    }
    printf("\n");
}

// Plotter function
void plotter() {
    FILE *f1 = fopen("Knap.txt", "w");
    srand(time(NULL));

    for (int iter = 1; iter <= 10; iter++) {
        n = iter * 2;
        m = iter * 5;
        for (int i = 0; i < n; i++) {
            w[i] = rand() % m + 1;
            v[i] = rand() % 50 + 1;
        }
        Knap();
        fprintf(f1, "%d\t%d\n", n, count);
    }
    fclose(f1);
    printf("Plot data saved to Knap.txt\n");
}

// Main function
int main() {
    int choice;
    printf("Enter your choice:\n1. Tester\n2. Plotter\n");
    scanf("%d", &choice);

    if (choice == 1) tester();
    else if (choice == 2) plotter();
    else printf("Invalid input\n");

    return 0;
}
