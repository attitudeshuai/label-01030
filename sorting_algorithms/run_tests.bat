@echo off
chcp 65001 >nul
setlocal enabledelayedexpansion

echo ==========================================
echo 七种排序算法测试
echo ==========================================
echo.

REM 检查编译器是否可用
where g++ >nul 2>&1
if %errorlevel% neq 0 (
    echo [警告] 未检测到 g++ 编译器
    echo.
    echo 请选择以下方式之一运行测试:
    echo.
    echo 方式1: 安装 MinGW-w64 并添加到 PATH
    echo        下载地址: https://www.mingw-w64.org/downloads/
    echo.
    echo 方式2: 使用 Docker 运行测试 (推荐)
    echo        docker build -f Dockerfile.test -t sorting-test .
    echo        docker run --rm sorting-test
    echo.
    echo 方式3: 使用 Visual Studio 编译
    echo        cl /EHsc /std:c++17 /I include main.cpp /Fe:sort.exe
    echo.
    exit /b 1
)

echo 编译中...
g++ -std=c++17 -I include -o sort.exe main.cpp
if %errorlevel% neq 0 (
    echo 编译失败!
    exit /b 1
)
echo 编译成功!
echo.

set passed=0
set failed=0

echo ------------------------------------------
echo 测试 1: 基本整数排序
echo ------------------------------------------
(echo 5& echo 4 3 1 2 5) | sort.exe
echo.

echo ------------------------------------------
echo 测试 2: 已排序数组
echo ------------------------------------------
(echo 5& echo 1 2 3 4 5) | sort.exe
echo.

echo ------------------------------------------
echo 测试 3: 逆序数组
echo ------------------------------------------
(echo 5& echo 5 4 3 2 1) | sort.exe
echo.

echo ------------------------------------------
echo 测试 4: 包含重复元素
echo ------------------------------------------
(echo 7& echo 3 1 4 1 5 9 2) | sort.exe
echo.

echo ------------------------------------------
echo 测试 5: 包含负数
echo ------------------------------------------
(echo 6& echo -3 5 -1 0 2 -4) | sort.exe
echo.

echo ------------------------------------------
echo 测试 6: 单个元素
echo ------------------------------------------
(echo 1& echo 42) | sort.exe
echo.

echo ------------------------------------------
echo 测试 7: 两个元素
echo ------------------------------------------
(echo 2& echo 9 1) | sort.exe
echo.

echo ------------------------------------------
echo 测试 8: 字符排序
echo ------------------------------------------
(echo 5& echo e d c b a) | sort.exe
echo.

echo ------------------------------------------
echo 测试 9: 字符串排序
echo ------------------------------------------
(echo 4& echo banana apple cherry date) | sort.exe
echo.

echo ------------------------------------------
echo 测试 10: 大数据量
echo ------------------------------------------
(echo 10& echo 100 23 45 67 89 12 34 56 78 90) | sort.exe
echo.

echo ------------------------------------------
echo 测试 11: 跨行输入
echo ------------------------------------------
(echo 5& echo 1& echo 2& echo 3& echo 4& echo 5) | sort.exe
echo.

echo ------------------------------------------
echo 测试 12: 错误处理-数据不足
echo ------------------------------------------
(echo 5& echo 1 2 3) | sort.exe
echo.

echo ------------------------------------------
echo 测试 13: 错误处理-无效n值
echo ------------------------------------------
(echo -1& echo 1 2 3) | sort.exe
echo.

echo ==========================================
echo 测试完成
echo ==========================================

del sort.exe 2>nul
