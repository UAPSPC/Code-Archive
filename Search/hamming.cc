/* Search: Hamming Code search template / (Independent set)
   =================================================================
   Description: This is a template for finding a maximum set of
                binary code words that are all have at least a 
		Hamming distance of d between them.
   
		Also has some ideas for finding maximum clique

   Complexity:  O(exponential)
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        March 14, 2003
   References:  
   -----------------------------------------------------------------
   Reliability: 0
   Notes:       
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

#define MAXN 9
#define MAXS 21
int n, d;

int bitcount(int x){
  int c = 0;
  while(x){
    c++;
    x &= x-1;
  }
  return c;
}

int dist(int x, int y){
  return bitcount(x^y);
}

void PrintBin(int x){
  int i;
  for(i = 0; i < n; i++)
    printf("%d", x & (1<<i) ? 1 : 0);
  printf("\n");
}

int best;
int curr[MAXS];
int bestset[MAXS];

vector<int> pos[MAXS];
vector<int> adj[1<<MAXN];

void MaxClique(int k){
  int i; vector<int>::iterator it, it2;

  if(k > best){
    best = k;
    for(i = 0; i < k; i++) bestset[i] = curr[i];
  }
  for(it = pos[k].begin(); it != pos[k].end(); ++it){
    curr[k] = *it;
    pos[k+1].clear();
    insert_iterator<vector<int> > next(pos[k+1], pos[k+1].begin());
    it2 = it; it2++;
    set_intersection(it2, pos[k].end(),
	      adj[*it].begin(), adj[*it].end(),
	      next);
    if(k+1+(int)pos[k+1].size() <= best) continue;
    MaxClique(k+1);
  }
}

int main(){
  int i, j;
  
  while(scanf("%d %d", &n, &d) == 2){

    for(i = 0; i < MAXS; i++) pos[i].clear();
    
    for(i = 0; i < 1<<n; i++){
      adj[i].clear();
      for(j = i+1; j < 1<<n; j++){
	if(dist(i,j) >= d)
	  adj[i].push_back(j);
      }
    }
    best = -1;
    curr[0] = 0;
    pos[1] = adj[0];
    MaxClique(1);
    printf("Maximum code length: %d\n", best);
    for(i = 0; i < best; i++)
      PrintBin(bestset[i]);
  }
  return 0;
}
