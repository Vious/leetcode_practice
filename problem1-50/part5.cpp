#include <iostream>
#include <vector>
#include <queue>
#include <utility>

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

/* 25. Reverse Nodes in k-Group */
ListNode *simpleInverseListNode(ListNode *head) {
    // this code just do the inverse of a given list.
    if (!head || !head->next) {
        return head;
    }

    ListNode *pivot = head;
    ListNode *left = pivot, *right = pivot->next;
    ListNode *tmpPtr = nullptr;
    left->next = nullptr;
    pivot = right->next;
    right->next = left;
    tmpPtr = right;
    while(pivot) {
        left = pivot;
        right = pivot->next;
        left->next = tmpPtr;
        if (right) {
            pivot = right->next;
            right->next = left;
            tmpPtr = right;
        } else {
            break;
        }
    }
    head = (right) ? right : left;
    return head;
}
/* 25. Reverse Nodes in k-Group */
// check whether the remaining node is larger than k or not
ListNode *nextKthNode(ListNode *head, int k) {
    int tmpCount = 1;
    ListNode *tmpNode = head;
    while(tmpNode) {
        tmpNode = tmpNode->next;
        tmpCount++;
        if (tmpCount == k) {
            break;
        }
    }
    return tmpNode;
}

// reverse node from the given start node to end node
std::pair<ListNode*, ListNode*> reverseList(ListNode *start, ListNode *end) {
    ListNode *current = start;
    ListNode *prev = end->next;
    ListNode *tmpPtr = nullptr;
    while(prev != end) {
        tmpPtr = current->next;
        current->next = prev;
        prev = current;
        current = tmpPtr;
    }
    return {end, start};
}

ListNode* reverseKGroup(ListNode* head, int k) {
    if (!head || !head->next || k == 1) {
        return head;
    }
    ListNode *tmpKthNode = nextKthNode(head, k);
    if (!tmpKthNode) {return head;}
    ListNode *ptrHead = new ListNode();
    ptrHead->next = head;
    ListNode *pivot = ptrHead;
    while(tmpKthNode) {
        ListNode *end = tmpKthNode;
        auto reversed = reverseList(head, end);
        pivot->next = reversed.first;
        pivot = reversed.second;
        head = reversed.second->next;
        tmpKthNode = nextKthNode(head, k);
    }


    return ptrHead->next;
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

    std::cout << "Testing for Problem 25. Reverse Nodes in k-Group: " << std::endl;
    ListNode *list3 = new ListNode(1);
    list3->next = new ListNode(3);
    list3->next->next = new ListNode(4);
    list3->next->next->next = new ListNode(5, new ListNode(6));
    // auto reversed = reverseList(list3, list3->next->next->next);
    ListNode *res2 = reverseKGroup(list3, 2);
    while(res2) {
        std::cout << res2->val << " ";
        res2 = res2->next;
    }
    std::cout << std::endl;

    return 0;
}