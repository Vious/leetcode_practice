#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <set>
#include <cstring>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

/* 61. Rotate List */
ListNode* rotateRight(ListNode* head, int k) {
    if (k == 0 || !head || !head->next) {
        return head;
    }
    ListNode *tmpNode = head;
    int count = 1;
    while(tmpNode->next) {
        tmpNode = tmpNode->next;
        count++;
    }
    k %= count;
    if (k == 0) {
        return head;
    }
    tmpNode->next = head;
    for (int i = 0; i < count - k; i++) {
        head = head->next;
        tmpNode = tmpNode->next;
    }
    tmpNode->next = nullptr;
    return head;
}

/*  */

int main()
{
    std::cout << "Testing for Problem 61. Rotate List : " << std::endl;
    ListNode *head = new ListNode(1);
    head->next = new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5))));
    head = rotateRight(head, 2);
    for (auto ptr = head; ptr; ptr = ptr->next) {
        std::cout << ptr->val << " ";
    }
    std::cout << std::endl;

    return 0;
}