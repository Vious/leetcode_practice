#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <set>
#include <algorithm>
#include <queue>
#include <numeric>
#include <bitset>
#include <cmath>
#include <sstream>

/* 1497. Check If Array Pairs Are Divisible by k */
bool canArrange(std::vector<int>& arr, int k) {
    size_t size = arr.size();
    // if (size % 2 != 0) {
    //     return false;
    // }
    size_t count = 0;
    std::vector<size_t> frequencyMap(k, 0);
    for (size_t i = 0; i < size; i++) {
        int mod = (arr[i] % k + k) % k; /* deal with negative values */
        frequencyMap[mod]++;
    }
    for (size_t i = 1; i < k / 2 + 1; i++) {
        if (frequencyMap[i] != frequencyMap[k - i]) {
            return false;
        }
    }
    if (frequencyMap[0] % 2 != 0) {
        return false;
    }
    return true;
}

/* 1331. Rank Transform of an Array */
std::vector<int> arrayRankTransform(std::vector<int>& arr) {
    int size = arr.size();
    std::map<int, int> hashMap;
    std::vector<int> result(size, 0);
    std::vector<int> sortedArr(arr);
    std::sort(sortedArr.begin(), sortedArr.end());
    int count = 1;
    for (int i = 0; i < size; i++) {
        if (i > 0 && sortedArr[i] > sortedArr[i - 1]) {
            count++;
        }
        hashMap[sortedArr[i]] = count;
    }
    for (int i = 0; i < size; i++) {
        result[i] = hashMap[arr[i]];
    }
    return result;
}


/*  */

int main()
{
    std::cout << "1497. Check If Array Pairs Are Divisible by k: " << std::endl;
    std::vector<int> arr1 = {1,2,3,4,5,10,6,7,8,9};
    std::cout << canArrange(arr1, 5) << std::endl;
    std::vector<int> arr2 = {1,2,3,4,5,6};
    std::cout << canArrange(arr2, 7) << std::endl;
    std::cout << canArrange(arr2, 10) << std::endl;
    std::vector<int> arr3 = {-1,-1,-1,-1,2,2,-2,-2};
    std::cout << canArrange(arr3, 3) << std::endl;
    

    return 0;
}