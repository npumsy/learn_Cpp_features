//
// Created by light on 20-1-31.
//

#include <iostream>
#include <thread>
#include <chrono>

using namespace std::chrono;
using namespace std;


/**
 * 1.普通函数指针
 * 2.Lambda函数
 * 3.Functors
 * 4.非静态成员函数
 * 5.静态成员函数
 */

using ull = unsigned long long;
ull OddSum = 0;
ull EvenSum = 0;

/*
位运算i & 1会检查i的二进制表示的最后一位
    如果最后一位是0，则i是偶数，结果为0
    如果最后一位是1，则i是奇数，结果为1
*/
void findEven(ull start, ull end) {
    for (ull i = start; i <= end; ++i)
        if ((i & 1) == 0)
            EvenSum += i;
}

void findOdd(ull start, ull end) {
    for (ull i = start; i <= end; ++i)
        if ((i & 1) == 1)
            OddSum += i;
}

int main() {

    ull start = 0, end = 1900000000;


    auto startTime = high_resolution_clock::now();
    std::thread t2(findOdd,start,end);
    std::thread t1(findEven,start,end/2);// 后开始运算，但是运算量更小
    // 线程创建开始就立刻运行

    this_thread::sleep_for(microseconds(1));

    t1.detach();
    // join() 和 detach() 只是决定主线程如何管理这个已运行线程的生命周期。
    // join() 会阻塞主线程，直到被 join 的线程执行完毕
    // detach() 会使线程在后台运行，主线程不会等待它执行完毕

    // 经过1ms，已经累加到多少了
    cout << "EvenSum: " << EvenSum << endl;
    cout << "OddSum : " << OddSum << endl;
    t2.join();

    auto stopTime = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stopTime - startTime);

    cout << "EvenSum: " << EvenSum << endl;
    cout << "OddSum : " << OddSum << endl;
    cout << "Sec: " << duration.count() / 1000000 << endl;
    return 0;
}
