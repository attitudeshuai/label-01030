# 七种排序算法 C++ 实现

## How to Run

### 方式一：直接编译运行
```bash
cd sorting_algorithms
g++ -std=c++17 -o sort main.cpp
./sort
```

### 方式二：Docker 运行
```bash
docker-compose build
docker-compose run --rm sorting-algorithms
```

输入示例：
```
5
4 3 1 2 5
```

## Services

| 服务名 | 说明 |
|--------|------|
| sorting-algorithms | C++ 排序算法程序（交互式命令行） |

## 测试账号

无需账号，直接运行即可。

## 题目内容

### 问题描述
输入n个数据（整数、字符或字符串），分别使用冒泡排序、快速排序、直接插入排序、希尔排序、简单选择排序、堆排序、两路归并排序对n个数据按照由小到大排序，输出排序结果。

### 输入形式
- 第1行输入一个整数，表示数据的数目
- 第2行输入n个数据，数据之间用空格间隔

### 输出形式
- 第1行输出排序算法1的名称
- 第2行按照由小到大的顺序输出n个数据，数据之间用1个空格间隔
- 以此类推

### 样例输入
```
5
4 3 1 2 5
```

### 样例输出
```
Bubble Sort
1 2 3 4 5
Quick Sort
1 2 3 4 5
Insertion Sort
1 2 3 4 5
Shell Sort
1 2 3 4 5
Selection Sort
1 2 3 4 5
Heap Sort
1 2 3 4 5
Two-way Merge Sort
1 2 3 4 5
```

---

## 项目结构

```
.
├── README.md
├── docker-compose.yml
├── .gitignore
├── label-01030.md
└── sorting_algorithms/
    ├── main.cpp
    ├── Dockerfile
    └── README.md
```

## 实现的排序算法

1. **冒泡排序 (Bubble Sort)** - 相邻元素比较交换
2. **快速排序 (Quick Sort)** - 分治法，选取基准元素划分
3. **直接插入排序 (Insertion Sort)** - 将元素插入已排序序列
4. **希尔排序 (Shell Sort)** - 缩小增量排序
5. **简单选择排序 (Selection Sort)** - 每次选择最小元素
6. **堆排序 (Heap Sort)** - 利用堆数据结构
7. **两路归并排序 (Two-way Merge Sort)** - 分治法，合并有序子序列

## 特性

- 支持整数、字符、字符串三种数据类型
- 自动检测输入数据类型
- 使用 C++ 模板实现通用排序
