#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <ranges>
#include <queue>
#include <numeric>
#include <list>

using namespace std;
/* Definition for singly-linked list. */ 
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

/* 876. Middle of the Linked List */
ListNode* middleNode(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    ListNode *slow = head, *fast = head;
    while(fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

/* 141. Linked List Cycle */
bool hasCycle(ListNode *head) {
    if (head == nullptr) {
        return false;
    }
    ListNode *slow = head, *fast = head;
    while(fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            return true;
        }
    }
    return false;
}

/* 142. Linked List Cycle II */
ListNode *detectCycle(ListNode *head) {
    if (head == nullptr) {
        return head;
    }
    ListNode *slow = head, *fast = head;
    while(fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        /* a - c = (k - 1)(b + c) */
        if(slow == fast) {
            while(fast != head) {
                fast = fast->next;
                head = head->next;
            }
            return fast;
        }
    }
    return nullptr;
}

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
/* 143. Reorder List */
void reorderList(ListNode* head) {
    if (head->next == nullptr) {
        return;
    }
    ListNode *middle = middleNode(head);
    ListNode *head2 = reverseList(middle);
    ListNode *next = nullptr;
    while(head2->next != nullptr) {
        next = head2->next;
        head2->next = head->next;
        head->next = head2;
        head = head2->next;
        head2 = next;
    }
}

/* 234. Palindrome Linked List */
bool isPalindrome(ListNode* head) {
    ListNode *middle = middleNode(head);
    ListNode *revHead = reverseList(middle);
    while(revHead != nullptr) {
        if (revHead->val != head->val) {
            return false;
        } else {
            revHead = revHead->next;
            head = head->next;
        }
    }
    return true;
}

/* 2130. Maximum Twin Sum of a Linked List */
int pairSum(ListNode* head) {
    ListNode *middle = middleNode(head);
    ListNode *revHead = reverseList(middle);
    int ans = INT32_MIN;
    while(revHead != nullptr) {
        int sum = revHead->val + head->val;
        ans = std::max(sum, ans);
        revHead = revHead->next;
        head = head->next;
    }
    return ans;
}