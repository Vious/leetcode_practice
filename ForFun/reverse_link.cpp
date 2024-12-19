#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <ranges>
#include <queue>
#include <numeric>

using namespace std;
/* Definition for singly-linked list. */ 
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

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

/* 92. Reverse Linked List II */
ListNode* reverseBetween(ListNode* head, int left, int right) {
    ListNode *dummy = new ListNode(0, head);
    ListNode *p0 = dummy;
    for (int i = 0; i < left - 1; i++) {
        p0 = p0->next;
    }
    ListNode *prev = nullptr, *cur = p0->next;
    ListNode *next = nullptr;
    for (int i = 0; i < right - left + 1; i++) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    p0->next->next = cur;
    p0->next = prev;
    return dummy->next;
}

/* 25. Reverse Nodes in k-Group */
ListNode* reverseKGroup(ListNode* head, int k) {
    int length = 0;
    ListNode *tmpNode = head;
    while(tmpNode) {
        length++;
        tmpNode = tmpNode->next;
    }
    ListNode *dummy = new ListNode(0, head);
    ListNode *p0 = dummy;
    ListNode *prev = nullptr, *cur = p0->next;
    ListNode *next = nullptr;
    int swapNum = length / k;
    for (int i = 0; i < swapNum; i++) {
        for(int j = 0; j < k; j++) {
            next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        /* use next to p0 */
        next = p0->next;
        p0->next->next = cur;
        p0->next = prev;
        p0 = next;
    }
    return dummy->next;
}

/* 24. Swap Nodes in Pairs */
ListNode* swapPairs(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    ListNode *dummy = new ListNode(0, head);
    ListNode *p0 = dummy;
    ListNode *prev = nullptr, *cur = p0->next;
    ListNode *next = nullptr;
    while(cur->next != nullptr) {
        for (int i = 0; i < 2; i++) {
            next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        next = p0->next;
        p0->next->next = cur;
        p0->next = prev;
        p0 = next;
        if (cur == nullptr) {
            break;
        }
    }
    return dummy->next;
}

/* 445. Add Two Numbers II */
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    if (l1 == nullptr || l2 == nullptr) {
        return l1 == nullptr ? l2 : l1;
    }
    l1 = reverseList(l1);
    l2 = reverseList(l2);
    ListNode *head1 = l1;
    int sum = 0;
    int carry = 0;
    while(l1->next != nullptr && l2->next != nullptr) {
        sum = l1->val + l2->val + carry;
        carry = sum / 10;
        sum %= 10;
        l1->val = sum;
        l1 = l1->next;
        l2 = l2->next;
    }
    if (l1->next != nullptr && l2->next == nullptr) {
        sum = l1->val + l2->val + carry;
        carry = sum / 10;
        sum %= 10;
        l1->val = sum;
        while(carry > 0) {
            if (l1->next != nullptr) {
                l1 = l1->next;
                sum = l1->val + carry;
                carry = sum / 10;
                sum %= 10;
                l1->val = sum;
            } else {
                ListNode *tail = new ListNode(0);
                l1->next = tail;
                sum = tail->val + carry;
                tail->val = sum;
                carry = 0;
            }
        }
    } else if (l1->next == nullptr && l2->next != nullptr) {
        sum = l1->val + l2->val + carry;
        carry = sum / 10;
        sum %= 10;
        l1->val = sum;
        l1->next = l2->next;
        while(carry > 0) {
            if (l2->next != nullptr) {
                l2 = l2->next;
                sum = l2->val + carry;
                carry = sum / 10;
                sum %= 10;
                l2->val = sum;
            } else {
                ListNode *tail = new ListNode(0);
                l2->next = tail;
                sum = tail->val + carry;
                tail->val = sum;
                carry = 0;
            }
        }
    } else {
        sum = l1->val + l2->val + carry;
        carry = sum / 10;
        sum %= 10;
        l1->val = sum;
        if (carry) {
            ListNode *tail = new ListNode(0);
            l1->next = tail;
            sum = tail->val + carry;
            tail->val = sum;
        }
    }
    return reverseList(head1);
}

/* 2816. Double a Number Represented as a Linked List */
ListNode* doubleIt(ListNode* head) {
    if (head == nullptr) {
        return head;
    }
    head = reverseList(head);
    ListNode *saveHead = head;
    int carry = 0;
    while(head->next != nullptr) {
        int dval = head->val * 2 + carry;
        carry = dval / 10;
        dval %= 10;
        head->val = dval;
        head = head->next;
    }
    int dval = head->val * 2 + carry;
    carry = dval / 10;
    dval %= 10;
    head->val = dval;
    if (carry) {
        ListNode *tail = new ListNode(carry);
        head->next = tail;
    }
    return reverseList(saveHead);
}