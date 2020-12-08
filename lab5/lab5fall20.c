// Name: Samson Nguyen
// ID: 1001496565
//
// High-level description:
//
//    Input:
//
// compiled using this command: gcc lab5fall20.c -o lab5fall20 -lm

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct vertex {
   int x, y;
} vertex;

// all from here to main() reference
// http://ranger.uta.edu/~weems/NOTES3318/kruskal.c

int numVertices,numEdges;
int *parent,*weight,numTrees;

struct edge {
  int head, tail;
  double weight;
};
typedef struct edge edgeType;
edgeType *edgeTab;

int find(int x)
// Find root of tree containing x
{
   int i,j,root;

   // Find root
   for (i=x;
        parent[i]!=i;
        i=parent[i]);
   root=i;
   // path compression - make all nodes on path
   // point directly at the root
   for (i=x;
        parent[i]!=i;
        j=parent[i],parent[i]=root,i=j);
return root;
}

void unionFunc(int i,int j)
// i and j must be roots!
{
   if (weight[i]>weight[j])
   {
     parent[j]=i;
     weight[i]+=weight[j];
   }
   else
   {
     parent[i]=j;
     weight[j]+=weight[i];
   }
   numTrees--;
}

int weightAscending(const void* xin, const void* yin)
// Used in call to qsort()
{
   edgeType *x,*y;

   x=(edgeType*) xin;
   y=(edgeType*) yin;
   if (x->weight > y->weight) {
      return 1;
   } else if (x->weight < y->weight) {
      return -1;
   } else {
      return 0;
   }
}

int main() {
   // input: n, the number of points
   //        n lines of 2 ints as x and y coords
   int i, j, k, x, y, root1, root2;
   double MSTweight = 0;
   vertex *inputVertices;
   scanf("%d", &numVertices);
   inputVertices = (vertex *)malloc(numVertices * sizeof(vertex));
   numEdges = (numVertices * (numVertices - 1))/2;
   edgeTab = (edgeType *)malloc(numEdges * sizeof(edgeType));
   parent = (int *)malloc(numVertices * sizeof(int));
   weight = (int *)malloc(numVertices * sizeof(int));
   for (i = 0; i < numVertices; i++) {
      scanf("%d", &x);
      scanf("%d", &y);
      inputVertices[i].x = x;
      inputVertices[i].y = y;
      printf("%d %d %d\n", i, x, y);
   }
   for (i = 0, k = 0; i < numVertices; i++) {
      for (j = i + 1; j < numVertices; j++) {
         edgeTab[k].head = i;
         edgeTab[k].tail = j;
         int hx = inputVertices[i].x;
         int hy = inputVertices[i].y;
         int tx = inputVertices[j].x;
         int ty = inputVertices[j].y;
         edgeTab[k++].weight = sqrt((tx-hx) * (tx-hx) + (ty-hy) * (ty-hy));
      }
   }
   // from http://ranger.uta.edu/~weems/NOTES3318/kruskal.c
   for (i=0;i<numVertices;i++)
   {
     parent[i]=i;
     weight[i]=1;
   }
   numTrees=numVertices;
   qsort(edgeTab,numEdges,sizeof(edgeType),weightAscending);
   int included = 0;
   for (i=0;i<numEdges && included < numVertices - 1;i++)
   {
     root1=find(edgeTab[i].tail);
     root2=find(edgeTab[i].head);
     if (root1==root2)
       printf("%d %d %0.3f discarded\n",edgeTab[i].tail,edgeTab[i].head,edgeTab[i].weight);
     else
     {
       printf("%d %d %0.3f included\n",edgeTab[i].tail,edgeTab[i].head,edgeTab[i].weight);
       MSTweight+=edgeTab[i].weight;
       unionFunc(root1,root2);
       included++;
     }
   }
   if (numTrees!=1)
     printf("MST does not exist\n");
   printf("Sum of weights of spanning edges %0.3f\n", MSTweight);

   free(inputVertices);
   free(edgeTab);
   free(parent);
   free(weight);
   return 0;
}
