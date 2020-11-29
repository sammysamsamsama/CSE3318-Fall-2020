// Name: Samson Nguyen
// ID: 1001496565
//
// High-level description:
//    This program will compute subset sums for all possible cardinalities
//    of the input.
//    Take 2 ints, length of input and target value, then read input ints.
//    Calculate all possible subset sums and output the table and traceback
//    for each cardinality.
//
// compiled using this command: gcc lab3fall20.c -o lab3fall20

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

    for (position = 9; n > 1 && position >= 1; position--) {
        printf("position %d n %d\n", position, n);
        // reset C
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
        // accumulate
        for (i = 1; i < 10; i++) {
            C[i] += C[i - 1];
        }
        // shift array right
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
        for (i = 0, j = 0; i < n; i++) {
            if ((S[i] / div) % 10 == index) {
                S[j++] = S[i];
            }
        }
        n = C[index + 1] - C[index];
    }
    printf("position %d n %d\n", position, n);
    printf("MSD 10 radix: The value with rank %d is %d\n", k1, S[0]);

    free(S);
    return 0;
}
