/* Graph Theory: Directed Eulerian Graphs   
   =================================================================
   Description: Template for finding directed Eulerian paths/cycles
                This is written so that it returns the 
		lexicographically first such path/cycle.
   
   Complexity:  O(M) where M is the # of edges
   -----------------------------------------------------------------
   Author:      Gilbert Lee
   Date:        Nov 10, 2003
   References:  
   -----------------------------------------------------------------
   Reliability: 2 (Problem C Catenyms - Jan 25, 2003)
                  (Problem H Play on Words - Nov 8, 2003)
   Notes:       This is the direct code for solving Catenyms. 
                Here is the underlying idea:
		1. Count the indegree/outdegree of each node.
		2. Check if the graph is connected. (done here with
		   Unionfind).  If not, then not Eulerian.
		3. A directed Euler cycle exists if for each
		   node the in degree = out degree.
		4. A directed Euler path exists if there is exactly
		   source node with outdegree = 1+in degree and one
		   sink node with indegree = 1+out degree
		5. Sort the edges in the order that you need.
		6. Do a search for a path, choosing lexicographically
		   first when possible, then build from back, 
		   splicing when necessary.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Maximum number of nodes, max number of edges */
#define MAXN 26
#define MAXM 1001

typedef struct{
  int src, dst;
  char name[21], used;
} Edge;

Edge e[MAXM];
int esize; 
int sets[MAXN], odeg[MAXN], ideg[MAXN]; 
int seq[MAXM], seqsize;
char used[MAXN];

int cmp_Edge(Edge *a, Edge *b){
  return strcmp(a->name, b->name);
}

int getRoot(int x){
  return sets[x] < 0 ? x : (sets[x] = getRoot(sets[x]));
}

void Union(int a, int b){
  int ra = getRoot(a), rb = getRoot(b);
  if(ra != rb){
    sets[ra] += sets[rb];
    sets[rb] = ra;
  }
}

void getPath(int start, int end){
  int temp[MAXM], tsize = 0, i, curr;

  for(i = 0; i < esize; i++){
    if(e[i].used || e[i].src != start) continue;
    temp[tsize++] = i;
    e[i].used = 1;
    odeg[e[i].src]--;
    curr = e[i].dst;
    break;
  }
  
  while(curr != end){
    for(i = 0; i < esize; i++){
      if(e[i].used || e[i].src != curr) continue;
      temp[tsize++] = i;
      e[i].used = 1;
      odeg[e[i].src]--;
      curr = e[i].dst;
      break;
    }
  }
  
  for(i = tsize-1; i >= 0; i--){
    if(odeg[e[temp[i]].dst]) getPath(e[temp[i]].dst, e[temp[i]].dst);
    seq[seqsize++] = temp[i];
  }
}

void init(){
  memset(sets, -1, sizeof(sets));
  memset(odeg, 0, sizeof(odeg));
  memset(ideg, 0, sizeof(ideg));
  memset(used, 0, sizeof(used));
}

int main(){
  int tnum, i, start, end, flag, count;

  for(scanf("%d", &tnum); tnum; tnum--){
    init();
    count = 0;
    
    /* Read edges, in this case: words */
    for(scanf("%d", &esize), i = 0; i < esize; i++){
      scanf(" %s", e[i].name);

      /* Src is the first letter of word, dst is last letter */
      e[i].src = e[i].name[0]-'a';
      e[i].dst = e[i].name[strlen(e[i].name)-1] - 'a';
      e[i].used = 0;

      /* Increment in/out degrees */
      odeg[e[i].src]++; ideg[e[i].dst]++;

      /* Keep track of # of vertices in use */
      if(!used[e[i].src]){
        count++;
        used[e[i].src] = 1;
      }
      if(!used[e[i].dst]){
        count++;
        used[e[i].dst] = 1;
      }
      Union(e[i].src, e[i].dst);
    }
    
    /* Sort edges lexicographically */
    qsort(e, esize, sizeof(e[0]), (void *) cmp_Edge);

    /* Check if the graph is connected */
    if(sets[getRoot(e[0].src)] != -count){
      /* This means its not connected so no Euler path*/
      printf("***\n");  
      continue;
    }
    
    /* Determine src / dst if it exists */
    /* Flag is used to mark if the graph is not Eulerian */
    flag = 0;  
    start = end = -1;
    for(i = 0; i < 26; i++){
      if(!used[i]) continue;
      if(ideg[i] == odeg[i]+1){
        if(end == -1) end = i;
        else {
          flag = 1;
          break;
        }
      } else if(odeg[i] == ideg[i]+1){
        if(start == -1) start = i;
        else {
          flag = 1;
          break;
        }
      } else if(odeg[i] != ideg[i]){
        flag = 1;
        break;
      }
    }
    if(flag){
      /* Graph is not Eulerian */
      printf("***\n");
      continue;
    } else {
      /* Graph has an Eulerian path or Eulerian cycle */
      /* Print out a eulerian path/cycle from start to end */

      if(start == -1 && end == -1){
	/* Graph has euler cycle */

        for(i = 0; i < 26; i++)
          if(used[i]) break;
        seqsize = 0;
        getPath(i, i);
        for(i = seqsize-1; i >= 0; i--)
          printf("%s%c", e[seq[i]].name, i ? '.' : '\n');
      } else {
	/* Graph has Euler path */

        seqsize = 0;
        getPath(start, end);
        for(i = seqsize-1; i >= 0; i--)
          printf("%s%c", e[seq[i]].name, i ? '.' : '\n');
      } 
    }
  }
  return 0;
}









