#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <queue>
#include <numeric>
#include <bitset>
#include <cmath>
#include <sstream>


/* 1371. Find the Longest Substring Containing Vowels in Even Counts */
int findTheLongestSubstring(std::string s) {
    int prefixXor = 0;
    int maxNum = 0;

    int vowelsMap[26] = {0};
    vowelsMap['a' - 'a'] = 1;
    vowelsMap['e' - 'a'] = 2;
    vowelsMap['i' - 'a'] = 4;
    vowelsMap['o' - 'a'] = 8;
    vowelsMap['u' - 'a'] = 16;

    std::vector<int> preMap(32, -1);
    int size = s.size();
    for (int i = 0; i < size; i++) {
        prefixXor ^= vowelsMap[s[i] - 'a'];
        if (preMap[prefixXor] == -1 and prefixXor != 0) {
            preMap[prefixXor] = i;
        }
        maxNum = std::max(maxNum, i - preMap[prefixXor]);
    } 

    return maxNum;
}

/* 539. Minimum Time Difference */
int calDiffMinutes(std::string a, std::string b) {
    int hr1 = std::stoi(a.substr(0, 2)), hr2 = std::stoi(b.substr(0, 2));
    int mn1 = std::stoi(a.substr(3, 2)), mn2 = std::stoi(b.substr(3, 2));

    return std::min((hr2 * 60 + mn2 - hr1 * 60 - mn1), ((hr1 + 24) * 60 - hr2 * 60 + mn1 - mn2) );
}

int findMinDifference(std::vector<std::string>& timePoints) {
    std::sort(timePoints.begin(), timePoints.end());
    int size = timePoints.size();
    int minDiff = calDiffMinutes(timePoints[0], timePoints[size - 1]);
    for (int i = 0; i < size - 1; i++) {
        int tmpDiff = calDiffMinutes(timePoints[i], timePoints[i + 1]);
        if (tmpDiff < minDiff) {
            minDiff = tmpDiff;
        }
    }
    return minDiff;
}

/* 884. Uncommon Words from Two Sentences */
std::vector<std::string> uncommonFromSentences(std::string s1, std::string s2) {
    std::unordered_map<std::string, int> wordsMap;
    std::stringstream ss(s1);
    std::string word;
    while(getline(ss, word, ' ')) {
        wordsMap[word]++;
    }
    std::stringstream ss2(s2);
    while(getline(ss2, word, ' ')) {
        wordsMap[word]++;
    }

    std::vector<std::string> results;
    for (auto iter = wordsMap.begin(); iter != wordsMap.end(); iter++) {
        if (iter->second < 2) {
            results.emplace_back(iter->first);
        } 
    }
    return results;

}

/* 179. Largest Number */
bool compareStr(const std::string &a, const std::string &b) {
    return a + b > b + a;    
}

std::string largestNumber(std::vector<int>& nums) {
    std::string res = "";
    std::vector<std::string> strs;
    int size = nums.size();
    for (int i = 0; i < size; i++) {
        strs.emplace_back(std::to_string(nums[i]));
    }
    // std::sort(strs.begin(), strs.end(), [this](const std::string &a, const std::string &b) {return a + b > b + a;});
    std::sort(strs.begin(), strs.end(), [](const std::string &a, const std::string &b) {return a + b > b + a;});
    if (strs[0] == "0") return "0";
    for (int i = 0; i < size; i++) {
        res += strs[i];
    }
    return res;

}

/* 241. Different Ways to Add Parentheses */
std::vector<int> diffWaysToCompute(std::string expression) {
    std::vector<int> results;

    if (expression.size() == 0) {
        return results;
    }
    if (expression.size() == 1) {
        results.emplace_back(std::stoi(expression));
        return results;
    }
    if (expression.size() == 2 && std::isdigit(expression[0])) {
        results.emplace_back(std::stoi(expression));
        return results;
    }
    int size = expression.size();
    for (int i = 0; i < size; i++) {
        char curChar = expression[i];

        if (std::isdigit(curChar)) {
            continue;
        }

        std::vector<int> leftPart = diffWaysToCompute(expression.substr(0, i));

        std::vector<int> rightPart = diffWaysToCompute(expression.substr(i + 1));

        for (int leftValue : leftPart) {
            for (int rightValue : rightPart) {
                int tmpCal = 0;
                switch (curChar)
                {
                case '+':
                    /* code */
                    tmpCal = leftValue + rightValue;
                    break;
                case '-':
                    tmpCal = leftValue - rightValue;
                    break;
                case '*':
                    tmpCal = leftValue * rightValue;
                    break;
                default:
                    break;
                }
                results.push_back(tmpCal);
            }
        }

    }

    return results;
}

/* 214. Shortest Palindrome */
std::vector<int> buildPrefixTable(const std::string &str) {
    std::vector<int> prefixTable(str.size(), 0);
    int length = 0, size = str.size();

    for (int i = 1; i < size; i++) {
        while(length > 0 && str[i] != str[length] ) {
            length = prefixTable[length - 1];
        }
        if (str[i] == str[length]) {
            length++;
        }
        prefixTable[i] = length;
    }

    return prefixTable;
}

std::string shortestPalindrome(std::string s) {
    std::string revStr = std::string(s.rbegin(), s.rend());

    std::string combStr = s + "#" + revStr;

    auto prefixTable = buildPrefixTable(combStr);

    int length = prefixTable[combStr.size() - 1];

    std::string suffix = revStr.substr(0, s.size() - length);

    return suffix + s;
}

int main()
{
    std::cout << "1371. Find the Longest Substring Containing Vowels in Even Counts " << std::endl;
    std::string str = "23:59";
    std::cout << str.substr(0, 2) << " ," << str.substr(3, 2) << std::endl;

    std::vector<std::string> strs = {"9", "123" ,"211", "311"};
    std::sort(strs.begin(), strs.end(), std::greater<std::string>());

    for (auto &str : strs) {
        std::cout << str << " ";
    }
    std::cout << std::endl;

    std::cout << "Test 241. Different Ways to Add Parentheses: " << std::endl;
    std::cout << "Test expression = \"2-1-1\": " <<  std::endl;
    auto res = diffWaysToCompute("2-1-1");
    for (auto ele: res) {
        std::cout << ele << " ";
    }
    std::cout << std::endl;

    std::cout << "Test 214. Shortest Palindrome: " << std::endl;


    return 0;
}