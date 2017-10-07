/* Manacher's Algorithm (Find All Palindromes)
   =================================================================
   Description: Given a string S, will find the max size of the palindrome
                centered at each character.

   Complexity:  O(n) where n is number of characters in string
   -----------------------------------------------------------------
   Author:      Morgan Redshaw
   Date:        September 2017
   References:  HackerRank Post
   -----------------------------------------------------------------
   Reliability: 1 (UVa 11475)
   Notes:       - Padding isn't necessary, but makes the code + calculations
                far easier.
                - Also allows finding palindromes that don't have a center
*/
#include <iostream>

using namespace std;

const int MaxC = 200010;

// By not setting the even indicies, defaults to \0, which will never be in string
char word[MaxC];
// Ensure is > 2 * MaxN.
int P[MaxC];

int CalculateAllPalindromes(const string& orig) {
    // Originally from https://www.hackerrank.com/topics/manachers-algorithm
    int wordSize = orig.size() * 2 + 1;
    int C = 0, R = -1;
    
    // Odd indicies contain the characters in original string
    for (int i = 0; i < orig.size(); ++i) {
        word[i * 2 + 1] = orig[i];
    }
    
    for (int i = 0; i < wordSize; ++i) {
        int rad = 0;
        // Can skip over everything covered by R - is identical to
        // mirrored position of i w.r.t C (pos 2C - i)
        if (i < R) {
            rad = min(P[2 * C - i], R - i);
        }
        
        // Try to extend.
        while (i + rad < wordSize && i - rad >= 0
               && word[i - rad] == word[i + rad]) {
            rad++;
        }
        --rad;
        P[i] = rad;
        
        if (i + rad > R) {
            C = i;
            R = i + rad;
        }
    }
}

int main() {
    string orig;
    while (cin >> orig) {
        int PSize = CalculateAllPalindromes(orig);
        
        // Ignore i = 0, PSize - 1 due to them being edge cases
        for (int i = 1; i < PSize - 1; ++i) {
            int characterSpot = i / 2;
            cout << "For spot " << characterSpot << (i % 2 == 0 ? " (before character):\n" : " (character):\n");
            if (P[i] == 0) {
                cout << "   No palindrome between characters\n";
                continue;
            }
            
            int palindromSize = P[i];
            int lenToStart = P[i] / 2;
            // Only skipped characters have their character spot rounded up. So lenToEnd is < lenToStart.
            int lenToEnd = lenToStart - (i % 2 == 0);
            
            cout << "   Palindrome size " << palindromSize << " start " << (characterSpot - lenToStart) << " end " << (characterSpot + lenToEnd) << '\n';
        }
    }
}