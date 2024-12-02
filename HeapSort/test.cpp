#include <iostream>
#include <random>
#include <chrono> //用于记录时间
#include "HeapSort.h"

//check函数
template <typename T>
bool check(const std::vector<T>& vec) {
    for (size_t i = 1; i < vec.size(); ++i) {
        if (vec[i] < vec[i - 1]) { // 检查是否为升序
            return false;// 逆序就返回false
        }
    }
    return true;
}

// 生成测试数据
std::vector<int> generateRandomSequence(size_t size, int range = 1000000000) { // 生成10亿内随机数
    std::vector<int> vec(size);
    std::random_device rd;                                 // 使用randomdevice生成种子
    std::mt19937 gen(rd());                                 // 使用mt19937生成随机数引擎
    std::uniform_int_distribution<int> dist(0, range - 1); // 生成随机数
    std::generate(vec.begin(), vec.end(), [&]() {          // 使用generate函数生成随机数
        return dist(gen);
    });
    return vec;
}

std::vector<int> generateOrderedSequence(size_t size) {
    std::vector<int> vec(size);
    std::iota(vec.begin(), vec.end(), 0);// 利用iota生成有序序列
    return vec;
}

std::vector<int> generateReverseSequence(size_t size) {
    auto vec = generateOrderedSequence(size);
    std::reverse(vec.begin(), vec.end());//通过reverse将iota生成有序序列逆序
    return vec;
}

std::vector<int> generateRepetitiveSequence(size_t size, int range = 1000) { // 保证大量重复
    std::vector<int> vec(size);
    std::random_device rd;                                 
    std::mt19937 gen(rd());                                 
    std::uniform_int_distribution<int> dist(0, range - 1); // 利用uniform_int_distribution生成均匀随机数
    std::generate(vec.begin(), vec.end(), [&]() {          
        return dist(gen);
    });
    return vec;
}

// 测试自定义堆排序和 std::sort_heap
void testSorting() {
    std::vector<std::vector<int>> testCases = {
        generateRandomSequence(1000000),
        generateOrderedSequence(1000000),
        generateReverseSequence(1000000),
        generateRepetitiveSequence(1000000) // 生成题目要求序列
    };

    const std::vector<std::string> testCaseNames = { // 使输出结果更为清晰
        "Random Sequence",
        "Ordered Sequence",
        "Reverse Sequence",
        "Repetitive Sequence"
    };

    for (size_t i = 0; i < testCases.size(); ++i) {
        auto vec1 = testCases[i];
        auto vec2 = testCases[i];

        // 自定义堆排序
        auto start = std::chrono::high_resolution_clock::now();// 利用chrono中的高精度时钟
        heapSort(vec1);
        auto end = std::chrono::high_resolution_clock::now();
        auto customTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(); //毫秒记录

        // 检查结果正确性
        if (!check(vec1)) {
            std::cerr << "Custom heapSort failed on " << testCaseNames[i] << "\n";
        }

        // STL中的堆排序
        start = std::chrono::high_resolution_clock::now();
        std::make_heap(vec2.begin(), vec2.end()); //heap sort前需要先Make heap
        std::sort_heap(vec2.begin(), vec2.end());
        end = std::chrono::high_resolution_clock::now();
        auto stlTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        if (!check(vec2)) {
            std::cerr << "std::sort_heap failed on " << testCaseNames[i] << "\n";
        }

        // 输出结果
        std::cout << testCaseNames[i] << ": \n"
                  << "Custom heapSort time: " << customTime << " ms\n"
                  << "std::sort_heap time: " << stlTime << " ms\n\n";
    }
}

int main() {
    testSorting();
    return 0;
}
