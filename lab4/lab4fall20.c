// Name: Samson Nguyen
// ID: 1001496565
//
// High-level description:
//    This program will compute the kth smallest number in a sequence of n ints
//    in the range 0...999,999,999.
//    Input: n and k, 1 <= k <= n <= 10000000,
//    n ints in the indicated range, one per line. Duplicate inputs possible.
//
// compiled using this command: gcc lab4fall20.c -o lab4fall20

#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;  // input length
    int k, k1;  // target kth smallest int
    int *S = NULL; // input sequence
    int C[10] = {0}; // counting array
    int i, j, position, index, temp;

    // read n and k
    scanf("%d", &n);
    scanf("%d", &k);
    k1 = k;

    // dynamically allocate S
    S = (int *) malloc(n * sizeof(int));

    // read input sequence
    for (i = 0; i < n; i++) {
        scanf("%d", &S[i]);
    }

    // counting sort for each of the 9 digit positions
    for (position = 9; n > 1 && position >= 1; position--) {
        printf("position %d n %d\n", position, n);
        // reset C for counting sort
        for (i = 0; i < 10; i++) {
            C[i] = 0;
        }
        // div = 10^position
        int div = 1;
        for (i = 1; i < position; i++) {
            div *= 10;
        }
        // for each int in S, count occurrences
        for (i = 0; i < n; i++) {
            temp = S[i];
            temp = (temp / div) % 10;
            C[temp]++;
        }
        // accumulate [1, 2, 3, 4] -> [1, 3, 6, 10]
        for (i = 1; i < 10; i++) {
            C[i] += C[i - 1];
        }
        // shift array right [1, 3, 6, 10] -> [0, 1, 3, 6]
        for (i = 9; i > 0; i--) {
            C[i] = C[i - 1];
        }
        C[0] = 0;
        // find first count > k - 1
        // discard all below and above that digit
        for (i = 0; i < 10; i++) {
            if (C[i] > k - 1) {
                index = i - 1;
                k -= C[i - 1];
                break;
            }
        }
        // move digits in the bin around k to the start of S
        for (i = 0, j = 0; i < n; i++) {
            if ((S[i] / div) % 10 == index) {
                S[j++] = S[i];
            }
        }
        // adjust n to account for discarded ints
        n = C[index + 1] - C[index];
    }
    printf("position %d n %d\n", position, n);
    printf("MSD 10 radix: The value with rank %d is %d\n", k1, S[0]);

    free(S);
    return 0;
}
