#include <iostream>
#include <vector>
#include <functional>
#include <random>
#include <chrono>
#include <cstdlib>
#include <string>

    // 找到大于n的下一个质数
    int nextPrime(int n) {
        // 一个简单的质数检查函数
        while (true) {
            bool isPrime = true;
            for (int i = 2; i * i <= n; ++i) {
                if (n % i == 0) {
                    isPrime = false;
                    break;
                }
            }
            if (isPrime) return n;
            ++n;
        }
    }

template <typename AnyType>
class HashEntry {
public:
    AnyType element;  // 哈希表元素
    bool isActive;    // 元素是否有效

    // 默认构造函数，初始化元素和活跃状态
    HashEntry(const AnyType &e = AnyType(), bool a = false)
        : element{e}, isActive{a} {}

    // 移动构造函数，初始化元素和活跃状态
    HashEntry(AnyType &&e, bool a = false)
        : element{std::move(e)}, isActive{a} {}
};

template <typename AnyType, typename HashFamily>
class CuckooHashTable {
public:
    // 构造函数，初始化哈希表大小，并设置哈希函数数量和重哈希次数
    explicit CuckooHashTable(int size = 101)
        : array(nextPrime(size)), numHashFunctions(hashFunctions.getNumberOfFunctions()), rehashes(0) {
        makeEmpty();
    }

    // 清空哈希表
    void makeEmpty() {
        currentSize = 0;
        for (auto &entry : array)
            entry.isActive = false;
    }

    // 查找元素是否在哈希表中
    bool contains(const AnyType &x) const {
        return findPos(x) != -1;
    }

    // 从哈希表中移除元素
    bool remove(const AnyType &x) {
        int currentPos = findPos(x);
        if (!isActive(currentPos)) return false;
        array[currentPos].isActive = false;
        --currentSize;
        return true;
    }

    // 插入元素（左值）
    bool insert(const AnyType &x) {
        if (contains(x)) return false;
        if (currentSize >= array.size() * MAX_LOAD) expand();
        return insertHelper(x);
    }

    // 插入元素（右值）
    bool insert(AnyType &&x) {
        if (contains(x)) return false;
        if (currentSize >= array.size() * MAX_LOAD) expand();
        return insertHelper(std::move(x));
    }

private:
    static const double MAX_LOAD;  // 最大负载因子
    static const int ALLOWED_REHASHES;  // 允许的最大重哈希次数
    int currentSize;  // 当前元素数量
    int numHashFunctions;  // 哈希函数的数量
    int rehashes;  // 重哈希次数
    std::vector<HashEntry<AnyType>> array;  // 哈希表数组
    HashFamily hashFunctions;  // 哈希函数

    // 根据哈希函数和索引计算哈希值
    size_t myhash(const AnyType &x, int which) const {
        return hashFunctions.hash(x, which) % array.size();
    }

    // 查找元素的位置，返回该位置的索引
    int findPos(const AnyType &x) const {
        for (int i = 0; i < numHashFunctions; ++i) {
            int pos = myhash(x, i);
            if (isActive(pos) && array[pos].element == x)
                return pos;
        }
        return -1;
    }

    // 检查当前位置是否有效
    bool isActive(int currentPos) const {
        return currentPos != -1 && array[currentPos].isActive;
    }

    // 插入元素的辅助函数
    bool insertHelper(const AnyType &x) {
        const int COUNT_LIMIT = 100;  // 最大尝试次数
        AnyType currentItem = x;
        while (true) {
            int lastPos = -1;
            int pos;
            for (int count = 0; count < COUNT_LIMIT; ++count) {//查看是否需要重哈希
                for (int i = 0; i < numHashFunctions; ++i) {
                    pos = myhash(currentItem, i);
                    if (!isActive(pos)) {
                        array[pos] = HashEntry<AnyType>(std::move(currentItem), true);
                        ++currentSize;
                        return true;
                    }
                }
            }

            // 如果插入失败，则将当前元素逐出并交换
            int i = 0;
            do {
                pos = myhash(currentItem, rand() % numHashFunctions);
            } while (pos == lastPos && i++ < 5);

            lastPos = pos;
            std::swap(currentItem, array[pos].element);
        }

        // 如果重哈希次数超过上限，则扩展哈希表
        if (++rehashes > ALLOWED_REHASHES) {
            expand();
            rehashes = 0;
        } else {
            rehash();
        }
    }

