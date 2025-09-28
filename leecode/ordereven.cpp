

#include "../leetcode-debug/header.h"

using namespace std;

class Solution {
public:
    vector<int> trainingPlan(vector<int>& actions) {
        int as = actions.size();
        int right=as-1;
        for(int left=0;left<as;left++){
            if(left>=right)break;
            if(!(actions[left]&1)){
                while(right>left&&!(actions[right]&1)){
                    right--;
                }
                int tmp=actions[left];
                actions[left]=actions[right];
                actions[right--]=tmp;
            }
        }
        return actions;
    }
};
#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    // Excecutor的第一个模板参数为类名，第二个模板参数为false；
    Excecutor<Solution, true> exc("../in.txt");
    exc.instance = exc.createInstance<void>();

    REGISTER(trainingPlan)
    exc.run();
}