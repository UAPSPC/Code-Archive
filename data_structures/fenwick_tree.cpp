/*  Author: Ian DeHaan, 2019

    Fenwick Tree data structure. Allows to update index and get sum
    of array up to index in logarithmic time.

    Complexity: O(n log n) to build the tree
                O(log n) to update a value
                O(log n) to get sum 

    Reliability:
    fenwick - Open Kattis
    moviecollection - Open Kattis
*/
#include<iostream>
#include<vector>
using namespace std;

struct FenwickTree {
    int n;
    vector<long long> ftree;

    // Gets sum up to and INCLUDING index
    long long sum(int index) {
        long long out = 0;
        index++;
        while (index > 0) {
            out += ftree[index];
            index -= index & (-index);
        }
        return out;
    }

    // Adds delta to value at index
    void update(int index, long long delta) {
        index++;
        while (index <= n) {
            ftree[index] += delta;
            index += index & (-index);
        }
    }

    // Call this first or the rest won't like you
    void construct(long long vals[], int n) {
        this->n = n;
        ftree.resize(n+1);
        for (int i = 1; i <= n; i++) {
            ftree[i] = 0;
        }

        for (int i = 0; i < n; i++) {
            update(i, vals[i]);
        }
    }
};