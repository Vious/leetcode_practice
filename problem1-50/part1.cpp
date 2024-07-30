#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <unordered_set>
#include <cmath>
 
// problem 1. Two Sum
std::vector<int> twoSum(std::vector<int>& nums, int target) {
    std::vector<int> results;
    int size = nums.size();
    std::unordered_map<int, int> hashMap;
    for (int i = 0; i < size; i++) {
        int remained = target - nums[i];
        if(hashMap.find(nums[i]) != hashMap.end()) {
            results.push_back(hashMap[nums[i]]);
            results.push_back(i);
            // what even faster is to use {} to return vectors rather than push_back
            return results;
        }
        hashMap[remained] = i;
    }

    return results;

}

// Problem 2. Add Two Numbers
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    if (l1 == nullptr || l2 == nullptr) {
        return l1 == nullptr ? l2 : l1;
    }
    ListNode *result;
    ListNode *tmpL1 = l1, *tmpL2 = l2;
    bool l1HasNext = (tmpL1->next != nullptr);
    bool l2HasNext = (tmpL2->next != nullptr);

    int val = (tmpL1->val + tmpL2->val);
    int carryF = val / 10;
    
    result = new ListNode(val % 10);
    ListNode *tmp = new ListNode(carryF);
    ((carryF || (l1HasNext || l2HasNext)) && (result->next = tmp));
    while(l1HasNext && l2HasNext) {
        tmpL1 = tmpL1->next;
        tmpL2 = tmpL2->next;
        int val = (tmpL1->val + tmpL2->val) + tmp->val;
        tmp->val = val % 10;
        carryF = val / 10;

        ListNode *loopNext = new ListNode(carryF);
        l1HasNext = (tmpL1->next != nullptr);
        l2HasNext = (tmpL2->next != nullptr);
        ((carryF || (l1HasNext || l2HasNext)) && (tmp->next = loopNext));
        tmp = tmp->next;

    }

    while(l1HasNext) {
        tmpL1 = tmpL1->next;
        int val = (tmpL1->val) + tmp->val;
        tmp->val = val % 10;
        carryF = val / 10;
        ListNode *loopNext = new ListNode(carryF);
        l1HasNext = (tmpL1->next != nullptr);
        ((carryF || (l1HasNext)) && (tmp->next = loopNext));
        tmp = tmp->next;
    }

    while(l2HasNext) {
        tmpL2 = tmpL2->next;
        int val = (tmpL2->val) + tmp->val;
        tmp->val = val % 10;
        carryF = val / 10;
        ListNode *loopNext = new ListNode(carryF);
        l2HasNext = (tmpL2->next != nullptr);
        ((carryF || (l2HasNext)) && (tmp->next = loopNext));
        tmp = tmp->next;
    }

    return result;

}

/* Problem 3. longest-substring-without-repeating-characters
 */
int lengthOfLongestSubstring(std::string s) {
    if (s.length() == 0 || s.length() == 1) {
        return s.length();
    }
    int maxLen = 1;
    // std::string tmpStr = s.substr(0, 1);
    int length = s.length();
    int left = 0, right;
    // std::unordered_map<char, int> hashMap;
    std::unordered_set<char> substrSet;
    substrSet.insert(s[left]);
    for (right = 1; right < length; right++) {
        if (substrSet.count(s[right]) == 0) {
            substrSet.insert(s[right]);
            maxLen = (maxLen > (right - left + 1)) ? maxLen : (right - left + 1);
        } else {
            while(substrSet.count(s[right]) != 0) {
                substrSet.erase(s[left]);
                left++;
            }
            substrSet.insert(s[right]);
        }
    }

    return maxLen;

}

