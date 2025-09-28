

#include "../leetcode-debug/header.h"

using namespace std;
// [0,1,2,2,3,0,4,2]
// 2
class Solution1 {
public:
    int removeElement(vector<int>& nums, int val) {
        int k=0;
        vector<int> delis;
        for(int i=0;i<nums.size();i++){
            if(nums[i]==val)delis.push_back(i);
        }
        k=nums.size()-1;
        for(int j=0;j<delis.size();j++){
            // k=delis[j]+1;
            while(k>0&&nums[k]==val)k--;
            nums[delis[j]]=nums[k--];
        }
        if(nums[0]==val)nums.pop_back();
        return nums.size()-delis.size();
    }
};
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int is=nums.size();
        int left=0;
        for(int right=0;right<is;right++){
            if(nums[right]!=val){
                nums[left++]=nums[right];
            }
        }
        return left;
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