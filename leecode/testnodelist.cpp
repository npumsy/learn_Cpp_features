

#include "../leetcode-debug/header.h"

using namespace std;

class Solution {
public:
    ListNode* trainningPlan(ListNode* head) {
        return recur(nullptr, head);
    }
    ListNode* recur(ListNode* pre, ListNode* cur){
        if(!cur)return pre;
        ListNode* res = recur(cur,cur->next);
        cur->next=pre;
        return res;
    }
};

#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
// Excecutor的第一个模板参数为类名，第二个模板参数为false；
  Excecutor<Solution, true> exc("/mnt/f/Develop/learn_Cpp_features/leecode/testcases.txt");
  exc.instance = exc.createInstance<void>();

  REGISTER(trainningPlan)
  exc.run();
}