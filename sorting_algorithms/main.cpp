/**
 * 七种排序算法实现
 * 支持整数、字符、字符串的排序
 * 编译: g++ -std=c++17 -o sort main.cpp
 * 运行: ./sort
 */

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <type_traits>

using namespace std;

// ==================== 排序算法模板类 ====================

template<typename T>
class SortingAlgorithms {
private:
    // 交换两个元素
    static void swap(T& a, T& b) {
        T temp = a;
        a = b;
        b = temp;
    }

public:
    // 1. 冒泡排序 (Bubble Sort)
    static vector<T> bubbleSort(vector<T> arr) {
        int n = arr.size();
        for (int i = 0; i < n - 1; i++) {
            bool swapped = false;
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                    swapped = true;
                }
            }
            if (!swapped) break; // 优化：如果没有交换，说明已经有序
        }
        return arr;
    }

    // 2. 快速排序 (Quick Sort)
    static vector<T> quickSort(vector<T> arr) {
        quickSortHelper(arr, 0, arr.size() - 1);
        return arr;
    }

private:
    static void quickSortHelper(vector<T>& arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            quickSortHelper(arr, low, pi - 1);
            quickSortHelper(arr, pi + 1, high);
        }
    }

    static int partition(vector<T>& arr, int low, int high) {
        T pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (arr[j] <= pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return i + 1;
    }

public:
    // 3. 直接插入排序 (Insertion Sort)
    static vector<T> insertionSort(vector<T> arr) {
        int n = arr.size();
        for (int i = 1; i < n; i++) {
            T key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
        return arr;
    }

    // 4. 希尔排序 (Shell Sort)
    static vector<T> shellSort(vector<T> arr) {
        int n = arr.size();
        // 使用 Hibbard 增量序列
        for (int gap = n / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < n; i++) {
                T temp = arr[i];
                int j = i;
                while (j >= gap && arr[j - gap] > temp) {
                    arr[j] = arr[j - gap];
                    j -= gap;
                }
                arr[j] = temp;
            }
        }
        return arr;
    }

    // 5. 简单选择排序 (Selection Sort)
    static vector<T> selectionSort(vector<T> arr) {
        int n = arr.size();
        for (int i = 0; i < n - 1; i++) {
            int minIdx = i;
            for (int j = i + 1; j < n; j++) {
                if (arr[j] < arr[minIdx]) {
                    minIdx = j;
                }
            }
            if (minIdx != i) {
                swap(arr[i], arr[minIdx]);
            }
        }
        return arr;
    }

    // 6. 堆排序 (Heap Sort)
    static vector<T> heapSort(vector<T> arr) {
        int n = arr.size();
        // 构建最大堆
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(arr, n, i);
        }
        // 逐个提取元素
        for (int i = n - 1; i > 0; i--) {
            swap(arr[0], arr[i]);
            heapify(arr, i, 0);
        }
        return arr;
    }

private:
    static void heapify(vector<T>& arr, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left] > arr[largest]) {
            largest = left;
        }
        if (right < n && arr[right] > arr[largest]) {
            largest = right;
        }
        if (largest != i) {
            swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }

public:
    // 7. 两路归并排序 (Two-way Merge Sort)
    static vector<T> mergeSort(vector<T> arr) {
        if (arr.size() <= 1) return arr;
        mergeSortHelper(arr, 0, arr.size() - 1);
        return arr;
    }

private:
    static void mergeSortHelper(vector<T>& arr, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSortHelper(arr, left, mid);
            mergeSortHelper(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    }

    static void merge(vector<T>& arr, int left, int mid, int right) {
        vector<T> leftArr(arr.begin() + left, arr.begin() + mid + 1);
        vector<T> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);

        int i = 0, j = 0, k = left;
        while (i < leftArr.size() && j < rightArr.size()) {
            if (leftArr[i] <= rightArr[j]) {
                arr[k++] = leftArr[i++];
            } else {
                arr[k++] = rightArr[j++];
            }
        }
        while (i < leftArr.size()) {
            arr[k++] = leftArr[i++];
        }
        while (j < rightArr.size()) {
            arr[k++] = rightArr[j++];
        }
    }

public:
    // 输出数组
    static void printArray(const vector<T>& arr) {
        for (size_t i = 0; i < arr.size(); i++) {
            if (i > 0) cout << " ";
            cout << arr[i];
        }
        cout << endl;
    }

    // 执行所有排序并输出结果
    static void runAllSorts(const vector<T>& original) {
        // 1. 冒泡排序
        cout << "Bubble Sort" << endl;
        printArray(bubbleSort(original));

        // 2. 快速排序
        cout << "Quick Sort" << endl;
        printArray(quickSort(original));

        // 3. 直接插入排序
        cout << "Insertion Sort" << endl;
        printArray(insertionSort(original));

        // 4. 希尔排序
        cout << "Shell Sort" << endl;
        printArray(shellSort(original));

        // 5. 简单选择排序
        cout << "Selection Sort" << endl;
        printArray(selectionSort(original));

        // 6. 堆排序
        cout << "Heap Sort" << endl;
        printArray(heapSort(original));

        // 7. 两路归并排序
        cout << "Two-way Merge Sort" << endl;
        printArray(mergeSort(original));
    }
};

// ==================== 数据类型检测与解析 ====================

enum class DataType {
    INTEGER,
    CHARACTER,
    STRING
};

// 判断字符串是否为整数
bool isInteger(const string& s) {
    if (s.empty()) return false;
    size_t start = 0;
    if (s[0] == '-' || s[0] == '+') start = 1;
    if (start == s.size()) return false;
    for (size_t i = start; i < s.size(); i++) {
        if (!isdigit(s[i])) return false;
    }
    return true;
}

// 判断字符串是否为单个字符
bool isCharacter(const string& s) {
    return s.size() == 1;
}

// 检测数据类型
DataType detectDataType(const vector<string>& tokens) {
    bool allIntegers = true;
    bool allChars = true;

    for (const auto& token : tokens) {
        if (!isInteger(token)) allIntegers = false;
        if (!isCharacter(token)) allChars = false;
    }

    if (allIntegers) return DataType::INTEGER;
    if (allChars) return DataType::CHARACTER;
    return DataType::STRING;
}

// ==================== 主函数 ====================

int main() {
    int n;
    cin >> n;
    cin.ignore(); // 忽略换行符

    string line;
    getline(cin, line);

    // 解析输入数据
    vector<string> tokens;
    istringstream iss(line);
    string token;
    while (iss >> token) {
        tokens.push_back(token);
    }

    // 检测数据类型并执行排序
    DataType type = detectDataType(tokens);

    switch (type) {
        case DataType::INTEGER: {
            vector<int> data;
            for (const auto& t : tokens) {
                data.push_back(stoi(t));
            }
            SortingAlgorithms<int>::runAllSorts(data);
            break;
        }
        case DataType::CHARACTER: {
            vector<char> data;
            for (const auto& t : tokens) {
                data.push_back(t[0]);
            }
            SortingAlgorithms<char>::runAllSorts(data);
            break;
        }
        case DataType::STRING: {
            SortingAlgorithms<string>::runAllSorts(tokens);
            break;
        }
    }

    return 0;
}
