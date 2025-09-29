

#include "../leetcode-debug/header.h"

using namespace std;

class Solution {
public:
    vector<vector<int>> fileCombination_(int target) {
        bool odd =(target&1) ;// 奇
        vector<vector<int>> comb;
        
        if(odd){// 奇
            for(int i=2;i<target/2;i++){
                int j=target/i;
                if(j<i)break;
                vector<int> temp;
                if(i*j<=target){
                    temp.push_back(j);
                    temp.push_back(j+1);
                    if(i*j==target){
                        comb.push_back(temp);
                    }
                }
                while(temp.size()<j){}
            }
        }else{// 偶数
            for(int i=3;i<target/3;i++){
                int j=target/i;
                if(j>=i)break;

            }
        }
        return comb;
    }

    vector<vector<int>> fileCombination_ref(int target) {
        int i = 1;
        double j = 2.0;
        vector<vector<int>> res;
        while(i < j) {
            j = (-1 + sqrt(1 + 4 * (2 * target + (long) i * i - i))) / 2;
            if(i < j && j == (int)j) {
                vector<int> ans;
                for(int k = i; k <= (int)j; k++)
                    ans.push_back(k);
                res.push_back(ans);
            }
            i++;
        }
        return res;
    }

    vector<vector<int>> fileCombination(int target) {
        bool odd =(target&1) ;// 奇
        vector<vector<int>> comb;
        int l=1,r;
        // auto getr= [target](int l){long insq = 4*(2*target+l*l-l)+1;return (int)(sqrt(insq)-1)/2;};
        auto getr= [target](int l){
            long insq = 2*target;insq+=((long)l*l);insq-=l;insq*=4;
            return (int)(sqrt(insq+1)-1)/2;
        };
        int nums=2;
        if(!(target&1))nums=3;
        int mean;
        r=getr(l);
        deque<int> slide_nums;
        vector<int> tmp;
        // for(;mean>nums;nums++){
        //     mean=target/nums;
            
            int sum=0;
            for(;l<=r;l++){
                r=getr(l);
                for(int i=l;i<=r;i++){
                    tmp.push_back(i);
                    sum+=i;
                    if(sum==target){
                        // for(auto nn:slide_nums){
                        // tmp.push_back(nn);
                        // }
                    comb.push_back(tmp);
                    
                    }
                }
                // slide_nums.pop_front();
                tmp.clear();
                sum=0;
            }
            
        // }
        // if(!comb.size()){// 抢救模式？
        //     r=getr(l);
        //     int sum=0;
        //     bool flag=false;
        //     for(int i=l;i<=r;i++){
        //         slide_nums.push_back(i);
        //         sum+=i;
        //         if(target==sum){flag=true;break;}
        //     }
            
        //     if(flag){
        //         for(auto i:slide_nums){
        //         tmp.push_back(i);
        //         }
        //         comb.push_back(tmp);
        //     }
        // }
        return comb;
    }
};
#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    // Excecutor的第一个模板参数为类名，第二个模板参数为false；
    Excecutor<Solution, true> exc("../in.txt");
    exc.instance = exc.createInstance<void>();

    REGISTER(fileCombination)
    exc.run();
}