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

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/* 1367. Linked List in Binary Tree */
bool treeNodeDFS(ListNode* head, TreeNode* root) {
    if (head == nullptr) {
        return true;
    }
    if(root == nullptr) {
        return false;
    }
    if (head->val != root->val) {
        return false;
    }
    return treeNodeDFS(head->next, root->left) || treeNodeDFS(head->next, root->right);
}

bool isSubPath(ListNode* head, TreeNode* root) {
    if (root == nullptr) {
        return false;
    }
    return treeNodeDFS(head, root) || isSubPath(head, root->left) || isSubPath(head, root->right);
}

/* 725. Split Linked List in Parts */
std::vector<ListNode*> splitListToParts(ListNode* head, int k) {
    std::vector<ListNode*> results;
    ListNode *checkNode = head;
    int count = 0;
    while(checkNode) {
        count++;
        checkNode = checkNode->next;
    }
    int quota = count / k;
    checkNode = head;
    if (quota == 0) {
        for (int i = 0; i < k; i++) {
            if (checkNode) {
                ListNode *aNode = checkNode;
                checkNode = checkNode->next;
                aNode->next = nullptr;                
                results.emplace_back(aNode);
            } else {
                results.emplace_back(nullptr);
            }
        }
    } else {
        int gap = count - quota * k;
        for (int i = 0; i < k ; i++) {
            if (gap != 0) {
                ListNode *aHead = checkNode;
                for (int j = 0; j < quota; j++) {
                    checkNode = checkNode->next;
                }
                ListNode *aNode = checkNode;
                checkNode = checkNode->next;
                aNode->next = nullptr;                
                results.emplace_back(aHead);
                gap--;
            } else {
                ListNode *aHead = checkNode;
                for (int j = 0; j < quota - 1; j++) {
                    checkNode = checkNode->next;
                }
                ListNode *aNode = checkNode;
                checkNode = checkNode->next;
                aNode->next = nullptr;                
                results.emplace_back(aHead);
            }
        }
    }
    return results;
}

/* 2326. Spiral Matrix IV */
std::vector<std::vector<int>> spiralMatrix(int m, int n, ListNode* head) {
    std::vector<std::vector<int>> results(m, std::vector<int>(n));
    int dx = -1, dy = 1;
    int row = 0, col = 0;
    int left = 0, right = n - 1, up = 1, bottom = m - 1;
    bool turn = false;

    for (int i = 0; i < m * n; i++) {
        if (head) {
            results[row][col] = head->val;
            head = head->next;
            if (!turn) {
                col += dy;
                if (col == right + 1) {
                    col = right;
                    right--;
                    turn = true;
                    dx = -dx;
                    row += dx;
                } else if (col == left - 1) {
                    col = left;
                    left++;
                    turn = true;
                    dx = -dx;
                    row += dx;
                }
            } else {
                row += dx;
                if (row == bottom + 1) {
                    row = bottom;
                    bottom--;
                    turn = false;
                    dy = -dy;
                    col += dy;
                } else if (row == up - 1) {
                    row = up;
                    up++;
                    turn = false;
                    dy = -dy;
                    col += dy;
                }
            }
        } else {
            results[row][col] = -1;
            if (!turn) {
                col += dy;
                if (col == right + 1) {
                    col = right;
                    right--;
                    turn = true;
                    dx = -dx;
                    row += dx;
                } else if (col == left - 1) {
                    col = left;
                    left++;
                    turn = true;
                    dx = -dx;
                    row += dx;
                }
            } else {
                row += dx;
                if (row == bottom + 1) {
                    row = bottom;
                    bottom--;
                    turn = false;
                    dy = -dy;
                    col += dy;
                } else if (row == up - 1) {
                    row = up;
                    up++;
                    turn = false;
                    dy = -dy;
                    col += dy;
                }
            }

        }
    }

    return results;
}

/* 2807. Insert Greatest Common Divisors in Linked List */
int calGCD(int a, int b) {
    int minV = a >= b ? b : a;
    int gcd = 1;
    for (int i = 1; i <= minV ; i++) {
        if (a % i == 0 && b % i ==0) {
            gcd = i;
        }
    } 
    return gcd;
}

