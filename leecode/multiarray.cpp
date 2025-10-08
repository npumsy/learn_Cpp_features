

#include "../leetcode-debug/header.h"

using namespace std;
// arrayB[i] 表示将 arrayA[i] 从总体中排除后的其他的乘积。
// B[i] = A[0] * A[1] * ... * A[i - 1] * A[i + 1] * ... * A[n - 1]
// 如：
// B[0]=  1* A[1]*A[2]*...*A[n-3]*A[n-2]*A[n-1]
// B[1]= A[0] *1* A[2]*...*A[n-3]*A[n-2]*A[n-1]
// B[2]= A[0]*A[1] *1* ...*A[n-3]*A[n-2]*A[n-1]
//
// B[n-2]=A[0]*A[1]*A[2]*...*A[n-3] *1* A[n-1]
// B[n-1]=A[0]*A[1]*A[2]*...*A[n-3]*A[n-2] *1
class Solution {
public:
    vector<int> statisticalResult(vector<int>& arrayA) {
        int len = arrayA.size();
        if(len == 0) return {};
        vector<int> arrayB(len, 1);
        arrayB[0] = 1;
        int tmp = 1;
        for(int i = 1; i < len; i++) {
            arrayB[i] = arrayB[i - 1] * arrayA[i - 1];
        }
        for(int i = len - 2; i >= 0; i--) {
            tmp *= arrayA[i + 1];
            arrayB[i] *= tmp;
        }
        return arrayB;
    }
};

// 作者：Krahets
// 链接：https://leetcode.cn/leetbook/read/illustration-of-algorithm/lhiayd/
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
#define REGISTER(func) exc.registerMemberFunction(#func, &Solution::func);

int main() {
    // Excecutor的第一个模板参数为类名，第二个模板参数为false；
    Excecutor<Solution, true> exc("../in.txt");
    exc.instance = exc.createInstance<void>();

    REGISTER(statisticalResult)
    exc.run();
}