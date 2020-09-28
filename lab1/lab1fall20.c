// Name: Samson Nguyen
// ID: 1001496565
//
// Take a sequence of n integers as input and remove the duplicates, then output
// the number of unique integers and the list of unique integers in the same
// order they were inputted.
//
// compiled using this command: gcc lab1fall20.c -o lab1fall20

#include <stdio.h>
#include <stdlib.h>

typedef struct Pair {
  int value;
  int index;
} Pair;

// function to compare pairs by value for use in qsort
// inputs: Pair* a, Pair* b
// output: a->value - b->value
int compare_values(const void *a, const void *b) {
  return (*(Pair*)a).value - (*(Pair*)b).value;
}

// function to compare pairs by indices for use in qsort
// inputs: Pair* a, Pair* b
// output: a->index - b->index
int compare_indices(const void *a, const void *b) {
  return (*(Pair*)a).index - (*(Pair*)b).index;
}

// function to find the unique values of a sorted array of pairs,
// put them at the beginning, and return the number of unique values.
// inputs: array = address of first Pair of array,
//         n = number of Pairs in the array
// output: int of unique values in array
int remove_duplicates(Pair *array, int n) {
   int i, j;

   // the first value cannot be a duplicate
   // loop from 1 to n-1 and copy first occurances to j++ index
   for(i = 1, j = 1; i < n; i++) {
     if(array[i].value == array[i - 1].value) {
       continue;
     } else {
       array[j++] = array[i];
     }
   }
   return j;
}

int main() {
  int n = 0;
  Pair *array = NULL;
  int i, j;
  int input = 0;

  // Read n, the number of integers to read
  scanf("%d", &n);
  array = malloc(n * sizeof(Pair));

  // Read input sequence into Pair structs
  for(i = 0; i < n; i++) {
    scanf("%d", &input);
    array[i].value = input;
    array[i].index = i;
  }

  // Sort pairs ascending by value in a stable fashion
  qsort(array, n, sizeof(Pair), compare_values);

  // Using one pass over the sorted result,
  // remove any occurances beyond the first one for a key
  // save the number of unique pairs as j
  j = remove_duplicates(array, n);

  // Sort j pairs ascending by index
  qsort(array, j, sizeof(Pair), compare_indices);

  // Output the number of unique values followed by those values
  printf("%d\n", j);
  for (i = 0; i < j; i++) {
      printf("%d\n", array[i].value);
  }
  free(array);
  return 0;
}
