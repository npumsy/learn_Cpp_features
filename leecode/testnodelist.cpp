#include <iostream>
#include <vector>
using namespace std;

//  Definition for singly-linked list.
 struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
 };


class Solution {
public:
    vector<int> reverseBookList(ListNode* head) {
        vector<int> vc;
        cal(head, vc);
        return vc;
    }
    void cal(ListNode* p,vector<int> &in){
        if(p->next){
            p=p->next;
            cal(p,in);
        }else{
            in.push_back(p->val);
        }
        
    }
};
int main(){
    Solution s;
    ListNode* head = new ListNode(1);
    head = head->next = new ListNode(2);
    
    s.reverseBookList(head);
    return 0;
}