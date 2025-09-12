#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int opcount = 0, dp[25][25], weight[25], profit[25];

int max(int a, int b) {
    return a > b ? a : b;
}

// Recursive memoization
int knapsackMemo(int n, int W) {
    if (dp[n][W] != -1) return dp[n][W];

    opcount++;
    if (weight[n - 1] <= W)
        return dp[n][W] = max(knapsackMemo(n - 1, W), profit[n - 1] + knapsackMemo(n - 1, W - weight[n - 1]));
    else
        return dp[n][W] = knapsackMemo(n - 1, W);
}

// Initialize dp table
void init(int n, int W) {
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= W; j++) {
            if (i == 0 || j == 0) dp[i][j] = 0;
            else dp[i][j] = -1;
        }
    }
}

// Tester: user input
void tester() {
    int n, W;
    printf("Enter number of items: ");
    scanf("%d", &n);
    printf("Sack capacity: ");
    scanf("%d", &W);

    for (int i = 0; i < n; i++) {
        printf("Enter weight and profit of item %d: ", i + 1);
        scanf("%d%d", &weight[i], &profit[i]);
    }

    init(n, W);
    printf("Max profit is %d\n", knapsackMemo(n, W));

    printf("DP Table:\n");
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= W; j++)
            printf("%d\t", dp[i][j]);
        printf("\n");
    }

    printf("Picked items: ");
    int k = W;
    for (int i = n; i > 0; i--) {
        if (dp[i][k] != dp[i - 1][k]) {
            printf("%d ", i);
            k -= weight[i - 1];
        }
    }
    printf("\nOpcount: %d\n", opcount);
}

// Plotter: random items, saves operation count
void plotter() {
    FILE *fp = fopen("knapsackMemo.txt", "w");
    srand(time(NULL));

    for (int i = 5; i <= 10; i++) {
        int W = i * 2;
        for (int j = 0; j < i; j++) {
            weight[j] = rand() % 10 + 1;
            profit[j] = rand() % 50 + 1;
        }
        init(i, W);
        opcount = 0;
        knapsackMemo(i, W);
        fprintf(fp, "%d\t%d\n", i, opcount);
    }

    fclose(fp);
    printf("Plot data saved to knapsackMemo.txt\n");
}

// Main function
int main() {
    int ch;
    printf("Enter \n1. Tester\n2. Plotter\n");
    scanf("%d", &ch);

    if (ch == 1) tester();
    else if (ch == 2) plotter();
    else printf("Invalid choice.\n");

    return 0;
}
