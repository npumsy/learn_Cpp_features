#include<iostream>
#include<vector>
using namespace std;
// 这是个没有数据的空类，仅用于展示copy 和 move
class XData{
    public:
        XData(){cout<<"Init\n";};
        ~XData(){cout<<"Destroy\n";};
        // 按照实例拷贝对象
        XData(const XData&){cout<<"Copy\n";};
};
void setData(vector<XData> &data){
    // 这里在多线程调用时，data会丢失
    cout<<"setData\n";
}
void setData2(vector<XData> data){
    // 这里需要使用move把数据传递进来
    cout<<"setData2\n";
}
vector<XData> getData(){
    vector<XData> data(3);
    return data;
    // 此时自动调用move把数据从局部空间移动出来
}
int main() {
    // vector<XData> data1(3);

    // auto data2 = data1; // 调用复制构造函数
    // auto data3 = move(data1); // 调用移动构造函数
    // setData(data1); 
    // setData2(move(data1)); // 调用移动构造函数

    auto data4 = getData(); // 此时默认用的是move而不是copy
    return 0;
}