#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Function to find all prime numbers up to n using Sieve of Eratosthenes algorithm
void sieveOfEratosthenes(int n) {
    // Create a boolean array "prime[0..n]" and initialize all entries as true.
    // A value in prime[i] will finally be false if i is Not a prime, else true.
    bool prime[n + 1];
    for (int i = 0; i <= n; i++)
        prime[i] = true;

    for (int p = 2; p * p <= n; p++) {
        // If prime[p] is not changed, then it is a prime
        if (prime[p] == true) {
            // Update all multiples of p
            for (int i = p * p; i <= n; i += p)
                prime[i] = false;
        }
    }

    // Print all prime numbers
    printf("Prime numbers up to %d are:\n", n);
    for (int p = 2; p <= n; p++) {
        if (prime[p])
            printf("%d ", p);
    }
    printf("\n");
}

// Main function to test the above algorithm
int main() {
    int n;
    printf("Enter a number to find all primes up to that number: ");
    scanf("%d", &n);

    // Call the function to find all prime numbers up to n
    sieveOfEratosthenes(n);

    return 0;
}
