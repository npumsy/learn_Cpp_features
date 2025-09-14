#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>

// 共享资源
int counter = 0;

// 互斥锁，用于保护 counter
std::mutex mtx;

// 线程函数：对 counter 累加 10 次
void increaseCounter(int id, int iterations, bool useMutex) {
    for (int i = 0; i < iterations; ++i) {
        // mtx.lock();                    // 🔒 加锁
        if (useMutex) mtx.lock();

        int temp = counter;     // 1. 读
        std::this_thread::sleep_for(std::chrono::nanoseconds(1)); // ⚠️ 强制让出时间片，100% 暴露数据竞争。
        temp++;                 // 2. 改
        counter = temp;         // 3. 写（故意不合并成 ++counter）
        // ++counter;               // 访问共享变量

        // std::cout<< "Thread " << id << ": counter = " << counter << std::endl;
        // 如果保留这句打印，每次打印都强制线程等待 I/O 锁 → 降低了并发冲突
        // 去掉后，++counter 变成纯内存操作，速度极快，多个线程频繁同时读写 counter，数据竞争充分暴露

        // mtx.unlock();                  // 🔓 解锁
        if (useMutex) mtx.unlock();
    }
}

int main() {
    const int num_threads = 3;
    const int iterations_per_thread = 10;
    const bool useMutex = false; // 改为 true 测试加锁

    std::vector<std::thread> threads;

    // 创建多个线程
    std::cout << "Starting " << num_threads << " threads...\n\n";
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(increaseCounter, i + 1, iterations_per_thread, useMutex);
    }

    // 等待所有线程完成
    for (auto& t : threads) {
        t.join();
    }

    // 输出最终结果
    std::cout << "\nFinal counter value: " << counter << std::endl;
    std::cout << "Expected: " << num_threads * iterations_per_thread << std::endl;

    return 0;
}