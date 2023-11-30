#include <stdio.h>

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to find the multiplicative inverse of a modulo m using extended Euclidean algorithm
int modInverse(int a, int m) {
    int m0 = m;
    int y = 0, x = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        int q = a / m;
        int t = m;

        m = a % m;
        a = t;
        t = y;

        y = x - q * y;
        x = t;
    }

    if (x < 0)
        x += m0;

    return x;
}

int main() {
    int e = 31;
    int n = 3599;

    // Find p and q using trial-and-error
    int p, q;
    for (p = 2; p <= n; p++) {
        if (n % p == 0) {
            q = n / p;
            break;
        }
    }

    // Calculate Euler's totient function (phi(n))
    int phi_n = (p - 1) * (q - 1);

    // Find the private key (d) using the extended Euclidean algorithm
    int d = modInverse(e, phi_n);

    printf("Public key (e, n): (%d, %d)\n", e, n);
    printf("Private key (d): %d\n", d);

    return 0;
}