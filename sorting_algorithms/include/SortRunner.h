/**
 * @file SortRunner.h
 * @brief 排序执行器，负责运行所有排序算法并输出结果
 */

#ifndef SORT_RUNNER_H
#define SORT_RUNNER_H

#include <iostream>
#include <vector>
#include "Sorter.h"
#include "Logger.h"

/**
 * @brief 排序执行器类
 */
template<typename T>
class SortRunner {
public:
    /**
     * @brief 输出数组内容
     * @param arr 待输出数组
     * @param os 输出流
     */
    static void printArray(const std::vector<T>& arr, std::ostream& os = std::cout) {
        for (size_t i = 0; i < arr.size(); i++) {
            if (i > 0) os << " ";
            os << arr[i];
        }
        os << std::endl;
    }

    /**
     * @brief 执行所有排序算法并输出结果
     * @param original 原始数据
     * @param os 输出流
     */
    static void runAllSorts(const std::vector<T>& original, std::ostream& os = std::cout) {
        Logger::info("开始执行七种排序算法");

        // 1. 冒泡排序
        os << "Bubble Sort" << std::endl;
        printArray(Sorter<T>::bubbleSort(original), os);

        // 2. 快速排序
        os << "Quick Sort" << std::endl;
        printArray(Sorter<T>::quickSort(original), os);

        // 3. 直接插入排序
        os << "Insertion Sort" << std::endl;
        printArray(Sorter<T>::insertionSort(original), os);

        // 4. 希尔排序
        os << "Shell Sort" << std::endl;
        printArray(Sorter<T>::shellSort(original), os);

        // 5. 简单选择排序
        os << "Selection Sort" << std::endl;
        printArray(Sorter<T>::selectionSort(original), os);

        // 6. 堆排序
        os << "Heap Sort" << std::endl;
        printArray(Sorter<T>::heapSort(original), os);

        // 7. 两路归并排序
        os << "Two-way Merge Sort" << std::endl;
        printArray(Sorter<T>::mergeSort(original), os);

        Logger::info("所有排序算法执行完成");
    }
};

#endif // SORT_RUNNER_H
