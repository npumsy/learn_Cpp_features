

#include "../leetcode-debug/header.h"

using namespace std;

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        vector<int> nums1_(nums1.begin(),nums1.begin()+m);
        int i=0,j=0,k=0;
        while(i<m&&j<n){
            int d=nums1_[i]<nums2[j]?(nums1_[i++]):(nums2[j++]);
            nums1[k++]=d;
        }
        while(j<n)nums1[k++]=nums2[j++];
        while(i<m)nums1[k++]=nums1_[i++];
    }
};
#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    // Excecutor的第一个模板参数为类名，第二个模板参数为false；
    Excecutor<Solution, true> exc("../in.txt");
    exc.instance = exc.createInstance<void>();

    REGISTER(merge)
    exc.run();
}