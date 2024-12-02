#ifndef HEAPSORT_H
#define HEAPSORT_H

#include <vector>
#include <algorithm>

template <typename T>
void heapSort(std::vector<T>& vec) {
    std::make_heap(vec.begin(), vec.end());  // 构建最大堆
    for (auto it = vec.end(); it != vec.begin(); --it) {
        std::pop_heap(vec.begin(), it);      // 将堆顶元素移至当前范围的末尾
    }
}

#endif