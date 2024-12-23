#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <ranges>
#include <queue>
#include <numeric>
#include <list>
#include <stack>

using namespace std;
/* Definition for singly-linked list. */ 
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

/* 237. Delete Node in a Linked List */
void deleteNode(ListNode* node) {
    node->val = node->next->val;
    ListNode *next = node->next;
    node->next = next->next;
    delete next;
}

/* 19. Remove Nth Node From End of List */
ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode *dummy = new ListNode(0, head);
    ListNode *left = dummy, *right = dummy;
    for (int i = 1; i <= n; i++) {
        right = right->next;
    }
    while(right->next != nullptr) {
        right = right->next;
        left = left->next;
    }
    ListNode *tmpNode = left->next;
    left->next = left->next->next;
    delete tmpNode;
    return dummy->next;
}

/* 83. Remove Duplicates from Sorted List */
ListNode* deleteDuplicates(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    ListNode *cur = head;
    ListNode *tmpNode = nullptr;
    while(cur->next != nullptr) {
        if (cur->val == cur->next->val) {
            tmpNode = cur->next;
            cur->next = cur->next->next;
            delete tmpNode;
        } else {
            cur = cur->next;
        }
    }
    return head;
}

/* 82. Remove Duplicates from Sorted List II */
ListNode* deleteDuplicatesV2(ListNode* head) {
    ListNode *dummy = new ListNode(INT32_MIN, head);
    ListNode *cur = dummy;
    ListNode *tmpNode = nullptr;
    while(cur->next != nullptr && cur->next->next != nullptr) {
        int val = cur->next->val;
        if (cur->next->next->val == val) {
            while(cur->next != nullptr && cur->next->val == val ) {
                tmpNode = cur->next;
                cur->next = cur->next->next;
                delete tmpNode;
            }
        } else {
            cur = cur->next;
        }
    }
    return dummy->next;
}

/* 203. Remove Linked List Elements */
ListNode* removeElements(ListNode* head, int val) {
    ListNode *dummy = new ListNode(INT32_MIN, head);
    ListNode *cur = dummy, *tmpNode = nullptr;
    while(cur->next != nullptr) {
        if (cur->next->val == val) {
            tmpNode = cur->next;
            cur->next = cur->next->next;
            delete tmpNode;
        } else {
            cur = cur->next;
        }
    }
    return dummy->next;
}

/* 3217. Delete Nodes From Linked List Present in Array */
ListNode* modifiedList(vector<int>& nums, ListNode* head) {
    int size = nums.size();
    if (size == 0) {
        return head;
    }
    std::unordered_map<int, int> hashMap;
    for (int i = 0; i < size; i++) {
        hashMap[nums[i]]++;
    }
    ListNode *left = head, *right = head->next;
    ListNode *tmpNode = nullptr;
    while(right) {
        if (hashMap[right->val]) {
            tmpNode = right;
            right = right->next;
            left->next = right;
            delete tmpNode;
        } else {
            left = left->next;
            right = right->next;
        }
    }
    if (hashMap[head->val]) {
        head = head->next;
    }
    return head;
}

/* 206. Reverse Linked List */
ListNode* reverseList(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    ListNode *prev = nullptr, *pivot = head->next;
    while(pivot != nullptr) {
        head->next = prev;
        prev = head;
        head = pivot;
        pivot = pivot->next;
        head->next = prev;
    }
    return head;
}

/* 2487. Remove Nodes From Linked List */
ListNode* removeNodes(ListNode* head){
    /* v1, create new list */
    /* 
        std::stack<ListNode*> nodeStack;
    ListNode *tmpNode = head;
    while(tmpNode != nullptr) {
        nodeStack.emplace(tmpNode);
        tmpNode = tmpNode->next;
    }
    tmpNode = nodeStack.top();
    nodeStack.pop();
    ListNode *dummy = new ListNode(0, tmpNode);
    int value = tmpNode->val;
    ListNode *pivot = nullptr;
    while(!nodeStack.empty()) {
        tmpNode = nodeStack.top();
        nodeStack.pop();
        if (tmpNode->val < value) {
            // delete tmpNode;
            continue;
        } else {
            pivot = dummy->next;
            dummy->next = tmpNode;
            tmpNode->next = pivot;
            value = tmpNode->val;
        }
    }
    return dummy->next;
     */
    ListNode *revHead = reverseList(head);
    ListNode *cur = revHead, *tmpNode = nullptr;
    int value = cur->val;
    while(cur->next != nullptr) {
        if (value > cur->next->val) {
            tmpNode = cur->next;
            cur->next = cur->next->next;
        } else {
            cur = cur->next;
            value = cur->val;
        }
    }
    return reverseList(revHead);
}

/* 1669. Merge In Between Linked Lists */
ListNode* mergeInBetween(ListNode* list1, int a, int b, ListNode* list2) {
    ListNode *left = list1;
    ListNode *right = list1;
    ListNode *node2end = list2;
    while(node2end->next != nullptr) {
        node2end = node2end->next;
    }
    for (int i = 1; i < a; i++) {
        left = left->next;
    }
    for (int i = 0; i < b; i++) {
        right = right->next;
    }
    left->next = list2;
    node2end->next = right->next;
    return list1;
}
