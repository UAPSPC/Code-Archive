// Calculate the suffix array for a string. Includes code for
// LCP and how to code up string matching range.
typedef pair<int, int> ii;

const int MaxN = 100010;
char T[MaxN];
int N;
int SA[MaxN], tempSA[MaxN]; // SA[i] = index of suffix i in string
int RA[MaxN], tempRA[MaxN]; // Rank of i in T
int c[MaxN];
void radixSort(int k) {
    int i, maxi = max(300, N);
    memset(c, 0, sizeof c);
    for (i = 0; i < N; ++i)
        c[i + k < N ? RA[i + k] : 0]++; // TODO: Mod for circular
    int sum = 0;
    for (i = 0; i < maxi; ++i) {
        int t = c[i]; c[i] = sum; sum += t;
    }
    for (i = 0; i < N; ++i) {
        // TODO: Mod for circular
        int indexToC = SA[i] + k < N ? RA[SA[i] + k] : 0; 
        tempSA[c[indexToC]++] = SA[i];
    }
    for (i = 0; i < N; ++i) SA[i] = tempSA[i];
}

void constructSA() {
    int i;
    for (i = 0; i < N; ++i) RA[i] = T[i];
    for (i = 0; i < N; ++i) SA[i] = i;
    for (int k = 1; k < N; k <<= 1) {
        radixSort(k); radixSort(0);
        int r = 0;
        tempRA[SA[0]] = r;
        for (i = 1; i < N; ++i) {
            tempRA[SA[i]] =
                (RA[SA[i]] == RA[SA[i - 1]] && 
                 RA[(SA[i] + k) %N] == RA[(SA[i-1] + k) %N]) ? r : ++r;
        }
        for (i = 0; i < N; ++i) RA[i] = tempRA[i];
        if (RA[SA[N - 1]] == N - 1) break;
    }
}

// Returns inclusive set of all matches of P[0:pLen] into SA.
// Returns -1, -1 if no matches exist.
char P[MaxN];
ii StringMatching(int pLen) { // O(|P|log|N|)
    int low = 0, high = N-1;
    while (low < high) {
        int mid = (low + high) / 2;
        int result = strncmp(T + SA[mid], P, pLen);
        if (result >= 0) high = mid;
        else low = mid + 1;
    }
    if (strncmp(T + SA[low], P, pLen) != 0) return ii(-1, -1);
    ii ans; ans.first = low;
    low = 0; high = N - 1;
    while (low < high) {
        int mid = (low + high) / 2;
        int result = strncmp(T + SA[mid], P, pLen);
        if (result > 0) high = mid;
        else low = mid + 1;
    }
    if (strncmp(T + SA[high], P, pLen) != 0) --high;
    ans.second = high;
    return ans;
}


int LCP[MaxN]; // LCP[i] = prefix size that SA[i] has in common with SA[i-1]
// Last character MUST be different than all other characters!
void ComputeLCP() {
    int Phi[MaxN], PLCP[MaxN], i, L;
    Phi[SA[0]] = -1;
    for (i = 1; i < N; ++i) Phi[SA[i]] = SA[i-1];
    for (L = i = 0; i < N; ++i) {
        if (Phi[i] == -1) { PLCP[i] = 0; continue; }    
        while (T[i + L] == T[Phi[i] + L]) ++L;
        PLCP[i] = L;
        L = max(L - 1, 0);
    }
    for (int i = 0; i < N; ++i) LCP[i] = PLCP[SA[i]];
}
