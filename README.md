# 七种排序算法 C++ 实现

## How to Run

### 方式一：直接编译运行

#### Linux / macOS
```bash
cd sorting_algorithms
g++ -std=c++17 -I include -o sort main.cpp
./sort
```

#### Windows (MinGW-w64)

1. 安装 MinGW-w64：
   - 下载：https://www.mingw-w64.org/downloads/
   - 或使用 MSYS2：`pacman -S mingw-w64-ucrt-x86_64-gcc`
   - 确保 `g++` 在系统 PATH 中

2. 编译运行：
```cmd
cd sorting_algorithms
g++ -std=c++17 -I include -o sort.exe main.cpp
sort.exe
```

#### Windows (Visual Studio)
```cmd
cd sorting_algorithms
cl /EHsc /std:c++17 /I include main.cpp /Fe:sort.exe
sort.exe
```

### 方式二：Docker 运行（推荐，无需本地编译环境）

#### 交互式运行（手动输入）
```bash
docker-compose build
docker-compose run --rm sorting-algorithms
```
程序启动后需手动输入数据，例如：
```
5
4 3 1 2 5
```
输入完成后按 Ctrl+D (Linux/Mac) 或 Ctrl+Z (Windows) 结束输入。

#### 管道式运行（自动化测试）
```bash
# Linux/macOS
echo -e "5\n4 3 1 2 5" | docker run --rm -i $(docker build -q -f sorting_algorithms/Dockerfile sorting_algorithms)

# Windows PowerShell
"5`n4 3 1 2 5" | docker run --rm -i sorting-test

# Windows CMD
(echo 5 & echo 4 3 1 2 5) | docker run --rm -i sorting-test
```

#### 运行自动化测试
```bash
docker build -f sorting_algorithms/Dockerfile.test -t sorting-test ./sorting_algorithms
docker run --rm sorting-test
```

### 调试模式（启用日志）
```bash
./sort --debug
```

## Services

| 服务名 | 说明 | 运行方式 |
|--------|------|----------|
| sorting-algorithms | C++ 排序算法程序 | 交互式（需手动输入 n 和数据） |
| sorting-test | 自动化测试镜像 | 自动运行测试用例 |

## 测试账号

无需账号，直接运行即可。

## 题目内容

### 问题描述
输入n个数据（整数、字符或字符串），分别使用冒泡排序、快速排序、直接插入排序、希尔排序、简单选择排序、堆排序、两路归并排序对n个数据按照由小到大排序，输出排序结果。

### 输入形式
- 第1行输入一个整数，表示数据的数目
- 第2行输入n个数据，数据之间用空格间隔（支持跨行输入）

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
    ├── main.cpp              # 程序入口
    ├── include/
    │   ├── Logger.h          # 日志工具类
    │   ├── Sorter.h          # 七种排序算法模板类
    │   ├── InputParser.h     # 输入解析工具类
    │   └── SortRunner.h      # 排序执行器
    ├── Dockerfile            # 生产环境 Docker 配置
    ├── Dockerfile.test       # 测试环境 Docker 配置
    ├── run_tests.sh          # Linux/Mac 测试脚本
    ├── run_tests.bat         # Windows 测试脚本
    └── README.md
```

## 实现的排序算法

| 序号 | 算法名称 | 英文名称 | 时间复杂度(平均) | 空间复杂度 | 稳定性 |
|------|----------|----------|------------------|------------|--------|
| 1 | 冒泡排序 | Bubble Sort | O(n²) | O(1) | 稳定 |
| 2 | 快速排序 | Quick Sort | O(n log n) | O(log n) | 不稳定 |
| 3 | 直接插入排序 | Insertion Sort | O(n²) | O(1) | 稳定 |
| 4 | 希尔排序 | Shell Sort | O(n^1.3) | O(1) | 不稳定 |
| 5 | 简单选择排序 | Selection Sort | O(n²) | O(1) | 不稳定 |
| 6 | 堆排序 | Heap Sort | O(n log n) | O(1) | 不稳定 |
| 7 | 两路归并排序 | Two-way Merge Sort | O(n log n) | O(n) | 稳定 |

## 数据类型检测规则

程序自动检测输入数据类型，判定优先级如下：

| 优先级 | 类型 | 判定条件 | 示例 | 排序结果 |
|--------|------|----------|------|----------|
| 1 | CHARACTER | 所有数据都是单字符 | `a b c` 或 `1 2 3` | 按 ASCII 码排序 |
| 2 | INTEGER | 所有数据都是有效整数（可多位） | `10 20 30` 或 `-5 0 100` | 按数值排序 |
| 3 | STRING | 其他情况 | `apple banana` | 按字典序排序 |

**注意**：单字符数字（如 `1 2 3`）会被判定为 CHARACTER 按 ASCII 排序，结果与整数排序相同。如需明确整数排序，请使用多位数（如 `01 02 03`）。

## 特性

- 模块化设计：排序算法、输入解析、日志记录分离为独立模块
- 支持整数、字符、字符串三种数据类型，自动检测
- 健壮的错误处理：数据个数校验、整数转换异常捕获、数值溢出检测
- 支持跨行输入
- 日志机制：通过 `--debug` 参数启用调试日志
- 跨平台支持：提供 Docker 运行方式

## 测试

### Docker 测试（推荐）
```bash
cd sorting_algorithms
docker build -f Dockerfile.test -t sorting-test .
docker run --rm sorting-test
```

### 本地测试
```bash
cd sorting_algorithms
chmod +x run_tests.sh
./run_tests.sh
```

测试结果：13 个测试用例全部通过
