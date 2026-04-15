/**
 * @file Sorter.h
 * @brief 七种排序算法模板类
 */

#ifndef SORTER_H
#define SORTER_H

#include <vector>
#include <string>
#include "Logger.h"

template<typename T>
class Sorter {
private:
    static void swapElements(T& a, T& b) {
        T temp = a;
        a = b;
        b = temp;
    }

    // ==================== 快速排序辅助函数 ====================
    static void quickSortHelper(std::vector<T>& arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            quickSortHelper(arr, low, pi - 1);
            quickSortHelper(arr, pi + 1, high);
        }
    }

    static int partition(std::vector<T>& arr, int low, int high) {
        T pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (arr[j] <= pivot) {
                i++;
                swapElements(arr[i], arr[j]);
            }
        }
        swapElements(arr[i + 1], arr[high]);
        return i + 1;
    }

    // ==================== 堆排序辅助函数 ====================
    static void heapify(std::vector<T>& arr, int n, int i) {
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
            swapElements(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }

    // ==================== 归并排序辅助函数 ====================
    static void mergeSortHelper(std::vector<T>& arr, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSortHelper(arr, left, mid);
            mergeSortHelper(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    }

    static void merge(std::vector<T>& arr, int left, int mid, int right) {
        std::vector<T> leftArr(arr.begin() + left, arr.begin() + mid + 1);
        std::vector<T> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);

        size_t i = 0, j = 0;
        int k = left;
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
    /**
     * @brief 冒泡排序 (Bubble Sort)
     * @param arr 待排序数组（传值，不修改原数组）
     * @return 排序后的数组
     */
    static std::vector<T> bubbleSort(std::vector<T> arr) {
        Logger::debug("执行冒泡排序，数据量: " + std::to_string(arr.size()));
        int n = static_cast<int>(arr.size());
        for (int i = 0; i < n - 1; i++) {
            bool swapped = false;
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    swapElements(arr[j], arr[j + 1]);
                    swapped = true;
                }
            }
            if (!swapped) break;
        }
        Logger::debug("冒泡排序完成");
        return arr;
    }

    /**
     * @brief 快速排序 (Quick Sort)
     * @param arr 待排序数组
     * @return 排序后的数组
     */
    static std::vector<T> quickSort(std::vector<T> arr) {
        Logger::debug("执行快速排序，数据量: " + std::to_string(arr.size()));
        if (!arr.empty()) {
            quickSortHelper(arr, 0, static_cast<int>(arr.size()) - 1);
        }
        Logger::debug("快速排序完成");
        return arr;
    }

    /**
     * @brief 直接插入排序 (Insertion Sort)
     * @param arr 待排序数组
     * @return 排序后的数组
     */
    static std::vector<T> insertionSort(std::vector<T> arr) {
        Logger::debug("执行插入排序，数据量: " + std::to_string(arr.size()));
        int n = static_cast<int>(arr.size());
        for (int i = 1; i < n; i++) {
            T key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
        Logger::debug("插入排序完成");
        return arr;
    }

    /**
     * @brief 希尔排序 (Shell Sort)
     * @note 使用希尔原始增量序列 (gap = n/2, n/4, ..., 1)
     * @param arr 待排序数组
     * @return 排序后的数组
     */
    static std::vector<T> shellSort(std::vector<T> arr) {
        Logger::debug("执行希尔排序，数据量: " + std::to_string(arr.size()));
        int n = static_cast<int>(arr.size());
        // 使用希尔原始增量序列: n/2, n/4, ..., 1
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
        Logger::debug("希尔排序完成");
        return arr;
    }

    /**
     * @brief 简单选择排序 (Selection Sort)
     * @param arr 待排序数组
     * @return 排序后的数组
     */
    static std::vector<T> selectionSort(std::vector<T> arr) {
        Logger::debug("执行选择排序，数据量: " + std::to_string(arr.size()));
        int n = static_cast<int>(arr.size());
        for (int i = 0; i < n - 1; i++) {
            int minIdx = i;
            for (int j = i + 1; j < n; j++) {
                if (arr[j] < arr[minIdx]) {
                    minIdx = j;
                }
            }
            if (minIdx != i) {
                swapElements(arr[i], arr[minIdx]);
            }
        }
        Logger::debug("选择排序完成");
        return arr;
    }

    /**
     * @brief 堆排序 (Heap Sort)
     * @param arr 待排序数组
     * @return 排序后的数组
     */
    static std::vector<T> heapSort(std::vector<T> arr) {
        Logger::debug("执行堆排序，数据量: " + std::to_string(arr.size()));
        int n = static_cast<int>(arr.size());
        // 构建最大堆
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(arr, n, i);
        }
        // 逐个提取元素
        for (int i = n - 1; i > 0; i--) {
            swapElements(arr[0], arr[i]);
            heapify(arr, i, 0);
        }
        Logger::debug("堆排序完成");
        return arr;
    }

    /**
     * @brief 两路归并排序 (Two-way Merge Sort)
     * @param arr 待排序数组
     * @return 排序后的数组
     */
    static std::vector<T> mergeSort(std::vector<T> arr) {
        Logger::debug("执行归并排序，数据量: " + std::to_string(arr.size()));
        if (arr.size() <= 1) return arr;
        mergeSortHelper(arr, 0, static_cast<int>(arr.size()) - 1);
        Logger::debug("归并排序完成");
        return arr;
    }
};

#endif // SORTER_H
