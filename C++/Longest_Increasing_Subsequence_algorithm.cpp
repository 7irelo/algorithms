#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to find the length of the Longest Increasing Subsequence
int longestIncreasingSubsequenceLength(const vector<int>& nums) {
    int n = nums.size();
    vector<int> dp(n, 1);

    // Dynamic programming approach
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (nums[i] > nums[j]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }

    // Find the maximum length from the dp array
    int maxLength = 0;
    for (int i = 0; i < n; ++i) {
        maxLength = max(maxLength, dp[i]);
    }

    return maxLength;
}

int main() {
    vector<int> nums = {10, 22, 9, 33, 21, 50, 41, 60};
    int length = longestIncreasingSubsequenceLength(nums);
    cout << "Length of the Longest Increasing Subsequence: " << length << endl;
    return 0;
}
