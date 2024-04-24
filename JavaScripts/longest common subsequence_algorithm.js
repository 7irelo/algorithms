function longestCommonSubsequence(str1, str2) {
    // Create a 2D array to store the lengths of LCS for each pair of substrings
    const dp = [];
    for (let i = 0; i <= str1.length; i++) {
        dp[i] = new Array(str2.length + 1).fill(0);
    }

    // Fill the dp array using dynamic programming approach
    for (let i = 1; i <= str1.length; i++) {
        for (let j = 1; j <= str2.length; j++) {
            if (str1[i - 1] === str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1; // If characters match, increment LCS length
            } else {
                dp[i][j] = Math.max(dp[i - 1][j], dp[i][j - 1]); // Otherwise, take maximum of previous lengths
            }
        }
    }

    // Reconstruct LCS from dp array
    let lcs = '';
    let i = str1.length, j = str2.length;
    while (i > 0 && j > 0) {
        if (str1[i - 1] === str2[j - 1]) {
            lcs = str1[i - 1] + lcs; // Add matched character to LCS
            i--;
            j--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--; // Move to previous row if left cell has higher value
        } else {
            j--; // Move to previous column if top cell has higher value
        }
    }

    return lcs;
}

// Example strings
const str1 = 'ABCBDAB';
const str2 = 'BDCAB';

// Find the longest common subsequence
const result = longestCommonSubsequence(str1, str2);
console.log('Longest Common Subsequence:', result);
