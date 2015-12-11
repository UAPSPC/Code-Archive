/* Search: Binary Search Template
   =================================================================
   Description: Given a sorted array A of size n, it tried to find
                an item x in the array using binary search.  The
		function returns non-zero if x is found, and zero
		otherwise.  Furthermore, if it is found, then
		A[index] = x.  If it is not found, then index is the 
		place x should be inserted into A.

		ie. A[i] <= x              for 0 <= i < index
		            x < A[i]       for index <= i < n

	        There is also an insert routine here that will
		insert the element into the right place after the
		array has been reallocated (if necessary) to
		store n+1 elements

   Complexity:
   -----------------------------------------------------------------
   Author:      Howard Cheng
   Date:        Nov 10, 2003
   References:  
   -----------------------------------------------------------------
   Reliability: 0
   Notes:       This routine is written for integer arrays, but can
                be adapted to other types by changing the
                comparison operator.
*/

#include <stdio.h>

int bin_search(int *A, int n, int x, int *index){
   int low, up, mid;

   if (n <= 0 || x < A[0]) {
      *index = 0;
      return 0;
   }
   if (A[n-1] < x) {
      *index = n;
      return 0;
   }
   if (x == A[n-1]) {
      *index = n-1;
      return 1;
   }
   for(low = 0, up = n-1; low + 1 < up;){
     mid = (low+up)/2;
     if (A[mid] <= x)
       low = mid;
     else 
       up = mid;
   }
   if (A[low] == x) {
      *index = low;
      return 1;
   } else {
      *index = up;
      return 0;
   }
}

void insert(int *A, int n, int x, int index){
   int i;
   for (i = n-1; i >= index+1; i--)
     A[i] = A[i-1];
   A[index] = x;
}


int main(void){
   int A[10000];
   int n, i, x, index;
   
   n = 0;
   while (scanf("%d", &x) == 1 && n < 10000) {
     if (!bin_search(A, n, x, &index)) {
       n++;
       insert(A, n, x, index);
     }
     printf("List:");
     for (i = 0; i < n; i++) {
       printf(" %d", A[i]);
       if (i == index) printf("*");
     }
     printf("\n");
   }
   return 0;
}
