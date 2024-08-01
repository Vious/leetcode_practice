#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cctype>

/* Problem 6. Zigzag Conversion */
std::string convert(std::string s, int numRows) {
    int size = s.size();
    if(size <= numRows || numRows == 1) {
        return s;
    }
    std::string results = "";
    std::map<int, std::string> rowMap;
    int upOrDown;
    int rowIdx = 0;
    for (int i = 0; i < size; i++) {
        rowMap[rowIdx] += s[i];
        if (rowIdx == 0) {
            upOrDown = 1;
        } else if (rowIdx == numRows - 1) {
            upOrDown = -1;
        }
        rowIdx += upOrDown;
        
    }
    std::map<int, std::string>::iterator iter;
    for (iter = rowMap.begin(); iter != rowMap.end(); iter++) {
        results += iter->second;
    }
    return results;
}

/* Problem 7. Reverse Integer */
int reverse(int x) {
    int res = 0;
    while(x) {
        int decimalDig = x % 10;
        if (res > INT32_MAX / 10 || res < INT32_MIN / 10) {
            return 0;
        }
        res = res * 10 + decimalDig;
        x /= 10;
    }
    return res;
}

/* Problem 8. String to Integer (atoi) */
int myAtoi(std::string s) {
    int size = s.size();
    if (size == 0) {
        return 0;
    }
    int startIdx = 0;
    while(startIdx < size && s[startIdx] == ' ') {
        startIdx++;
    }
    if (startIdx == size) {
        return 0;
    }
    bool posSign = true;
    if (s[startIdx] == '+') {
        startIdx++;
    } else if (s[startIdx] == '-') {
        posSign = false;
        startIdx++;
    }
    // long long result = 0;
    // while(startIdx < size && isdigit(s[startIdx])) {
    //     result = result * 10 + (s[startIdx] - '0');
    //     if (result > INT32_MAX && posSign) {
    //         return INT32_MAX;
    //     }
    //     // here should be -result < INT32_MIN
    //     if (-result < INT32_MIN && !posSign) {
    //         return INT32_MIN;
    //     } 
    //     startIdx++;
    // }
    // result = !posSign ? -result: result;
    // return static_cast<int> (result);

    // use only int type
    int result = 0;
    while(startIdx < size && isdigit(s[startIdx])) {
        int digit = s[startIdx] - '0';
        if (result > INT32_MAX/10 || (result == INT32_MAX/10 && digit > 7)) {
            return posSign? INT32_MAX: INT32_MIN;
        }
        result = result * 10 + digit;
        startIdx++;
    }
    result = !posSign ? -result: result;
    return result;

}

/* Problem 9. Palindrome Number */
bool isPalindrome(int x) {
    if (x < 0) {
        return false;
    }
    if (x < 10) {
        return true;
    }
    /* solution 1, use vector to store digits */
    // std::vector<int> digitsVector;
    
    // while (x) {
    //     digitsVector.push_back(x % 10);
    //     x /= 10;
    // }
    // int size = digitsVector.size();
    // for (int i = 0; i < size/2 ; i++) {
    //     if (digitsVector[i] != digitsVector[size - i - 1]) {
    //         return false;
    //     }
    // }
    // return true;

    /* solution 2, do the reverse */
    long long int original = x;
    long long int reverse = 0;
    while (original) {
        reverse = reverse * 10 + original % 10;
        original /= 10;
    }
    if (x == reverse) {
        return true;
    } else {
        return false;
    }

    return true;
}

/* Problem 10. Regular Expression Matching */
bool isMatch(std::string s, std::string p) {
    if (p.empty()) {
        return s.empty();
    }
    // /* first solution, recursive, might exceed time limits for leetcode server on case: s = "aaaaaaaaaaaaaaaaaaa", p = "a*a*a*a*a*a*a*a*a*b" or other similar cases */
    // bool curMatch = (!s.empty() && (s[0] == p[0] || p[0] == '.'));
    // int pLen = p.size();
    // if (pLen >= 2 && p[1] == '*') {
    //     return curMatch && isMatch(s.substr(1), p) \
    //         || isMatch(s, p.substr(2));
    // } else {
    //     return (curMatch && isMatch(s.substr(1), p.substr(1)));
    // }

    // return false;
    // second solution, DP
    int m = s.size(), n = p.size();
    // remember to initialize to false
    std::vector<std::vector<bool>> dp(m + 1, std::vector<bool>(n + 1, false));
    dp[0][0] = true;
    /* several cases to deal with:
    dp[i][j] == true if following conditions hold:
    1. if p[j - 1] != '*', then dp[i-1][j-1] == true && s[i - 1] matches p[j - 1]
    2. 
     */


}

int main() 
{
    std::cout << "Testing for Problem 6. Zigzag Conversion: " << std::endl;
    std::cout << "Testing \"PAYPALISHIRING\" of 3 rows: " << convert("PAYPALISHIRING", 3) << std::endl; 

    std::cout << "Testing for Problem 7. Reverse Integer: " << std::endl;
    std::cout << "123: " << reverse(123) << " -123: " << reverse(-123) << " 120:" << reverse(120) << std::endl;


    std::cout << "Testing for Problem 8. String to Integer (atoi): " << std::endl;
    std::cout << "Testing " << "1337c0d3 :" << myAtoi("1337c0d3") << std::endl;
    std::cout << "Testing " << "0-1 :" << myAtoi("0-1") << std::endl;
    std::cout << "Testing " << "   -042 :" << myAtoi("   -042") << std::endl;
    std::cout << "Testing " << "words and 987 :" << myAtoi("words and 987") << std::endl;
    std::cout << "Testing " << " -91283472332:" << myAtoi("-91283472332") << std::endl;
    

    std::cout << "Testing for Problem 9. Palindrome Number: " << std::endl;
    std::cout << "Testing " << "121 :" << isPalindrome(121) << std::endl;
    std::cout << "Testing " << "1221 :" << isPalindrome(1221) << std::endl;
    std::cout << "Testing " << "-121 :" << isPalindrome(-121) << std::endl;
    std::cout << "Testing " << "120 :" << isPalindrome(120) << std::endl;

    std::cout << "Testing for Problem 10. Regular Expression Matching: " << std::endl;
    std::cout << "Testing for s = \"aa\", p = \"a\" : " << isMatch("aa", "a")  << std::endl;
    std::cout << "Testing for s = \"aa\", p = \".a\" : " << isMatch("aa", "a.")  << std::endl;
    std::cout << "Testing for s = \"aa\", p = \"a*\" : " << isMatch("aa", "a*")  << std::endl;
    std::cout << "Testing for s = \"aaaaaaaaaaaaaaaaaaa\", p = \"a*a*a*a*a*a*a*a*a*b\" : " << isMatch("aaaaaaaaaaaaaaaaaaa", "a*a*a*a*a*a*a*a*a*b")  << std::endl;


    return 0;
}