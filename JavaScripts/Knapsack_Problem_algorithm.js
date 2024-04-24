function knapsack(weights, values, capacity) {
    const n = weights.length;
    const dp = Array.from({ length: n + 1 }, () => Array(capacity + 1).fill(0));

    for (let i = 1; i <= n; i++) {
        for (let w = 0; w <= capacity; w++) {
            if (weights[i - 1] <= w) {
                dp[i][w] = Math.max(dp[i - 1][w], values[i - 1] + dp[i - 1][w - weights[i - 1]]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    const selectedItems = [];
    let i = n, w = capacity;
    while (i > 0 && w > 0) {
        if (dp[i][w] !== dp[i - 1][w]) {
            selectedItems.push(i - 1);
            w -= weights[i - 1];
        }
        i--;
    }

    return {
        maxValue: dp[n][capacity],
        selectedItems: selectedItems.reverse()
    };
}

// Example usage
const weights = [2, 3, 4, 5];
const values = [3, 4, 5, 6];
const capacity = 8;

const result = knapsack(weights, values, capacity);
console.log('Max Value:', result.maxValue);
console.log('Selected Items:', result.selectedItems.map(item => `Item ${item + 1}`));
