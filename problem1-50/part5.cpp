#include <iostream>

/* Problem 21. Merge Two Sorted Lists */
/**
 * Definition for singly-linked list. */
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    if (!list1 || !list2) {
        return list1 ? list1 : list2;
    }
    bool flag = list1->val < list2->val;
    ListNode *head = (flag) ? list1 : list2;
    ListNode *pivot = head;
    while(list1 && list2) {
        flag = list1->val < list2->val;
        if (flag) {
            while(list1 != nullptr && list1->val < list2->val) {
                pivot = list1;
                list1 = list1->next;
            }
            pivot->next = list2;

        } else {
            while(list2 != nullptr && list1->val >= list2->val) {
                pivot = list2;
                list2 = list2->next;
            }
            pivot->next = list1;
        }
    }
    if(list1 != nullptr) {
        pivot->next = list1;
    }
    if(list2 != nullptr) {
        pivot->next = list2;
    }
    return head;
}

/*  */


int main()
{
    std::cout << "Testing for Problem 21. Merge Two Sorted Lists: " << std::endl;
    ListNode *list1 = new ListNode(1);
    list1->next = new ListNode(2);
    list1->next->next = new ListNode(4);
    
    ListNode *list2 = new ListNode(1);
    list2->next = new ListNode(3);
    list2->next->next = new ListNode(4);
    list2->next->next->next = new ListNode(5);

    ListNode *res = mergeTwoLists(list1, list2);
    while(res) {
        std::cout << res->val << " ";
        res = res->next;
    }
    std::cout << std::endl;
    return 0;
}