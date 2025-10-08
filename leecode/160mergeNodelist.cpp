

#include "../leetcode-debug/header.h"

using namespace std;
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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        unordered_map<ListNode*, bool> m;
        while(headA != nullptr){
            m[headA] = true;
            headA = headA->next;
        }
        while(headB != nullptr){
            if(m[headB]) return headB;
            headB = headB->next;
        }
        return nullptr;
    }

};
#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    // Excecutor的第一个模板参数为类名，第二个模板参数为false；
    Excecutor<Solution, true> exc("../innode.txt");
    exc.instance = exc.createInstance<void>();

    REGISTER(getIntersectionNode)
    exc.run();
}