#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int dp[25][25], weight[25], profit[25];
int opcount = 0;

// Return maximum of two numbers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Recursive function with memoization
int knapsackMemo(int n, int W) {
    if (dp[n][W] != -1)  // already computed
        return dp[n][W];

    opcount++;
    if (weight[n-1] <= W) {
        // Option 1: include item (n-1), Option 2: exclude item
        return dp[n][W] = max(
            knapsackMemo(n-1, W),
            profit[n-1] + knapsackMemo(n-1, W - weight[n-1])
        );
    } else {
        // Item too heavy → skip
        return dp[n][W] = knapsackMemo(n-1, W);
    }
}

// Initialize dp table
void init(int n, int W) {
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= W; j++) {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else
                dp[i][j] = -1;
        }
    }
}

// Manual testing
void tester() {
    int n, W;
    printf("Enter number of items: ");
    scanf("%d", &n);
    printf("Enter knapsack capacity: ");
    scanf("%d", &W);

    printf("Enter weight and profit for each item:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &weight[i], &profit[i]);
    }

    init(n, W);
    int maxProfit = knapsackMemo(n, W);
    printf("\nMaximum Profit = %d\n", maxProfit);

    // Print dp table
    printf("\nDP Table:\n");
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= W; j++) {
            printf("%d\t", dp[i][j]);
        }
        printf("\n");
    }

    // Print selected items
    printf("\nSelected items:\n");
    int cap = W;
    for (int i = n; i > 0; i--) {
        if (dp[i][cap] != dp[i-1][cap]) {
            printf("Item %d (W=%d, P=%d)\n", i, weight[i-1], profit[i-1]);
            cap -= weight[i-1];
        }
    }

    printf("\nOpcount = %d\n", opcount);
}

// Automatic plotting (writes to file)
void plotter() {
    FILE *fp = fopen("knapsackMemo.txt", "w");

    for (int n = 5; n <= 10; n++) {
        int W = n * 2;

        // Random weights & profits
        for (int i = 0; i < n; i++) {
            weight[i] = rand() % 10 + 1;
            profit[i] = rand() % 50 + 1;
        }

        init(n, W);
        opcount = 0;
        knapsackMemo(n, W);
        fprintf(fp, "%d\t%d\n", n, opcount);
    }

    fclose(fp);
}

int main() {
    int ch;
    printf("Enter:\n1. Tester\n2. Plotter\nChoice: ");
    scanf("%d", &ch);

    if (ch == 1) tester();
    else if (ch == 2) plotter();
    else printf("Invalid choice!\n");

    return 0;
}
