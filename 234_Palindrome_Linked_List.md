# 234. Palindrome Linked List

## 1. 题目描述
Given a singly linked list, determine if it is a palindrome.

*Example 1:*
```
Input: 1->2
Output: false
```
*Example 1:*
```
Input: 1->2->2->1
Output: true
```
*Follow up:*
Could you do it in O(n) time and O(1) space?

## 2. O(n) time and space 解法
先遍历链表一遍得到链表的size，第二遍走前一半的时候记录下前一半的数字（O(n)space），走后一半的时候把数字与记录下的值对比来判断是否回文。
```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        ListNode* cur = head;
        int size = 0;
        bool isPalin = true;
        while (cur != NULL) {
            ++size;
            cur = cur->next;
        }
        cur = head;
        stack<int> stk;
        for (int i = 0; i < size / 2; ++i) {
            stk.push(cur->val);
            cur = cur->next;
        }
        if (size % 2 != 0) cur = cur->next;
        while (cur != NULL) {
            if (stk.top() != cur->val) {
                isPalin = false;
                break;
            } else {
                cur = cur->next;
                stk.pop();
            }
        }
        return isPalin;
    }
};
```
突然发现回文的定义是"A palindrome is a word, number, or other sequence of characters which reads the same backward as forward"，所以写的简单一点应该是第一遍把所有值都放进栈里面，第二遍全部对比就可以了，不用分成两半还要这么多判断，也不用存储size。

## 3. O(n) time O(1) space解法
通过翻转链表完成。
```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        ListNode *p1 = head, *p2 = head, *prev = NULL, *next;
        if (p2 == NULL) {
            cmpAndReverse(p1, p1->next, next)
        } if (p2->next == NULL) {
            cmpAndReverse(p1, p1->next->next, next)
        } else {
            next = p1->next;
            p1->next = prev;
            prev = p1;
            p1 = next;
            p2 = p2->next->next;
        }
    }
    
    bool cmpAndReverse(ListNode* p1, ListNode* p2, ListNode* pint) {
        bool isSame = true;
        ListNode* prev = pint, *next = NULL;
        while (p1 != NULL && p2 != NULL) {
            if (p1->val != p2->val) {
                isSame = false;
            }
            next = p1->next;
            p1->next = prev;
            prev = p1;
            p1 = next;
            p2 = p2->next;
        }
        return isSame;
    }
};
```