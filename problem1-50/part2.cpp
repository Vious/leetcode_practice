#include <iostream>
#include <vector>
#include <map>
#include <string>

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
        res = res * 10 + decimalDig;
        if (res > INT32_MAX || res < INT32_MIN) {
            return 0;
        }
        x /= 10;
    }
    return res;
}

int main() 
{
    std::cout << "Testing for Problem 6. Zigzag Conversion: " << std::endl;
    std::cout << "Testing \"PAYPALISHIRING\" of 3 rows: " << convert("PAYPALISHIRING", 3) << std::endl; 

    std::cout << "Testing for Problem 7. Reverse Integer: " << std::endl;
    std::cout << "123: " << reverse(123) << " -123: " << reverse(-123) << " 120:" << reverse(120) << std::endl;

    return 0;
}