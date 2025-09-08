#include <stdio.h>
#include <stdlib.h>
#define MAX 100

int t[MAX][MAX], v[MAX], w[MAX]; 
int n, m, count = 0;

// Utility function to get max of two numbers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Dynamic Programming for 0/1 Knapsack
int knapsack() {
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (i == 0 || j == 0) {
                t[i][j] = 0;
            } else {
                count++;
                if (w[i-1] > j) { 
                    // current item cannot fit
                    t[i][j] = t[i-1][j];
                } else {
                    // choose max of: including item i-1 OR excluding it
                    t[i][j] = max(t[i-1][j], v[i-1] + t[i-1][j - w[i-1]]);
                }
            }
        }
    }
    return t[n][m];
}

// Manual testing
void tester() {
    printf("Number of items: ");
    scanf("%d", &n);
    printf("Knapsack capacity: ");
    scanf("%d", &m);

    printf("Enter weights and values:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &w[i], &v[i]);
    }

    int maxVal = knapsack();
    printf("Maximum value = %d\n", maxVal);

    // Print DP table
    printf("\nDP Table:\n");
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            printf("%d ", t[i][j]);
        }
        printf("\n");
    }

    // Find selected items (backtracking from DP table)
    printf("\nSelected items:\n");
    int cap = m;
    for (int i = n; i > 0; i--) {
        if (t[i][cap] != t[i-1][cap]) {
            printf("Item %d (W=%d, V=%d)\n", i, w[i-1], v[i-1]);
            cap -= w[i-1];
        }
    }
}

// Automated analysis (count of operations)
void plotter() {
    FILE *f1 = fopen("Knap.txt", "w");

    for (int iter = 1; iter <= 10; iter++) {
        count = 0;
        n = iter * 2;   // number of items
        m = iter * 5;   // capacity

        // generate random weights & values
        for (int i = 0; i < n; i++) {
            w[i] = rand() % m + 1;
            v[i] = rand() % 50 + 1;
        }

        knapsack();
        fprintf(f1, "%d\t%d\n", n, count);
    }

    fclose(f1);
}

int main() {
    int ch;
    printf("Enter your choice:\n1. Tester\n2. Plotter\nChoice: ");
    scanf("%d", &ch);

    if (ch == 1) tester();
    else if (ch == 2) plotter();
    else printf("Invalid input!\n");

    return 0;
}