/* Problem 4. Median of Two Sorted Arrays */
double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
    int size1 = nums1.size(), size2 = nums2.size();
    // vector empty check
    if (size1 == 0) {
        if (size2 == 0) {
            return 0.0;
        } else {
            // check even or odd
            return (size2 % 2) == 0 ? ((double)nums2[size2 / 2] + nums2[size2 / 2 - 1]) / 2 : (double) nums2[size2 / 2];
        }
    } else {
        if (size2 == 0) {
            return (size1 % 2) == 0 ? ((double)nums1[size1 / 2] + nums1[size1 / 2 - 1]) / 2 : (double) nums1[size1 / 2];
        }
    }
    bool evenFlag = ((size1 + size2) % 2 ) == 0;
    double res = 0.0;
    // check for general cases, using binary search
    if (size1 > size2) {
        int indexLeft = 0,  indexR= size2;
        int  midNum = (size1 + size2 + 1) / 2;
        while (indexLeft <= indexR) {
             int mid = (indexLeft + indexR) / 2;
             int gap = midNum - mid;
             int left1 = (mid > 0) ? nums2[mid - 1] : INT32_MIN; // in nums2
             int left2 = (gap > 0) ? nums1[gap - 1] : INT32_MIN; // in nums1
             int right1 = (mid < size2) ? nums2[mid] : INT32_MAX;
             int right2 = (gap < size1) ? nums1[gap] : INT32_MAX;

             if (left1 <= right2 && left2 <= right1) {
                return evenFlag ? ((double)std::max(left1, left2) + std::min(right1, right2)) / 2.0 : std::max(left1, left2);
             } else if (left1 > right2) {
                indexR = mid - 1;
             } else {
                indexLeft = mid + 1;
             }

        }
    } else {
        int indexLeft = 0,  indexR= size1;
        int  midNum = (size1 + size2 + 1) / 2;
        while (indexLeft <= indexR) {
             int mid = (indexLeft + indexR) / 2;
             int gap = midNum - mid;
             int left1 = (mid > 0) ? nums1[mid - 1] : INT32_MIN; // in nums1
             int left2 = (gap > 0) ? nums2[gap - 1] : INT32_MIN; // in nums2
             int right1 = (mid < size1) ? nums1[mid] : INT32_MAX;
             int right2 = (gap < size2) ? nums2[gap] : INT32_MAX;

             if (left1 <= right2 && left2 <= right1) {
                return evenFlag ? ((double)std::max(left1, left2) + std::min(right1, right2)) / 2.0 : std::max(left1, left2);
             } else if (left1 > right2) {
                indexR = mid - 1;
             } else {
                indexLeft = mid + 1;
             }

        }

    }

    return res;
}

/* Problem 5. Longest Palindromic Substring */
std::string longestPalindrome(std::string s) {
    int size = s.size();
    if (size <= 1) {
        return s;
    } 

    int lenNoMiddle = 0;
    int lenWithMiddle = 0;
    int startIdx = 0, endIdx = 0;
    for (int i = 0; i < size; i++) {
        // check for pattern like "bab", with central character
        int left = i, right = i;
        while(left >= 0 && right <= size - 1 && s[left] == s[right]) {
            left--;
            right++;
        }
        lenWithMiddle = right - left - 1; // to be more precise, right - left + 1 - 2
        if (lenWithMiddle > endIdx - startIdx + 1) {
            startIdx = left + 1;
            endIdx = right - 1;
        }

        // check for pattern like "baab", no central character
        left = i, right = i + 1;
        while(left >= 0 && right <= size - 1 && s[left] == s[right]) {
            left--;
            right++;
        }
        lenNoMiddle = right - left - 1;
        if (lenNoMiddle > endIdx - startIdx + 1) {
            startIdx = left + 1;
            endIdx = right - 1;
        }
    }

    return s.substr(startIdx, endIdx - startIdx + 1);
}

int main()
{
    std::cout << "Testing Two Sum:" << std::endl;
    std::vector<int> aInput;
    aInput.push_back(2);
    aInput.push_back(7);
    aInput.push_back(11);
    aInput.push_back(15);

    auto results = twoSum(aInput, 9);
    std::cout << "Input are: ";
    for (auto value : aInput) {
        std::cout << value << ", ";
    }
    std::cout << std::endl;
    std::cout << "Answers are: ";
    for (auto value : results) {
        std::cout << value << ", ";
    }
    std::cout << std::endl;

    std::cout << "Testing 2. Add Two Numbers:" << std::endl;
    ListNode *l1 = new ListNode(2);
    l1->next = new ListNode(4);
    l1->next->next = new ListNode(3);

    ListNode *l2 = new ListNode(5);
    l2->next = new ListNode(6);
    l2->next->next = new ListNode(4);
    ListNode *result = addTwoNumbers(l1, l2);
    ListNode *res = result;
    std::cout << result->val << " ";
    while(result->next != nullptr) {
        result = result->next;
        std::cout << result->val << " ";
    }
    std::cout << std::endl;

    std::cout << "Testing 3. longest substring without repeating characters: " << std::endl;
    std::string str = "abcabcbb";
    std::cout << "Max len of \"abcabcbb\" : " << lengthOfLongestSubstring(str) << std::endl;

    std::cout << "Test 4. median of the two sorted arrays: " << std::endl;
    std::vector<int> nums1 = {2, 3, 4};
    std::vector<int> nums2 = {1};
    // nums2.push_back(3);
    // nums2.push_back(4);

    std::cout << "Median is: " << findMedianSortedArrays(nums1, nums2) << std::endl;

    std::cout << "Test 5. Longest Palindromic Substring: " << std::endl;
    std::string str1 = "babad", str2 = "cbbd";

    std::cout << "Longest Palindromic Substring " << "of " << str1 << " is: " << longestPalindrome(str1) << std::endl;
    std::cout << "Longest Palindromic Substring " << "of " << str2 << " is: " << longestPalindrome(str2) << std::endl;

    std::cout << "Longest Palindromic Substring " << "of aaaaaaaa"  << " is: " << longestPalindrome("aaaaaaaa") << std::endl;


    return 0;
}