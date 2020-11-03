// Name: Samson Nguyen
// ID: 1001496565
//
// High-level description:
//
//
// compiled using this command: gcc lab3fall20.c -o lab3fall20

#include <stdio.h>
#include <stdlib.h>

// subset sum function from http://ranger.uta.edu/~weems/NOTES3318/subsetSum.c
void subsetSum(int n, int m, int *S, int *C) {
   int i, j, potentialSum, cardinality, leftover;

   // Initialize table for DP
   // For each potential sum, determine the smallest index such
   // that its input value is in a subset to achieve that sum.
   for (cardinality = 1; cardinality <= n; cardinality++) {
      for (potentialSum = 1; potentialSum <= m; potentialSum ++) {
         for (j = 1; j <= n; j++) {
            leftover = potentialSum-S[j];
            if (cardinality == 1) {
               if (leftover == 0) {
                  break;
               }
            } else {
               if (leftover >= 0 && *(C + ((m + 1) * (cardinality - 1)) + leftover) < j) {
                  break;
               }
            }
         }
         *(C + ((m + 1) * cardinality) + potentialSum) = j;
      }
      *(C + ((m + 1) * cardinality)) = n + 1;
   }
}

// write output function from http://ranger.uta.edu/~weems/NOTES3318/subsetSum.c
void writeOutput(int n, int m, int *S, int *C) {
   int i, cardinality, j;

   // Output the input set
   printf("m is %d\n", m);
   printf("  i   S\n");
   printf("-------\n");
   for (i=0;i<=n;i++)
      printf("%3d %3d\n",i,S[i]);

   // Output the DP table
   printf("  i   card  C\n");
   printf("----------------\n");
   for (i = 0; i <= m; i++) {
      for (cardinality = 1; cardinality <= n; cardinality++) {
         printf("%3d %3d %3d\n", i, cardinality, *(C + (m + 1) * cardinality + i));
      }
   }

   // Output the backtrace
   for (cardinality = 1; cardinality <= n; cardinality++) {
      if (*(C + (m + 1) * (cardinality + 1) - 1) == n + 1) {
         printf("No solution with %d elements\n", cardinality);
      } else {
         printf("Solution with %d elements\n", cardinality);
         printf("   i   S\n");
         printf("--------\n");
         int trace_card = cardinality;
         for (i = m; i > 0; i -= S[*(C + (m + 1) * (trace_card) + i)], trace_card--) {
            int index = *(C + (m + 1) * (trace_card) + i);
            printf("%3d %3d\n", index, S[index]);
         }
      }
   }
   // if (C[m]==n+1) {
   //    printf("No solution\n");
   // } else {
   //    printf("Solution\n");
   //    printf("  i   S\n");
   //    printf("-------\n");
   //    for (i=m;i>0;i-=S[C[i]])
   //       printf("%3d %3d\n",C[i],S[C[i]]);
   // }
}

int main() {
   int n;   // input length
   int m;   // target value
   int *S = NULL; // input set
   int *C = NULL; // cost table
   int i;

   // read n and m
   scanf("%d",&n);
   scanf("%d",&m);

   // dynamically allocate arrays
   S = (int *)calloc((n + 1), sizeof(int));
   C = (int *)calloc((n + 1) * (m + 1), sizeof(int));

   // read input set
   S[0] = 0;
   for (i = 1; i <= n; i++) {
      scanf("%d", &S[i]);
   }

   subsetSum(n, m, S, C);
   writeOutput(n, m, S, C);

   free(S);
   free(C);
   return 0;
}
