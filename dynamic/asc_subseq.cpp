/* Dynamic Programming: Longest Ascending Subsequence
   =================================================================
   Description: Given an array of numbers, construct creates the length 
                of the longest strictly ascending subsequence
                Calling reconstruct_print(numbers, endOfLongest) will print
                out the last occurance of the longest ascending subsequence.
                Difference to asc_subseq.c is that this is shorter code,
                written for C++ and easier to copy/understand
   
   Complexity:  O(n log n)
   -----------------------------------------------------------------
   Author:      Morgan Redshaw
   Date:        June 9, 2016
   References:  Competitive Programming 3, source code given in chapter 3
                in their online sample
   -----------------------------------------------------------------
   Reliability: Longest strictly increasing:
                    UVa 10534 - Wavio Sequence
                    UVa 11456 - Trainsorting
                    UVa 497 - Strategic Defense Initiative
                    UVa 481 - What Goes Up
                Longest increasing:
                    UVa 231 - Testing the CATCHER
   Notes:       If you want to do the same things with descending
                subsequences, just reverse the array before calling
                the routines -> best to read the list in reverse if
                possible.
                To allow an ascending sequence (allowing duplicates)
                edit at Optional point in construct.
                The function construct will completely reset the data,
                so it can be called multiple times.
*/

#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

// End is the index in numbers of last number for longest subsequence
int endOfLongest;

// L is the current list. Is not actually a valid increasing subsequence, but using L_id and P, can reconstruct from it
vector<int> L;

// L_id[i] stores the index for the number stored in L at position i. Only necessary if you need to reconstruct the sequence
vector<int> L_id;
// P is what index came before a number. Only necessary if you need to reconstruct the sequence
vector<int> P;

// Returns length of longest
int construct(const vector<int>& numbers)
{
    L.clear();
    L_id.clear();
    P.clear();
    int lengthOfIncreasing = 0;
    endOfLongest = 0;
    
    for (int i = 0; i < numbers.size(); ++i)
    {
        const int num = numbers[i];

        // Optional:
        // Change to upper_bound for not strictly increasing (or allow duplicate numbers)
        int pos = lower_bound(L.begin(), L.end(), num) - L.begin();
        if (pos == L.size())
        {
            L.push_back(num);
            L_id.push_back(i);
        }
        else
        {
            L[pos] = num;
            L_id[pos] = i;
        }

        P.push_back(pos ? L_id[pos - 1] : -1);

        // >= to output the latest one
        if (pos + 1 >= lengthOfIncreasing) {
            lengthOfIncreasing = pos + 1;
            endOfLongest = i;
        }
    }
    
    return lengthOfIncreasing;
}

// End is the index in numbers of last number for wanted subsequence
// To get solution, will normally want to do reconstruct_print(endOfLatest)
// To get the length of longest, use lengthOfIncreasing
void reconstruct_print(const vector<int>& numbers, int end) {
    int x = end;
    stack<int> s;
    for (; P[x] >= 0; x = P[x])
        s.push(numbers[x]);
    
    s.push(numbers[x]);
    for (; !s.empty(); s.pop())
        cout << s.top() << '\n';
}

int main()
{
    int n;

    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];
    int result = construct(nums);

    cout << "Size of longest subsequence: " << result << '\n';
    reconstruct_print(nums, endOfLatest);
    return 0;
}