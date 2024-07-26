#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>

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
    // ListNode *l1, *l2;
    // ListNode *result = addTwoNumbers(l1, l2);
    // std::cout << 10 / 10 << std::endl;
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
    return 0;
}