/* Suffix Array Solver
   =================================================================
   Description: Builds a suffix array from a string of N characters.
				Also includes other functions to make it easier to use
				the results for the suffix array.

   Complexity:  O(n log n)
   -----------------------------------------------------------------
   Author:      Morgan Redshaw
   Date:        October 2017
   References:  Competitive Programming 3
   -----------------------------------------------------------------
   Reliability: Circular Sorting: UVa 719
				StringMatching: UVa 1254
				ComputeLCP: HackerRank String Simularity
   Notes:       - Defaults to non-circular sorting, but there are TODOS indicating
					what would need to be changed.
				- Uses radix sort to ensure takes N logN time.
				- Call constructSA before calling StringMatching or ComputeLCP
				- Unless doing circular sorting, add an ending character, especially if have multiple strings.
				- The ending character can be the same if you don't use the LCP array without any changes,
					but if you are trying to find the longest match then they may need to be different.
				- Using \0 as the ending character is convenient for printing out, especially if storing
					multiple strings.
				- T can also be a string, but a cstring is easier for StringMatching function.
*/
#include <iostream>
#include <cstring>

using namespace std;

typedef pair<int, int> ii;

const int MaxN = 100010;
char T[MaxN];
int N;
// Index from sorted suffix i to position in string
int SA[MaxN], tempSA[MaxN];
// Rank of i in T. Used by SA[j] = i.
int RA[MaxN], tempRA[MaxN];

// Must be as large as MaxN, since possible for every character
// to have a unique rank.
int c[MaxN];
void radixSort(int k) { // O(n), numbers up to N, any chars
	int i, maxi = max(300, N);
	memset(c, 0, sizeof c);
	for (i = 0; i < N; ++i) {// Integer rank freq
		// TODO: Mod instead if circular sorting.
		int index = i + k < N ? RA[i + k] : 0;
		c[index]++;
	}
	int sum = 0;
	for (i = 0; i < maxi; ++i) {
		int t = c[i];
		c[i] = sum;
		sum += t;
	}
	for (i = 0; i < N; ++i) { // Shuffle sufix array.
		// TODO: Mod if circular sorting.
		int indexToRA = SA[i] + k;
		int indexToC = indexToRA < N ? RA[indexToRA] : 0;
		tempSA[c[indexToC]++] = SA[i];
	}
	for (i = 0; i < N; ++i)
		SA[i] = tempSA[i];
}

void constructSA() {
	int i;
	for (i = 0; i < N; ++i)
		RA[i] = T[i];
	for (i = 0; i < N; ++i)
		SA[i] = i;
	for (int k = 1; k < N; k <<= 1) {
		radixSort(k); // Sort based on value k indicies after
		radixSort(0); // Sort based on current value of self (stable)
		int r = 0; // Rank, starting from 0.
		tempRA[SA[0]] = r;
		for (i = 1; i < N; ++i) {
			tempRA[SA[i]] =
				// Note that second condition will only be tried with non-circular sorting if SAs + k < N.
				// Otherwise they would already be different, due to sorting to the end.
				(RA[SA[i]] == RA[SA[i - 1]] && RA[(SA[i] +k)%N] == RA[(SA[i - 1] + k)%N]) ? r : ++r;
		}
		for (i = 0; i < N; ++i)
			RA[i] = tempRA[i];
		if (RA[SA[N - 1]] == N - 1)
			break; // All have unique ranks.
	}
}


// Returns inclusive set of all matches of P[0:pLen], indexed by SA of N, O(|P|log|N|).
// So matches are the strings T[SA[i]] for i in the set of matches returned.
// Returns -1, -1 if no matches exist.
char P[MaxN];
ii StringMatching(int pLen) {
	// Find lower bound on suffixes that match.
	int low = 0, high = N-1;
	while (low < high) {
		int mid = (low + high) / 2;
		int result = strncmp(T + SA[mid], P, pLen);
		if (result >= 0) high = mid; // At most this guy
		else low = mid + 1; // Can't include this guy
	}
	if (strncmp(T + SA[low], P, pLen) != 0)
		return ii(-1, -1); // Doesn't match.
	ii ans; ans.first = low;
	
	low = 0; high = N - 1;
	// Find upper bound on suffixes that match.
	while (low < high) {
		int mid = (low + high) / 2;
		int result = strncmp(T + SA[mid], P, pLen);
		if (result > 0) high = mid; // Too far into the array.
		else low = mid + 1; // Try only including above this guy.
	}
	if (strncmp(T + SA[high], P, pLen) != 0) // Went one past the end.
		--high;
	ans.second = high;
	return ans;
}

// LCP[i] = prefix size that SA[i] has in common with SA[i - 1];
int LCP[MaxN];
void ComputeLCP() {
	int Phi[MaxN], PLCP[MaxN], i;
	Phi[SA[0]] = -1;
	for (i = 1; i < N; ++i)
		Phi[SA[i]] = SA[i-1];
	int L = 0;
	for (i = 0; i < N; ++i) {
		if (Phi[i] == -1) { PLCP[i] = 0; continue; }	
		while (T[i + L] == T[Phi[i] + L]) ++L;
		PLCP[i] = L;
		L = max(L - 1, 0);
	}
	for (int i = 0; i < N; ++i)
		LCP[i] = PLCP[SA[i]];
}

// Will print out the sum, for the suffix starting from i,
// of its prefix with all other suffixes.
// Just an example of what you can use LCP for.
// Is O(n) to compute.
void PrintOutCommonPrefixForSuffix() {
	int suffix;
	scanf("%d", &suffix);
	
	int initialIndexInSA;
	for (int i = 0; ; ++i)
		if (SA[i] == suffix) {
			initialIndexInSA = i;
			break;
		}
	
	long long totalMatch = 0;
		
	int currentMatch = N - suffix;
	// Update current match before changing the index
	for (int i = initialIndexInSA; i >= 0 && currentMatch > 0; currentMatch = min(currentMatch, LCP[i]), --i) {
		totalMatch += currentMatch;
	}
	
	currentMatch = N - suffix;
	// Now go the other way
	for (int i = initialIndexInSA + 1; i < N && (currentMatch = min(currentMatch, LCP[i])); ++i) {
		totalMatch += currentMatch;
	}
	printf("Match is: %lld\n", totalMatch);
}

// Example of what can be done with 
void PrintOutMatchingRangeForString() {
	scanf("%s", P);
	int pLen = strlen(P);
	ii res = StringMatching(pLen);
	if (res.first == -1) {
		printf("No complete matches\n");
	} else {
		printf("Matches found:\n");
		for (int i = res.first; i <= res.second; ++i) {
			printf("    %s\n", T + SA[i]);
		}
	}
}

int main() {
	while (scanf("%s\n", T)) {
		N = strlen(T);
		
		constructSA();
		ComputeLCP();
		
		char command;
		while (scanf(" %c", &command), command != 'q') {
			switch (command) {
			case 'p':
				PrintOutCommonPrefixForSuffix();
				break;
				
			case 'm':
				PrintOutMatchingRangeForString();
				break;
			
			default:
				printf("Command not recognized, just p, m, or q are recognized\n");
			}
		}
	}
}