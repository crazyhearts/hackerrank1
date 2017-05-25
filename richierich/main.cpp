//
//  main.cpp
//  palindrome
//
//  Created by Raviraj Pinnamaraju on 16/05/17.
//  Copyright © 2017 Raviraj Pinnamaraju. All rights reserved.
//

#include <iostream>
#include <string.h>
#include <stdlib.h>

#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

int main() {
    
    int n;
    int k;
    cin >> n >> k;
    string number;
    cin >> number;
    
    // n -> length of the string
    // k -> number of elements to be replaced
    
    auto strLen = number.length();
    if (strLen != n) {
        n = strLen;
    }
    
    int startIndex = 0;
    int endIndex = n-1;
    
    // If there is only 1 number, change it to 9 if k > 0
    // else just return the number
    if (n == 1) {
        if (k > 0)
            cout << '9' << endl;
        else
            cout << number << endl;
        
        return 0;
    }
    
    auto isDivisibleBy2 = [](int n) {
        if ((n % 2) == 0)
            return true;
        else
            return false;
    };
    
    auto isPalindrome = [&]() {
        for (int i=0; i < ((n+1)/2); ++i) {
            if (number[i] == number[endIndex-i])
                continue;
            else
                return false;
        }
        
        return true;
    };
    
    auto replaceStringWith9 = [&]() {
        for(int i=0; i < n; ++i) {
            number[i] = '9';
        }
    };
    
    if (n == 1) {
        if (k > 0) {
            cout << '9' << endl;
        } else {
            cout << number << endl;
        }
        
        return 0;
    }
    
    // value of k > 1.. This changes things
    if (n <= k) {
        replaceStringWith9();
        cout << number << endl;
        return 0;
    }
    
    // n > 1.. we need to check if the string is palindrome
    if (isPalindrome() == true) {
        if (k == 1) {
            if (isDivisibleBy2(n) == false) {
                number[n/2] = '9';
                cout << number << endl;
            } else
                cout << number << endl;
            
            return 0;
        }
        
        auto newK = k;
        
        // if n is odd,
        //      k is odd -> replace the middle number with 9 first
        //      k is even -> do not touch the middle
        // if n is even
        //      k is odd -> ignore 1 ok
        //      k is even -> ignore the middle number
        bool isNOdd = !isDivisibleBy2(n);
        bool isKOdd = !isDivisibleBy2(k);
        
        if (isNOdd) {
            if (isKOdd) {
                number[(n-1)/2] = '9';
                newK = k -1; //k is even now
            }
        } else {
            if (isKOdd) {
                newK = k-1;
            }
        }
        
        for (int i=0; (i < (n+1/2)) && (newK > 0); ++i) {
            if (number[i] == '9')
                continue;
            
            number[i] = '9';
            number[endIndex-i] = '9';
            newK -=2;
        }
        
        cout << number << endl;
        return 0;
    }
    
    // Now comes the hard part. First find the number of characters we need to change
    // to make the number a palindrome
    vector<int> indices;
    {
        for(int i=0; i < ((n+1)/2); ++i) {
            if (number[i] == number[endIndex-i])
                continue;
            else
                indices.push_back(i);
        }
    };
    
    int numCharsToChange = indices.size();
    if (numCharsToChange > k) {
        cout << -1 << endl;
        return 0;
    }
    
    // First make the string a palindrome
    for_each(indices.begin(), indices.end(), [&](const int& n) {
        if (number[n] < number[endIndex-n]) {
            number[n] = number[endIndex-n];
        } else {
            number[endIndex-n] = number[n];
        }
    });
    
    auto checkIfIndexIsInList = [&](int i) {
        if (std::find(indices.begin(), indices.end(), i) != indices.end()) {
            return true;
        }
        
        return false;
    };
    
    // at this time we have already used up numCharsToChange out of k..
    // nothing will change it.. we may have some spar chane operations left
    auto newK = k;
    auto spareKs = k - numCharsToChange;
    for (int i=0; (i < ((n+1)/2)) && (newK > 0); ++i) {
        
        bool indexChanged = checkIfIndexIsInList(i);
        
        if (indexChanged) {
            newK--;
        }
        
        // we have modified the index.. so we used up 1 k
        // change both the 092282 (n= 6 k=3 numcharstochange=2 spareK =1)
        //                 292292  --> 992299 k=1 --> k =0
        
        //                 022289 (n= 6 k=3 numcharstochange=2 spareK = 1)
        //                 982289 --> 982289 k=2 --> 992299 k=0
        
        //                 0223289 (n=7 k=3 numcharstochange=2 sparek =1)
        //                 9823289 --> k=2 --> k=0 sparek =0 9923299
        
        //                 0223289 (n=7 k=4 numcharstochange=2 sparek =2)
        //                 9823289 --> k =2 --> k=0 sparek=1 -->
        if (number[i] == '9') {
            // number is already 9.. check if we changed it??
            if (indexChanged == true) {
                // do we have a spare K left?
                
            }
            continue;
        } else {
            // number is not 9.. check if we changed it??
            if (indexChanged == true) {
                // yes we changed it... do we have enough changes left??
                if (spareKs > 0) { // we have a spark k to use up
                    number[i] = '9';
                    number[endIndex-i] = '9';
                    spareKs--; // we used up a spare k
                }
            } else {
                // index has not changed.. see if we can make it max
                if (spareKs > 2) {
                    number[i] = '9';
                    number[endIndex-i] = '9';
                    spareKs -= 2;
                }
            }
        }
    }
    
    if (spareKs) {
        // we still have some spare k's
        // check if the number is odd
        if (isDivisibleBy2(n) == false) {
            number[n/2] = '9';
            spareKs--;
        }
    }
    
    cout << number << endl;
    return 0;
}
