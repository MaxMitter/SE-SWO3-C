#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define MAX_VALUE 1000
#define MAX_COINS 10

static int min(int a, int b) {
    return a < b ? a : b;
}

static int min_coins_iterative(int value, int coin_value[], int n_coins) {
    int min_coins[MAX_COINS];

    min_coins[0] = 0;
    for(int v = 0; v < MAX_COINS; v++) {
        min_coins[v] = INT_MAX;
        for (int k = n_coins - 1; k >= 0; k--) {
            if (v >= coin_value[k]) {
                min_coins[v] = min(min_coins[v], min_coins[v - coin_value[k]] + 1);
            }
        }
    }

    return min_coins[value];
}

static int min_coins_rec(int value, int coin_value[], int n_coins) {
    if (value == 0)
        return 0;

    int min_coins = INT_MAX;

    for (int k = n_coins - 1; k >= 0; k--) {
        if (value >= coin_value[k]) {
            int m = min_coins_rec(value - coin_value[k], coin_value, n_coins);

            min_coins = min(min_coins, m + 1);
        }
    }

    return min_coins;
}

int main() {

    int min_coins;
    int coins[] = { 1, 2, 5, 10, 20, 25 };
    int n_coins = sizeof(coins)/sizeof(coins[0]);

    min_coins = min_coins_rec(40, coins, n_coins);

    printf("min_coins: %d\n", min_coins);
    return 0;
}