    // 扩展哈希表
    void expand() {
        rehash(static_cast<int>(array.size() / MAX_LOAD));
    }

    // 重新哈希
    void rehash() {
        hashFunctions.generateNewFunctions();
        rehash(array.size());
    }

    // 根据新大小重新哈希
    void rehash(int newSize) {
        std::vector<HashEntry<AnyType>> oldArray = array;
        array.resize(nextPrime(newSize));
        for (auto &entry : array)
            entry.isActive = false;

        currentSize = 0;
        for (auto &entry : oldArray) {
            if (entry.isActive)
                insert(std::move(entry.element));
        }
    }


};

// 哈希表的最大负载因子
template <typename AnyType, typename HashFamily>
const double CuckooHashTable<AnyType, HashFamily>::MAX_LOAD = 0.40;

// 允许的最大重哈希次数
template <typename AnyType, typename HashFamily>
const int CuckooHashTable<AnyType, HashFamily>::ALLOWED_REHASHES = 5;

// 哈希函数族的类定义
template <typename AnyType>
class CuckooHashFamily {
public:
    size_t hash(const AnyType &x, int which) const;  // 哈希函数
    int getNumberOfFunctions();  // 获取哈希函数的数量
    void generateNewFunctions();  // 生成新的哈希函数
};

// 字符串哈希函数
template <int count>
class StringHashFamily {
public:
    StringHashFamily() : MULTIPLIERS(count) {
        generateNewFunctions();
    }

    int getNumberOfFunctions() const { return count; }

    // 生成新的哈希函数
    void generateNewFunctions() {
        for (auto &mult : MULTIPLIERS)
            mult = rand(); //随机生成倍数
    }

    // 字符串哈希函数
    size_t hash(const std::string &x, int which) const {
        const int multiplier = MULTIPLIERS[which];
        size_t hashVal = 0;
        for (auto ch : x)
            hashVal = multiplier * hashVal + ch; //horner
        return hashVal;
    }

private:
    std::vector<int> MULTIPLIERS;
};


std::string generateRandomString(int length) {
    const std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    std::string result;
    result.resize(length);
    
    for (int i = 0; i < length; ++i) {
        result[i] = chars[rand() % chars.size()];
    }
    return result;
}

// 测试不同负载因子的哈希表操作
void testCuckooHashTable(int numElements, double loadFactor) {
    const int tableSize = nextPrime(static_cast<int>(numElements / loadFactor));
    
    // 创建哈希表，表大小依负载因子而定
    CuckooHashTable<std::string, StringHashFamily<3>> hashTable(tableSize);
    
    // 生成待插入的随机字符串列表
    std::vector<std::string> testData;
    for (int i = 0; i < numElements; ++i) {
        testData.push_back(generateRandomString(30));  // 每个字符串的长度为30
    }
    
    // 插入元素到哈希表
    auto startInsert = std::chrono::high_resolution_clock::now();
    for (const auto& str : testData) {
        hashTable.insert(str);
    }
    auto endInsert = std::chrono::high_resolution_clock::now();
    
    // 测试"contains"操作
    auto startContains = std::chrono::high_resolution_clock::now();
    for (const auto& str : testData) {
        hashTable.contains(str);
    }
    auto endContains = std::chrono::high_resolution_clock::now();
    
    // 测试"remove"操作
    auto startRemove = std::chrono::high_resolution_clock::now();
    for (const auto& str : testData) {
        hashTable.remove(str);
    }
    auto endRemove = std::chrono::high_resolution_clock::now();
    
    // 计算并输出每个操作的耗时
    auto insertDuration = std::chrono::duration_cast<std::chrono::milliseconds>(endInsert - startInsert).count();
    auto containsDuration = std::chrono::duration_cast<std::chrono::milliseconds>(endContains - startContains).count();
    auto removeDuration = std::chrono::duration_cast<std::chrono::milliseconds>(endRemove - startRemove).count();
    
    std::cout << "Load Factor: " << loadFactor << "\n";
    std::cout << "Insert Time: " << insertDuration << " ms\n";
    std::cout << "Contains Time: " << containsDuration << " ms\n";
    std::cout << "Remove Time: " << removeDuration << " ms\n";
    std::cout << "----------------------------------\n";
}
