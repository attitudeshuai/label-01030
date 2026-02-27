#!/bin/bash
# 自动化测试脚本

echo "=========================================="
echo "七种排序算法测试"
echo "=========================================="

# 编译
echo "编译中..."
g++ -std=c++17 -o sort main.cpp
if [ $? -ne 0 ]; then
    echo "编译失败!"
    exit 1
fi
echo "编译成功!"
echo ""

# 测试用例数组
declare -a test_names=(
    "基本整数排序"
    "已排序数组"
    "逆序数组"
    "包含重复元素"
    "包含负数"
    "单个元素"
    "两个元素"
    "字符排序"
    "字符串排序"
    "大数据量"
)

declare -a test_inputs=(
    "5\n4 3 1 2 5"
    "5\n1 2 3 4 5"
    "5\n5 4 3 2 1"
    "7\n3 1 4 1 5 9 2"
    "6\n-3 5 -1 0 2 -4"
    "1\n42"
    "2\n9 1"
    "5\ne d c b a"
    "4\nbanana apple cherry date"
    "10\n100 23 45 67 89 12 34 56 78 90"
)

declare -a expected_outputs=(
    "1 2 3 4 5"
    "1 2 3 4 5"
    "1 2 3 4 5"
    "1 1 2 3 4 5 9"
    "-4 -3 -1 0 2 5"
    "42"
    "1 9"
    "a b c d e"
    "apple banana cherry date"
    "12 23 34 45 56 67 78 89 90 100"
)

passed=0
failed=0

for i in "${!test_names[@]}"; do
    echo "----------------------------------------"
    echo "测试 $((i+1)): ${test_names[$i]}"
    echo "----------------------------------------"
    
    # 运行测试
    output=$(echo -e "${test_inputs[$i]}" | ./sort)
    
    # 检查每种排序算法的输出
    expected="${expected_outputs[$i]}"
    
    # 验证所有7种排序结果
    all_correct=true
    while IFS= read -r line; do
        if [[ "$line" == "$expected" ]]; then
            continue
        elif [[ "$line" == *"Sort"* ]]; then
            continue
        else
            if [[ -n "$line" ]]; then
                all_correct=false
            fi
        fi
    done <<< "$output"
    
    # 简单验证：检查输出中是否包含预期结果7次
    count=$(echo "$output" | grep -c "^${expected}$" 2>/dev/null || echo "0")
    
    if [ "$count" -eq 7 ]; then
        echo "✓ 通过"
        ((passed++))
    else
        echo "✗ 失败"
        echo "输入: ${test_inputs[$i]}"
        echo "预期每行排序结果: $expected"
        echo "实际输出:"
        echo "$output"
        ((failed++))
    fi
    echo ""
done

echo "=========================================="
echo "测试结果: $passed 通过, $failed 失败"
echo "=========================================="

# 清理
rm -f sort

exit $failed
