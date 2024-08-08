#include <iostream>
#include <vector>
#include <queue>

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

/* 23. Merge k Sorted Lists */
ListNode* mergeKLists(std::vector<ListNode*>& lists) {
    int size = lists.size();
    if (size < 0) {
        return nullptr;
    } else if (size == 1) {
        return lists[0];
    }
    // solution 1, simply adopt the brute-force way, merge one by one.
    // ListNode *head = nullptr;
    // for (int i = 0; i < size; i++) {
    //     head = mergeTwoLists(head, lists[i]);
    // }
    // return head;
    
    //solution 2, use heap, priority queue
    auto compNode = [&](ListNode *l1, ListNode *l2) {
        return l1->val > l2->val;
    };
    std::priority_queue<ListNode*, std::vector<ListNode*>, decltype(compNode)> priorQueue(compNode);
    for (int i = 0; i < lists.size(); i++) {
        if (lists[i] == nullptr) {
            continue;
        }
        priorQueue.push(lists[i]);
    }
    if (priorQueue.empty()) {
        return nullptr;
    }
    ListNode *resultHead = new ListNode();
    ListNode *pivot = resultHead;
    ListNode *tmpPtr;
    while(!priorQueue.empty()) {
        tmpPtr = priorQueue.top();
        priorQueue.pop();
        pivot->next = tmpPtr;
        pivot = pivot->next;
        if(tmpPtr->next != nullptr) {
            priorQueue.push(tmpPtr->next);
        }
    }
    return resultHead->next;


}

/* 24. Swap Nodes in Pairs */
ListNode* swapPairs(ListNode* head) {
    if (!head || !head->next) {
        return head;
    }
    ListNode *left = head, *right = head->next;
    left->next = right->next;
    right->next = left;
    ListNode *res = right;
    ListNode *pivot;
    while(left->next && left->next->next) {
        pivot = left;
        left = left->next;
        right = left->next;
        left->next = right->next;
        right->next = left;
        pivot->next = right;
    }
    return res;

}

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

    // std::cout << "Testing for Problem 24. Swap Nodes in Pairs: " << std::endl;


    return 0;
}