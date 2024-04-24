#include <stdio.h>

// Function to find the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to find the maximum subarray sum using Kadane's Algorithm
int maxSubArraySum(int arr[], int size) {
    int max_so_far = arr[0]; // Initialize the maximum sum so far
    int curr_max = arr[0];   // Initialize the current maximum sum

    // Traverse the array from the second element
    for (int i = 1; i < size; i++) {
        // Update the current maximum sum by adding the current element or starting a new subarray
        curr_max = max(arr[i], curr_max + arr[i]);

        // Update the maximum sum so far
        max_so_far = max(max_so_far, curr_max);
    }
    return max_so_far;
}

// Main function to test the above algorithm
int main() {
    int arr[] = {-2, -3, 4, -1, -2, 1, 5, -3}; // Example array
    int size = sizeof(arr) / sizeof(arr[0]);  // Calculate the size of the array

    // Call the function to find the maximum subarray sum
    int max_sum = maxSubArraySum(arr, size);

    // Print the maximum subarray sum
    printf("Maximum subarray sum is %d\n", max_sum);

    return 0;
}
