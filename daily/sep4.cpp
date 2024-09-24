#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <queue>
#include <numeric>
#include <bitset>
#include <cmath>
#include <sstream>

/* 440. K-th Smallest in Lexicographical Order */
int countSteps(int n, long prefix1, long prefix2) {
    int steps = 0;
    while (prefix1 <= n) {
        steps += std::min((long)(n + 1), prefix2) - prefix1;
        prefix1 *= 10;
        prefix2 *= 10;
    }
    return steps;
}

int findKthNumber(int n, int k) {
    int curr = 1;
    k--;

    while (k > 0) {
        int step = countSteps(n, curr, curr + 1);
        if (step <= k) {
            curr++;
            k -= step;
        } else {
            curr *= 10;
            k--;
        }
    }

    return curr;
}

/* 2707. Extra Characters in a String */
int minExtraChar(std::string s, std::vector<std::string>& dictionary) {
    int size = s.length();
    std::unordered_set<std::string> dictSet(dictionary.begin(), dictionary.end());

    std::vector<int> dp(size + 1, 0);

    for (int i = size - 1; i >=0; i--) {
        dp[i] = dp[i + 1] + 1;
        for (int j = i; j < size; j++) {
            std::string curStr = s.substr(i, j - i + 1);
            if (dictSet.count(curStr)) {
                dp[i] = std::min(dp[i], dp[j + 1]);
            }
        }
    }
    return dp[0];
}

/* 3043. Find the Length of the Longest Common Prefix */
int longestCommonPrefix(std::vector<int>& arr1, std::vector<int>& arr2) {
    if (arr1.size() == 0 || arr2.size() == 0) {
        return 0;
    }
    std::unordered_set<int> lcpMap;
    for (int val : arr1) {
        while(!lcpMap.count(val) && val > 0) {
            lcpMap.insert(val);
            val /= 10;
        }
    }
    int res = 0;
    for (int val : arr2) {
        while(!lcpMap.count(val) && val > 0) {
            val /= 10;
        }
        if (val > 0) {
            res = std::max(res, static_cast<int>(log10(val)) + 1);
        }
    }
    return res;

}

int main()
{
    std::cout << "3043. Find the Length of the Longest Common Prefix\n";
    std::vector<int> arr1 = {1, 10, 100}, arr2 = {1000};
    std::cout << "Lcp of arr1 = {1, 10, 100}, arr2 = {1000}: " << longestCommonPrefix(arr1, arr2) << std::endl;

    return 0;
}