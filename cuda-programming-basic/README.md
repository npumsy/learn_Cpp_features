# CUDA 编程基础教程

本仓库包含了CUDA编程的基础教程示例代码，涵盖了从基础概念到高级优化的多个方面。每个子文件夹都专注于特定的CUDA编程主题，提供了实用的示例代码和详细注释。

This is from [tensorrt_starter\chapter2-cuda-programming](https://github.com/kalfazed/tensorrt_starter).

for more tutorial, see 
1. https://docs.nvidia.com/cuda/cuda-c-programming-guide/index.html
2. https://developer.nvidia.com/blog/even-easier-introduction-cuda/

## 目录结构

- 2.1-dim_and_index ：展示CUDA的线程索引和维度概念
- 2.2-cpp_cuda_interactive ：展示C++和CUDA代码之间的交互方式
- 2.3-matmul-basic ：展示基本的矩阵乘法CUDA实现
- 2.4-error-handler ：展示CUDA错误处理机制
- 2.5-device-info ：展示如何获取CUDA设备的硬件信息
- 2.6-nsight-system-and-compute ：介绍NVIDIA Nsight性能分析工具的使用
- 2.7-matmul-shared-memory ：展示如何使用共享内存优化矩阵乘法
- 2.8-bank-conflict ：展示CUDA中的共享内存银行冲突问题及其解决方案
- 2.9-stream-and-event ：展示CUDA流和事件的使用方法
- 2.10-bilinear-interpolation ：展示CUDA中的双线性插值实现
- 2.11-bilinear-interpolation-template ：展示使用模板实现的双线性插值
- 2.12-affine-transformation ：展示CUDA中的仿射变换实现
- data ：存放示例图片数据 https://github.com/kalfazed/tensorrt_starter/tree/main/chapter2-cuda-programming/2.10-bilinear-interpolation/data

## 子文件夹详细介绍

### 2.1-dim_and_index

**主要内容**：展示CUDA的线程索引和维度概念，是CUDA编程的基础。

**关键CUDA特性**：
- CUDA的线程层次结构（grid、block、thread）
- `threadIdx`、`blockIdx`、`blockDim`、`gridDim`等内置变量的使用
- 一维和二维网格（grid）和块（block）的配置方法
- 线程索引的计算（全局索引和局部索引）

**主要文件**：
- `print_index.cu`：包含多个展示不同索引计算方式的CUDA核函数

### 2.2-cpp_cuda_interactive

**主要内容**：展示C++和CUDA代码之间的交互方式，如何在C++程序中调用CUDA核函数。

**关键CUDA特性**：
- C++和CUDA代码的分离与集成
- CUDA核函数的声明和调用方法
- CUDA错误检查宏的使用
- 设备同步操作

**主要文件**：
- `print_index.cu`：包含CUDA核函数和调用包装函数
- `print_index.hpp`：声明可从C++调用的CUDA函数接口
- `main.cpp`：C++主程序，调用CUDA函数

### 2.3-matmul-basic

**主要内容**：展示基本的矩阵乘法CUDA实现，比较CPU和GPU的性能差异。

**关键CUDA特性**：
- GPU内存分配与释放（`cudaMalloc`、`cudaFree`）
- 主机与设备间的数据传输（`cudaMemcpy`）
- 基本的CUDA核函数设计
- 使用dim3配置线程网格
- 性能计时与比较

**主要文件**：
- `matmul_gpu_basic.cu`：基本的CUDA矩阵乘法实现
- `matmul_cpu.cpp`：CPU矩阵乘法实现，用于性能对比
- `main.cpp`：主程序，包含性能测试和结果验证

### 2.4-error-handler

**主要内容**：展示CUDA错误处理机制，帮助调试CUDA程序。

**关键CUDA特性**：
- CUDA错误检查宏的定义和使用
- 核函数执行后的错误检查
- CUDA API错误信息的获取和显示

**主要文件**：
- `utils.hpp`：定义了`CUDA_CHECK`和`LAST_KERNEL_CHECK`等错误检查宏

### 2.5-device-info

**主要内容**：展示如何获取CUDA设备的硬件信息，了解GPU的能力。

**关键CUDA特性**：
- CUDA设备数量查询（`cudaGetDeviceCount`）
- CUDA设备属性获取（`cudaGetDeviceProperties`）
- GPU硬件参数（计算能力、内存大小、缓存大小、时钟频率等）的展示

**主要文件**：
- `main.cpp`：展示如何获取并打印各种CUDA设备信息

### 2.6-nsight-system-and-compute

**主要内容**：介绍NVIDIA Nsight性能分析工具的使用，用于CUDA程序的性能分析和优化。

**关键CUDA特性**：
- Nsight System的使用方法
- Nsight Compute的使用方法
- CUDA程序性能分析技巧

### 2.7-matmul-shared-memory

**主要内容**：展示如何使用共享内存优化矩阵乘法，提高内存访问效率。

**关键CUDA特性**：
- 共享内存的声明和使用（`__shared__`关键字）
- 静态共享内存和动态共享内存的区别
- 矩阵分块计算（Tiling技术）
- 线程同步（`__syncthreads()`）
- 使用共享内存减少全局内存访问

**主要文件**：
- `matmul_gpu_shared.cu`：包含使用共享内存优化的矩阵乘法实现

### 2.8-bank-conflict

**主要内容**：展示CUDA中的共享内存银行冲突问题及其解决方案。

**关键CUDA特性**：
- 共享内存银行冲突的产生原因
- 如何通过内存访问模式避免银行冲突
- 使用填充（padding）解决银行冲突的方法
- 银行冲突对性能的影响

**主要文件**：
- `matmul_gpu_bank_conflict.cu`：故意制造银行冲突的矩阵乘法实现
- `matmul_gpu_bank_conflict_pad.cu`：使用填充解决银行冲突的矩阵乘法实现

### 2.9-stream-and-event

**主要内容**：展示CUDA流和事件的使用方法，用于异步执行和性能测量。

**关键CUDA特性**：
- CUDA流的创建和使用（`cudaStreamCreate`）
- 异步内存传输（`cudaMemcpyAsync`）
- 流内的核函数执行
- 多流并行执行任务
- 流同步操作

**主要文件**：
- `stream.cu`：展示单流和多流的使用方法
- `gelu.cu`：可能包含使用流执行的GELU激活函数实现

### 2.10-bilinear-interpolation

**主要内容**：展示CUDA中的双线性插值实现，常用于图像处理中的缩放操作。

**关键CUDA特性**：
- 图像处理中的并行计算
- 双线性插值算法的CUDA实现
- 图像数据在GPU上的处理

**主要文件**：
- `preprocess.cu`：包含CUDA实现的双线性插值预处理函数
- `main.cpp`：主程序，调用双线性插值函数处理图像

### 2.11-bilinear-interpolation-template

**主要内容**：展示使用模板实现的双线性插值，提高代码的可重用性和灵活性。

**关键CUDA特性**：
- CUDA中的模板编程
- 模板函数和模板类在CUDA中的应用
- 泛型双线性插值实现

### 2.12-affine-transformation

**主要内容**：展示CUDA中的仿射变换实现，用于图像的平移、旋转、缩放等几何变换。

**关键CUDA特性**：
- 仿射变换矩阵的应用
- 图像几何变换的并行计算
- 变换后像素坐标的计算

### data

**主要内容**：存放示例图片数据，用于图像处理相关的示例。

**包含文件**：
- 各种示例图片（cat.png、deer.png、eagle.png、fox.png、tiny-cat.png、unknown.png、wolf.png）

## 编译和运行

每个子文件夹中都包含`Makefile`或`CMakeLists.txt`，可以使用以下命令编译和运行示例：

```bash
# 使用Makefile编译
cd <子文件夹路径>
make

# 或使用CMake编译
cd <子文件夹路径>
mkdir build && cd build
cmake ..
make

# 运行编译后的程序
./<程序名>
```

## 学习建议

1. 按照编号顺序依次学习各个示例，从基础到高级
2. 仔细阅读代码中的注释，理解每个CUDA特性的使用场景
3. 修改代码中的参数和配置，观察结果变化，加深理解
4. 使用Nsight工具分析程序性能，学习性能优化技巧
5. 尝试将所学知识应用到自己的项目中

## 参考资料

- [NVIDIA CUDA Documentation](https://docs.nvidia.com/cuda/)
- [CUDA C++ Programming Guide](https://docs.nvidia.com/cuda/cuda-c-programming-guide/)
- [CUDA Runtime API Documentation](https://docs.nvidia.com/cuda/cuda-runtime-api/)