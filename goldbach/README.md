# Goldbach

Program that tests primality (`p`) and finds the Goldbach decomposition (`g`).

## Notes
- Compiled with `-m32`, where `int` is 32-bit, so all numbers are `long long` (limit is 10^10).
- Input number is read as a string and parsed with `strtoll`, so `banana`, `12abc` and
  overflowing values are detected reliably (`scanf("%d")` would not do this safely).
- `is_prime`: trial division by 2, 3, then 6k±1 up to sqrt(n) (~33k steps worst case).
- `g`: tries p = 2, 3, 4, ... and stops at the first p where both p and n-p are prime,
  so p is the smallest possible one. Typically found within a few hundred tries.
- Errors go to stderr with exit code 1; EOF prints `EOF detected, exiting` with exit code 0.
- Source: standard trial-division algorithm, no external code used.
