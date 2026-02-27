/**
 * @file main.cpp
 * @brief 七种排序算法程序入口
 * 
 * 支持整数、字符、字符串三种数据类型的排序
 * 编译: g++ -std=c++17 -I include -o sort main.cpp
 * 运行: ./sort
 * 调试模式（启用日志）: ./sort --debug
 */

#include <iostream>
#include <cstring>
#include "include/Logger.h"
#include "include/Sorter.h"
#include "include/InputParser.h"
#include "include/SortRunner.h"

using namespace std;

/**
 * @brief 打印使用帮助
 */
void printUsage(const char* programName) {
    cerr << "用法: " << programName << " [选项]" << endl;
    cerr << "选项:" << endl;
    cerr << "  --debug    启用调试日志输出" << endl;
    cerr << "  --help     显示此帮助信息" << endl;
}

/**
 * @brief 主函数
 */
int main(int argc, char* argv[]) {
    // 解析命令行参数
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--debug") == 0) {
            Logger::enable();
            Logger::setLevel(LogLevel::DEBUG);
            Logger::info("调试模式已启用");
        } else if (strcmp(argv[i], "--help") == 0) {
            printUsage(argv[0]);
            return 0;
        }
    }

    // 读取数据个数
    int n;
    if (!(cin >> n)) {
        cerr << "错误: 无法读取数据个数" << endl;
        Logger::error("无法读取数据个数");
        return 1;
    }

    // 验证 n 的有效性
    if (n <= 0) {
        cerr << "错误: 数据个数必须为正整数，当前值: " << n << endl;
        Logger::error("数据个数无效: " + to_string(n));
        return 1;
    }

    if (n > 100000) {
        cerr << "错误: 数据个数过大（最大支持 100000），当前值: " << n << endl;
        Logger::error("数据个数过大: " + to_string(n));
        return 1;
    }

    Logger::info("期望读取数据个数: " + to_string(n));

    // 读取数据（支持跨行输入）
    vector<string> tokens = InputParser::readTokens(cin, n);

    // 验证数据个数
    string errorMsg;
    if (!InputParser::validateCount(n, tokens.size(), errorMsg)) {
        cerr << "错误: " << errorMsg << endl;
        return 1;
    }

    // 如果数据过多，截取前 n 个
    if (tokens.size() > static_cast<size_t>(n)) {
        tokens.resize(n);
    }

    // 检测数据类型并执行排序
    DataType type = InputParser::detectDataType(tokens);

    switch (type) {
        case DataType::INTEGER: {
            auto result = InputParser::parseIntegers(tokens);
            if (!result.success) {
                cerr << "错误: " << result.errorMessage << endl;
                return 1;
            }
            SortRunner<int>::runAllSorts(result.data);
            break;
        }
        case DataType::CHARACTER: {
            auto result = InputParser::parseCharacters(tokens);
            if (!result.success) {
                cerr << "错误: " << result.errorMessage << endl;
                return 1;
            }
            SortRunner<char>::runAllSorts(result.data);
            break;
        }
        case DataType::STRING: {
            SortRunner<string>::runAllSorts(tokens);
            break;
        }
    }

    Logger::info("程序正常结束");
    return 0;
}
