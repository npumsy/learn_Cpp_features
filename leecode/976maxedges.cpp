

#include "../leetcode-debug/header.h"

using namespace std;

class Solution1 {
  public:
    int largestPerimeter(vector<int> &nums) {
        uint nls = nums.size();
        int max_l = 0;
        for (int i = 0; i < nls - 2; i++)
            for (int j = i + 1; j < nls - 1; j++)
                for (int k = j + 1; k < nls; k++) {
                    if (nums[i] + nums[j] > nums[k] &&
                        nums[i] + nums[k] > nums[j] &&
                        nums[j] + nums[k] > nums[i]) {
                        max_l = max(max_l, nums[i] + nums[j] + nums[k]);

                        // else
                    }
                }
        return max_l;
    }
};
class Solution {
  public:
    int largestPerimeter(vector<int> &nums) {
        uint nls = nums.size();
        int max_l = 0;
        sort(nums.begin(),nums.end());
        // vector<int> rise(nums);
        // sort(rise.begin(), rise.end());
        for(int i=nls-1;i>2;i--){
            if(nums[i-2]+nums[i-1]>nums[i])
                return max_l=nums[i-2]+nums[i-1]+nums[i];
        }
        return max_l;
    }
};
#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    // Excecutor的第一个模板参数为类名，第二个模板参数为false；
    Excecutor<Solution, true> exc("../in.txt");
    exc.instance = exc.createInstance<void>();

    REGISTER(largestPerimeter)
    exc.run();
}