ListNode* insertGreatestCommonDivisors(ListNode* head) {
    if (!head || !head->next) {
        return head;
    }
    int gcd = 1;
    ListNode *left = head, *right = head->next;
    while(right) {
        gcd = calGCD(left->val, right->val);
        ListNode *tmpNode = new ListNode(gcd, right);
        left->next = tmpNode;
        // tmpNode->next = right;
        left = right;
        right = right->next;
    }
    return head;
}

/* 2220. Minimum Bit Flips to Convert Number */
int minBitFlips(int start, int goal) {
    int count = 0;
    while(start || goal) {
        int sr = start & 1;
        int gr = goal & 1;
        if (sr != gr) {
            count++;
        }
        start >>= 1;
        goal >>= 1;
    }
    while(goal) {
        int gr = goal & 1;
        if (gr) {
            count++;
        } 
        goal >>= 1;
    }
    while(start) {
        int sr = start & 1;
        if (sr) {
            count++;
        }
        start >>= 1;
    }
    return count;
}

/* 1684. Count the Number of Consistent Strings */
int countConsistentStrings(std::string allowed, std::vector<std::string>& words) {
    int countNum = 0;
    for (auto &aWord : words) {
        bool isConsist = true;
        for (char ch : aWord) {
            if (allowed.find(ch) == std::string::npos) {
                isConsist = false;
                break;
            }
        }
        if (isConsist) {
            countNum++;
        }
    }
    return countNum;
    /*         // a faster way (use dictionary)
    vector<int>freq(26,0);
    for(char c:allowed) freq[c-'a']=1;
    int count=0;
    for(auto & word:words){
        char found=true;
        for(char &c:word){
            if(freq[c-'a']!=1) {
                found =false;
                break;
            }
        }
        if(found) count++;
    }
    */
}

/* 1310. XOR Queries of a Subarray */
/* consider prefix xor, x ^ y ^ x = y */
std::vector<int> xorQueries(std::vector<int>& arr, std::vector<std::vector<int>>& queries) {
    size_t size = arr.size();
    std::vector<int> preXor(size, 0);
    preXor[0] = arr[0];
    std::vector<int> results;
    for (size_t i = 1; i < size; i++) {
        preXor[i] = preXor[i - 1] ^ arr[i];
    }
    for (auto &q : queries) {
        if (q[0] == q[1]) {
            results.push_back(arr[q[0]]);
        } else {
            results.push_back(arr[q[0]] ^ preXor[q[0]] ^ preXor[q[1]]);
        }
    }
    return results;
}

/* 2419. Longest Subarray With Maximum Bitwise AND */
int longestSubarray(std::vector<int>& nums) {
    int maxValue = *std::max_element(nums.begin(), nums.end());
    int gap = 0;
    size_t size = nums.size();
    int left = 0, right = left;
    while(left < size) {
        if ((nums[left] & maxValue) < maxValue) {
            left++;
        } else {
            right = left;
            int andSub = nums[right];
            while(right < size && ((andSub & nums[right]) == maxValue)) {
                right++;
            }
            if (right < size) {
                int curLen = right - left;
                gap = std::max(curLen, gap);
            } else if ((andSub & nums[right - 1]) == maxValue) {
                int curLen = right - left;
                gap = std::max(curLen, gap);
            }
            left = right;
        }
    }
    return gap;
}

int main()
{
    std::cout << "2326. Spiral Matrix IV: " << std::endl;
    std::vector<int> nums = {3,0,2,6,8,1,7,9,4,2,5,5,0};
    std::cout << "Test nums = {3,0,2,6,8,1,7,9,4,2,5,5,0}\n";
    ListNode *head = new ListNode(0);
    ListNode *pivot = head;
    for (int ele : nums) {
        ListNode *aNode = new ListNode(ele);
        pivot->next = aNode;
        pivot = pivot->next;
    }
    auto res = spiralMatrix(3, 5, head->next);
    for (auto &vec : res) {
        for (auto ele : vec) {
            std::cout << ele << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Test 2419. Longest Subarray With Maximum Bitwise AND " << std::endl;
    std::vector<int> nums1 = {1,2,3,3,2,2};
    std::cout << "Answer for 1,2,3,3,2,2 : " << longestSubarray(nums1) << std::endl;

    return 0;
}