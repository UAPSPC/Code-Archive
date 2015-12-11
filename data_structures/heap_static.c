/* Data Structures: Heap implementation - with fixed max heap size
   =================================================================
   Description: Heap Data Structure
   
   Complexity:  Let N be the size of the heap:
                Insertion: O(lg N)
		Removal:   O(lg N)
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        Sept 15, 2002
   References:  "Algorithms in C" by Robert Sedgewick
   -----------------------------------------------------------------
   Reliability: 0
   Notes:       
*/

#include <stdio.h>

#define MAXN  50000

typedef int ET;           /* Defines the type of elements in heap */

typedef struct{
  ET a[MAXN];             /* Array storing heap elements */
  int n;                  /* Number of elements in heap  */
  int (*cmp)(ET,ET);      /* Comparator function pointer */
} Heap;

int cmp_asc(ET a, ET b){ return a - b; }
int cmp_des(ET a, ET b){ return b - a; }

void initHeap(Heap *h, int (*cmp)(ET, ET)){
  h->n = 0;
  h->cmp = cmp;
}

void downheap(Heap *h, int k){
  ET v = h->a[k];
  int j;

  while(k <= h->n/2){
    j = k+k;
    if(j < h->n && h->cmp(h->a[j], h->a[j+1]) > 0) j++;
    if(h->cmp(v,h->a[j]) <= 0) break;
    h->a[k] = h->a[j];
    k = j;
  }
  h->a[k] = v;
}

void upheap(Heap *h, int k){
  ET v = h->a[k];

  while(k > 1 && h->cmp(v, h->a[k/2]) < 0)
    h->a[k] = h->a[k/=2]; 
  h->a[k] = v;
}

ET replace(Heap *h, ET v){
  h->a[0] = v;
  downheap(h, 0);
  return h->a[0];
}

ET removetop(Heap *h){
  ET v = h->a[1];
  h->a[1] = h->a[h->n--];
  downheap(h, 1);
  return v;
}

void insert(Heap *h, ET v){
  h->a[++h->n] = v;
  upheap(h, h->n);
}

int main(){
  Heap minheap, maxheap;
  ET x;
  int i;

  initHeap(&minheap, cmp_asc);
  initHeap(&maxheap, cmp_des);
  
  while(scanf("%d", &x) == 1 && x){
    insert(&minheap, x);
    insert(&maxheap, x);
  }

  printf("Min heap:\n");
  while(minheap.n){
    printf("%d ", removetop(&minheap));
  }
  printf("\n");

  printf("Max heap:\n");
  while(maxheap.n){
    printf("%d ", removetop(&maxheap));
  }
  printf("\n");
  return 0;
}
