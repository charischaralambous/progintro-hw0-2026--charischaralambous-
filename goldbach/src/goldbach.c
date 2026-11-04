/*
 * goldbach.c - primality test and Goldbach check.
 *
 * Reads repeatedly an integer n (0 <= n <= 10^10) and a choice character:
 *   'p' -> tells whether n is prime
 *   'g' -> prints n = p + q with p <= q both prime, p as small as possible
 *
 * Numbers go up to 10^10, which does not fit in a 32-bit int (we compile
 * with -m32), so "long long" (64-bit, C99) is used everywhere.
 * Primality: trial division by 2, 3 and then 6k +/- 1 up to sqrt(n)
 * (at most ~33000 divisions for n <= 10^10), well under a second.
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define MAX_N 10000000000LL

/* Returns 1 if n is prime, 0 otherwise. */
static int is_prime(long long n)
{
    long long d;

    if (n < 2) return 0;
    if (n < 4) return 1;              /* 2 and 3 */
    if (n % 2 == 0 || n % 3 == 0) return 0;
    for (d = 5; d * d <= n; d += 6)
        if (n % d == 0 || n % (d + 2) == 0)
            return 0;
    return 1;
}

/* Smallest prime p such that n - p is also prime; 0 if none exists. */
static long long goldbach_smallest(long long n)
{
    long long p;

    for (p = 2; p <= n / 2; p++)
        if (is_prime(p) && is_prime(n - p))
            return p;
    return 0;
}

static void fail(const char *msg)
{
    fflush(stdout);
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

static void eof_exit(void)
{
    printf("EOF detected, exiting\n");
    exit(0);
}

int main(void)
{
    char token[256];
    char choice, *end;
    long long n, p;

    for (;;) {
        printf("Give me a number: ");
        fflush(stdout);
        if (scanf("%255s", token) != 1)
            eof_exit();

        errno = 0;
        n = strtoll(token, &end, 10);
        if (end == token || *end != '\0')
            fail("Invalid input: expected an integer");
        if (errno == ERANGE || n < 0 || n > MAX_N)
            fail("Number should be in the range [0, 10000000000]");

        printf("Choose how to test %lld - ('p' for prime, 'g' for goldbach) ", n);
        fflush(stdout);
        if (scanf(" %c", &choice) != 1)
            eof_exit();

        if (choice == 'p') {
            printf("%lld is %sprime\n", n, is_prime(n) ? "" : "not ");
        } else if (choice == 'g') {
            if (n <= 2 || n % 2 != 0) {
                printf("Goldbach's conjecture is applicable only to even numbers greater than 2!\n");
            } else {
                p = goldbach_smallest(n);
                if (p == 0)
                    printf("Counterexample found! Please contact us: %lld\n", n);
                else
                    printf("%lld = %lld + %lld\n", n, p, n - p);
            }
        } else {
            fail("Invalid choice: expected 'p' or 'g'");
        }
    }
    return 0;
}
