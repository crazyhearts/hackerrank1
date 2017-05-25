
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


string isValid(string s) {
    std::map<char, int> charCount;
    
    for(int i=0; i <s.length(); i++) {
        if (charCount.find((char)s[i]) != charCount.end()) {
            int count = charCount[(char)s[i]];
            charCount[(char)s[i]]++;
        } else {
            charCount.insert(std::make_pair((char)s[i], 1));
        }
    }
    
    int max = -1, numCharsWithDifferentCount = 0;
    for (map<char, int>::iterator it = charCount.begin(); it != charCount.end(); it++) {
        int count = it->second;
        char c = it->first;
        
        if (max == -1) {
            max = count;
            continue;
        }
        
        int maxCountDiff = max - count;
        
        if (maxCountDiff == 0)
            continue;
        
        if ((maxCountDiff > 1) || (maxCountDiff < -1)) {
            // Obviously the difference is more.. dont be in a hurry to dismiss
            if (count == 1) {
                ++numCharsWithDifferentCount;
            } else
                // well, we need more than 1 chage..
                return "NO";
        }
        if ((maxCountDiff == 1) || (maxCountDiff == -1)) {
            if (++numCharsWithDifferentCount > 1) {
                // There are more than 2 chars with count > max
                return "NO";
            }
        }
    }
    
    return "YES";
}


int main() {
    string s;
    cin >> s;
    string result = isValid(s);
    cout << result << endl;
    return 0;
}