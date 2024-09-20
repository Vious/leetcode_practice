#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <queue>
#include <numeric>
#include <bitset>

/* Sept, 1st */
/* 2022. Convert 1D Array Into 2D Array */
std::vector<std::vector<int>> construct2DArray(std::vector<int>& original, int m, int n) {
    size_t size = original.size();
    // long long int multiRes = m * n;
    if (size != m * n) {
        return {};
    }
    std::vector<std::vector<int>> results(m, std::vector<int>(n));
    size_t row, col;
    row = col = 0;
    for (int i = 0; i < size; i++) {
        row = i / n;
        col = i % n;
        results[row][col] = original[i];
    }
    return results;
}

/* Sept, 2nd */
/* 1894. Find the Student that Will Replace the Chalk */
int chalkReplacer(std::vector<int>& chalk, int k) {
    int size = chalk.size();
    if (size == 1) {
        return 0;
    }
    int retIndx, sum = 0;
    for (int i = 0; i < size; i++) {
        sum += chalk[i];
        if (sum > k) {
            return i;
        }
    }
    k %= sum;
    sum = 0;
    for (int i = 0; i < size; i++) {
        sum += chalk[i];
        if (sum > k) {
            return i;
        }
    }

    return retIndx;
}

/* Sept, 3rd */
/* 1945. Sum of Digits of String After Convert */
int getLucky(std::string s, int k) {
    int size = s.size();
    int sum = 0, value = 0;
    for (int i = 0; i < size; i++) {
        int tmpValue = s[i] - 'a' + 1;
        while(tmpValue) {
            value += (tmpValue % 10);
            tmpValue /= 10;
        }
    }
    k--;
    while(k) {
        if (value < 10) {
            return value;
        }
        while(value) {
            sum += (value % 10);
            value /= 10;
        }
        value = sum;
        sum = 0;
        k--;
    }
    return value;
}

/* Sept, 4th */
/* 874. Walking Robot Simulation */
int robotSim(std::vector<int>& commands, std::vector<std::vector<int>>& obstacles) {
    int size = commands.size();
    if (size == 0) {
        return 0;
    }
    int row, col;
    row = col = 0;
    int dx = 0, dy = 1, direction = 0;
    int maxDistance = 0;
    int obstSize = obstacles.size();
    std::unordered_map<int, std::vector<int>> directionMap = {{0, {0, 1}}, {1, {1, 0}}, {2, {0, -1}}, {3, {-1, 0}}};
    // use set to find, searches faster.
    std::set<std::pair<int,int>> obstSet;
    for(const auto &it : obstacles){
        obstSet.insert({it[0],it[1]});
    }

    for (int i = 0; i < size; i++) {
        if (commands[i] == -1) {
            direction = (direction + 1) % 4;
            dx = directionMap[direction][0];
            dy = directionMap[direction][1];
        } else if (commands[i] == -2) {
            direction = (direction + 3) % 4;
            dx = directionMap[direction][0];
            dy = directionMap[direction][1];
        } else {
            int count = commands[i];
            while(count > 0) {
                int tmpRow = row + dx;
                int tmpCol = col + dy;
                if (obstSet.find({tmpRow, tmpCol}) != obstSet.end() ){
                    break;
                }
                row = tmpRow;
                col = tmpCol;
                maxDistance = std::max(maxDistance, row * row + col * col);
                count--;
            }
        }
    }

    return maxDistance;
}

/* 2028. Find Missing Observations */
std::vector<int> missingRolls(std::vector<int>& rolls, int mean, int n) {
    int sum = std::accumulate(rolls.begin(), rolls.end(), 0);
    int size = rolls.size();
    if (mean * (size + n) > (sum + 6 * n)) {
        return {};
    }
    std::vector<int> results;
    int gap = mean * (size + n) - sum;
    if (gap < n) {
        return {};
    } else if (gap == n) {
        for (int i = 0; i < n; i++) {
            results.push_back(1);
        }
        return results;
    }
    int gapMean = gap / n;
    while(gap > 0) {
        if (results.size() < n) {
            results.push_back(gapMean);
            gap -= gapMean;
        } else {
            int idx = 0;
            while(gap > 0) {
                results[idx] += 1;
                idx = (idx + 1) % results.size();
                gap--;
            }
            break;
        }
    }

    return results;
}

/* 3217. Delete Nodes From Linked List Present in Array */
 struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
 };

ListNode* modifiedList(std::vector<int>& nums, ListNode* head) {
    int size = nums.size();
    if (size == 0) {
        return head;
    }
    // std::unordered_map<int, int> hashMap;
    std::bitset<100001> needRM;
    for (int i = 0; i < size; i++) {
        needRM.set(nums[i]);
    }
    ListNode *left = head, *right = head->next;
    while(right) {
        if (needRM[right->val]) {
            right = right->next;
            left->next = right;
        } else {
            left = left->next;
            right = right->next;
        }
    }
    if (needRM[head->val]) {
        head = head->next;
    }
    return head;
}

int main()
{
    std::cout << "2022. Convert 1D Array Into 2D Array: " << std::endl;
    std::vector<int> original = {1,2,3,4};
    auto res = construct2DArray(original, 2, 2);
    for (auto &vec : res) {
        for (int value : vec) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
    // std::cout << (4e4) * (4e4) << std::endl;
    // std::cout << __LONG_LONG_MAX__ << " " << INT32_MAX;

    std::cout << "1894. Find the Student that Will Replace the Chalk: " << std::endl;
    std::vector<int> chalk = {5,1,5};
    std::cout << "Result index : " << chalkReplacer(chalk, 22) << std::endl;

    std::cout << "1945. Sum of Digits of String After Convert: " << std::endl;
    std::string str = "vbyytoijnbgtyrjlsc";
    std::cout << "str = \"vbyytoijnbgtyrjlsc\", k = 2 : " << getLucky(str, 2) << std::endl;

    std::cout << "874. Walking Robot Simulation : " << std::endl;
    std::vector<int> commands = {4,-1,4,-2,4};
    std::vector<std::vector<int>> obstacles = {{2,4}};
    std::cout << "Ec distance: " << robotSim(commands, obstacles) << std::endl;

    // std::vector<int> commands = {6,-1,-1,6};
    // std::vector<std::vector<int>> obstacles = {};
    // std::cout << "Ec distance: " << robotSim(commands, obstacles) << std::endl;

    std::cout << "2028. Find Missing Observations" << std::endl;
    std::vector<int> rolls = {6,1,5,2};
    std::cout << "[6,1,5,2], mean = 4, n = 4: " << std::endl;
    auto res3 = missingRolls(rolls, 4, 4);
    for (auto ele : res3) {
        std::cout <<ele << " ";
    }

    return 0;
}