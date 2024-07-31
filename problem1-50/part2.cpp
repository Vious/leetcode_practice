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
    long long result = 0;
    while(startIdx < size && isdigit(s[startIdx])) {
        result = result * 10 + (s[startIdx] - '0');
        if (result > INT32_MAX && posSign) {
            return INT32_MAX;
        }
        // here should be -result < INT32_MIN
        if (-result < INT32_MIN && !posSign) {
            return INT32_MIN;
        } 
        startIdx++;
    }
    result = !posSign ? -result: result;
    return static_cast<int> (result);

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
    
    return 0;
}