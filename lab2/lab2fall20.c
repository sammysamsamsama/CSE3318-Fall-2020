// Name: Samson Nguyen
// ID: 1001496565
//
// High-level description:
//    This program will compute the maximum interleave factor for an integer
//    sequence X such that the resulting interleaved sequence is a subsequence
//    of another integer subsequence A.
//    Take 2 integers, the length of A and the length of X, then read the
//    integers of A, -999999999, the integers of X, and -999999999.
//    Output the trace of the successes and failures of a binary search for the
//    maximum interleave factor.
//    The last line of output will provide the maximum interleave factor.
//
// compiled using this command: gcc lab2fall20.c -o lab2fall20

#include <stdio.h>
#include <stdlib.h>

// function to find a subsequence in a sequence
// inputs: int *sequence = sequence to search through
//         int *subsequence = sequence to be found
//         int sequence_length = length of sequence
//         int subsequence_length = length of sequence
//         int interleave_factor = interleave factor to apply to subsequence
// output: 1 if subsequence found, else 0
int find_subsequence(int *sequence, int* subsequence, int sequence_length,
                        int subsequence_length, int interleave_factor) {
   // for each element of the subsequence
   for (int i = 0, j = 0; i < subsequence_length; i++) {
      // find the next occurance of element in sequence
      // interleave_factor times in a row
      int occurances = 0;
      while (1) {
         if (sequence[j++] == subsequence[i]) {
            // increment occurances
            // break while loop if we found interleave_factor occurances
            if (++occurances == interleave_factor) {
               break;
            }
         } else if (j >= sequence_length) {
            return 0;
         }
      }
   }
   return 1;
}

// function to find for max interleave factor of sequence X in sequence A
// inputs: int *A = address of integer sequence A
//         int *B = address of integer sequence X
//         int A_length = length of A
//         int X_length = length of X
//         int max_subsequence_length = length of A / length of X
// output: highest interleave factor of X that could be found in A
int binary_search_subsequences(int *A, int *X, int A_length, int X_length,
                                 int max_subsequence_length) {
   int low = 0;
   int high = max_subsequence_length;
   int max_repeats = 0;
   // keep searching until we find the border of max repeats in sequence
   while (low <= high){
      int mid = (low + high) / 2;
      int subsequence_found = find_subsequence(A, X, A_length, X_length, mid);
      // if we don't find subsequence in sequence, halve search downward
      // else halve search upward
      if (subsequence_found == 0) {
         printf("low %d mid %d high %d failed\n", low, mid, high);
         high = mid - 1;
      } else {
         printf("low %d mid %d high %d passed\n", low, mid, high);
         // if we found the subsequence, check for higher max_repeats
         max_repeats = mid > max_repeats ? mid : max_repeats;
         low = mid + 1;
      }
   }
   return max_repeats;
}

int main() {
   int A_length = 0;
   int X_length = 0;
   int *A = NULL;
   int *X = NULL;
   int i, max_subsequence_length, max_interleave_factor;

   // read the lengths of A and X
   scanf("%d",&A_length);
   scanf("%d",&X_length);

   // dynamically allocate arrays
   A = malloc(A_length * sizeof(int));
   X = malloc(X_length * sizeof(int));
   max_subsequence_length = A_length / X_length;

   // read input ints into arrays
   for (i = 0; i < A_length; i++) {
      scanf("%d", &A[i]);
   }
   scanf("%d", &i);
   // sequence inputs should be seperated by this value
   if (i != -999999999) {
      printf("Something's gone wrong reading A.\n");
      exit(1);
   }
   for (i = 0; i < X_length; i++) {
      scanf("%d", &X[i]);
   }
   scanf("%d", &i);
   if (i != -999999999) {
      printf("Something's gone wrong reading X.\n");
      exit(1);
   }

   // binary search for border of max interleave factor that can be found
   //    in sequence and save index of border as max_interleave_factor
   max_interleave_factor = binary_search_subsequences(A, X, A_length, X_length,
                                                         max_subsequence_length);

   printf("Maximum repeats is %d\n", max_interleave_factor);

   return 0;
}
