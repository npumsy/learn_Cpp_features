

#include "../leetcode-debug/header.h"

using namespace std;
// [0,1,2,2,3,0,4,2]
// 2
class Solution {
public:
    vector<int> successfulPairsStairs(vector<int>& spells, vector<int>& potions, long long success) {
        vector<int> successes(spells.size(),0);
        unordered_map<int,int> map_aspSuccess;
        int np=potions.size();
        sort(potions.begin(),potions.end());
        for(int j=0;j<spells.size();j++){
            // map[key] 如果 key 不存在，会自动插入 key，并用 int() 初始化为 0
            if(map_aspSuccess.find(spells[j]) != map_aspSuccess.end())
                successes[j]=map_aspSuccess[spells[j]];
            else{
                long long asp=spells[j];
                int minpo=success/asp+1;
                int i=0;
                // 按从大到小排列，依次递减尝试直到找到正好比临界值小的
                for(i=np-1;i>=0;i--){
                    if(potions[i]>minpo)continue;
                    else if(asp*potions[i]>=success)continue;
                    else {
                        successes[j]=(np-i-1);
                        break;
                    }//{if(asp*po>=success)su++;}
                }
                if(i==-1&&asp*potions[0]>=success)successes[j]=np;
                map_aspSuccess[spells[j]]=successes[j];
            }
        }
        return successes;
    }
    
    // 假设spells和potions都是100000个100000，success是10000000000，输出是100000个100000，就会超时报错
    vector<int> successfulPairsNoMap(vector<int>& spells, vector<int>& potions, long long success) {
        vector<int> successes(spells.size(),0);
        sort(potions.begin(),potions.end());
        for(int j=0;j<spells.size();j++){
            // map[key] 如果 key 不存在，会自动插入 key，并用 int() 初始化为 0
            long long asp=spells[j];
            successes[j] = findMoreThan2(potions,potions.size(),asp,success);
        }
        return successes;
    }
    
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        sort(potions.begin(), potions.end());
        vector<int> res;
        for (auto& i : spells) {
            long long t = (success + i - 1) / i - 1;
            res.push_back(potions.size() - (upper_bound(potions.begin(), potions.end(), t) - potions.begin()));
        }
        return res;
    }
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        vector<int> successes(spells.size(),0);
        unordered_map<int,int> map_aspSuccess;
        sort(potions.begin(),potions.end());
        for(int j=0;j<spells.size();j++){
            // map[key] 如果 key 不存在，会自动插入 key，并用 int() 初始化为 0
            if(map_aspSuccess.find(spells[j]) != map_aspSuccess.end())
                successes[j]=map_aspSuccess[spells[j]];
            else{
                long long asp=spells[j];
                successes[j] = findMoreThan2(potions,potions.size(),asp,success);
                
                map_aspSuccess[spells[j]]=successes[j];
            }
        }
        return successes;
    }

    // 查找正好比goal小的ordered_pos序号,
    // 返回 0-100，0代表全比goal小，100代表全比goal大，否则return在中间
    int findMoreThan2(vector<int> &ordered_pos,int np, long long asp, long long success){
        int idb=np-1,ida=0;
        int minpo= (success + asp - 1) / asp;  // 即 ceil(success / asp)
        ida=minpo;
        // 按从大到小排列，依次递减尝试直到找到正好比临界值小的
        if((asp*ordered_pos[ida]<success)&&(asp*ordered_pos[idb]>=success)){
            int cent;
            while(idb>ida+1){
                cent=int(0.618*(idb-ida)+ida);
                if(asp*ordered_pos[cent]>success){
                    idb=cent;
                }
                else{
                    ida=cent;
                }
            }
            while(asp*ordered_pos[cent]>=success&&cent>0)cent--;
            return np-cent-1;
        }
        else{
            if(asp*ordered_pos[ida]>=success)return np;
            else return 0;
        }
        
    }
    int findMoreThan(vector<int> &ordered_pos,int np, int asp, long long success){
        int idb=np,ida=0;
        int minpo=success/asp;
        int i=0;
        // 按从大到小排列，依次递减尝试直到找到正好比临界值小的
        for(i=np-1;i>=0;i--){
            if(ordered_pos[i]>minpo)continue;
            else if(asp*ordered_pos[i]>=success)continue;
            else {
                return (np-i-1);
                break;
            }
        }
        if(i==-1&&asp*ordered_pos[0]>=success)return np;
        return i;
    }
};
#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    // Excecutor的第一个模板参数为类名，第二个模板参数为false；
    Excecutor<Solution, true> exc("../in.txt");
    exc.instance = exc.createInstance<void>();

    REGISTER(successfulPairs)
    exc.run();
}