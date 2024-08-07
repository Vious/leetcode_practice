#include <iostream>
#include <vector>

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

/* 22. Generate Parentheses */
void backtraceParenthesis(std::vector<std::string> &curResults, std::string tmpStr, int leftNumber, int rightNumber) {
    if (rightNumber == 0) {
        curResults.emplace_back(tmpStr);
        return;
    } else {
        if (leftNumber > 0) {
            backtraceParenthesis(curResults, tmpStr + "(", leftNumber - 1, rightNumber);
            if (rightNumber > leftNumber) {
                backtraceParenthesis(curResults, tmpStr + ")", leftNumber, rightNumber - 1);
            }
        } else {
            backtraceParenthesis(curResults, tmpStr + ")", 0, rightNumber-1);
        }
    }
}
//solution 1, backtracing
std::vector<std::string> generateParenthesis(int n) {
    if (n < 1) {
        return {};
    } 
    std::vector<std::string> results;
    backtraceParenthesis(results, "(", n - 1, n);
    return results;
}
//solution 2, dynamic programming
std::vector<std::string> dpCodeForGenerateParenthesis(int n) {
    if (n < 1) {
        return {};
    }
    std::vector<std::vector<std::string>> dpResults(n+1);
    dpResults[0].push_back("");
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            std::vector<std::string> tmpStrs;
            for (auto str : dpResults[j]) {
                for (auto previous : dpResults[i - j - 1]) {
                    tmpStrs.emplace_back("(" + str + ")" + previous);
                }
            }
            dpResults[i].insert(dpResults[i].end(), tmpStrs.begin(), tmpStrs.end());
        }
    }

    return dpResults[n];

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

    std::cout << "Testing for Problem 22. Generate Parentheses: " << std::endl;
    std::cout << "Input n = 3: ";

    std::vector<std::string> results = generateParenthesis(4);
    for (auto str : results) {
        std::cout << str << ",";
    }
    std::cout << std::endl;

    return 0;
}