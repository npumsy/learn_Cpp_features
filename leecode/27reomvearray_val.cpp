

#include "../leetcode-debug/header.h"

using namespace std;

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        
    }
};
#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    // Excecutor的第一个模板参数为类名，第二个模板参数为false；
    Excecutor<Solution, true> exc("../in.txt");
    exc.instance = exc.createInstance<void>();

    REGISTER(removeElement)
    exc.run();
}