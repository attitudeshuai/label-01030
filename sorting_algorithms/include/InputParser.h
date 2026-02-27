/**
 * @file InputParser.h
 * @brief 输入解析工具类
 */

#ifndef INPUT_PARSER_H
#define INPUT_PARSER_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <cctype>
#include <climits>
#include "Logger.h"

/**
 * @brief 数据类型枚举
 */
enum class DataType {
    INTEGER,
    CHARACTER,
    STRING
};

/**
 * @brief 解析结果结构体
 */
template<typename T>
struct ParseResult {
    bool success;
    std::vector<T> data;
    std::string errorMessage;

    ParseResult() : success(false) {}
    ParseResult(const std::vector<T>& d) : success(true), data(d) {}
    ParseResult(const std::string& err) : success(false), errorMessage(err) {}
};

/**
 * @brief 输入解析器类
 */
class InputParser {
public:
    /**
     * @brief 判断字符串是否为有效整数
     * @param s 待检测字符串
     * @return 是否为整数
     */
    static bool isInteger(const std::string& s) {
        if (s.empty()) return false;
        size_t start = 0;
        if (s[0] == '-' || s[0] == '+') start = 1;
        if (start == s.size()) return false;
        for (size_t i = start; i < s.size(); i++) {
            if (!std::isdigit(static_cast<unsigned char>(s[i]))) return false;
        }
        return true;
    }

    /**
     * @brief 判断字符串是否为单个字符
     * @param s 待检测字符串
     * @return 是否为单字符
     */
    static bool isCharacter(const std::string& s) {
        return s.size() == 1;
    }

    /**
     * @brief 检测数据类型
     * @param tokens 字符串数组
     * @return 检测到的数据类型
     * 
     * 类型判定优先级：
     * 1. 如果所有 token 都是单字符 -> CHARACTER（包括单字符数字如 "1", "2"）
     * 2. 如果所有 token 都是有效整数（可以是多位数）-> INTEGER
     * 3. 否则 -> STRING
     * 
     * 注意：单字符数字（如 "1 2 3"）会被判定为 CHARACTER 而非 INTEGER，
     * 因为单字符输入更可能是字符排序场景。
     */
    static DataType detectDataType(const std::vector<std::string>& tokens) {
        if (tokens.empty()) {
            return DataType::STRING;
        }

        bool allChars = true;
        bool allIntegers = true;

        for (const auto& token : tokens) {
            if (!isCharacter(token)) allChars = false;
            if (!isInteger(token)) allIntegers = false;
        }

        // 优先判定为 CHARACTER（单字符优先）
        if (allChars) {
            Logger::info("检测到数据类型: CHARACTER");
            return DataType::CHARACTER;
        }
        // 其次判定为 INTEGER（多位数整数）
        if (allIntegers) {
            Logger::info("检测到数据类型: INTEGER");
            return DataType::INTEGER;
        }
        Logger::info("检测到数据类型: STRING");
        return DataType::STRING;
    }

    /**
     * @brief 从输入流读取 n 个数据（支持跨行输入）
     * @param is 输入流
     * @param n 期望读取的数据个数
     * @return 读取到的字符串数组
     */
    static std::vector<std::string> readTokens(std::istream& is, int n) {
        std::vector<std::string> tokens;
        std::string token;

        Logger::info("开始读取 " + std::to_string(n) + " 个数据");

        while (tokens.size() < static_cast<size_t>(n) && is >> token) {
            tokens.push_back(token);
        }

        Logger::info("实际读取到 " + std::to_string(tokens.size()) + " 个数据");
        return tokens;
    }

    /**
     * @brief 解析整数数组
     * @param tokens 字符串数组
     * @return 解析结果
     */
    static ParseResult<int> parseIntegers(const std::vector<std::string>& tokens) {
        std::vector<int> result;
        result.reserve(tokens.size());

        for (size_t i = 0; i < tokens.size(); i++) {
            try {
                size_t pos;
                long long val = std::stoll(tokens[i], &pos);
                
                // 检查是否完全解析
                if (pos != tokens[i].size()) {
                    std::string err = "第 " + std::to_string(i + 1) + " 个数据 '" 
                                    + tokens[i] + "' 包含非法字符";
                    Logger::error(err);
                    return ParseResult<int>(err);
                }
                
                // 检查整数范围
                if (val > INT_MAX || val < INT_MIN) {
                    std::string err = "第 " + std::to_string(i + 1) + " 个数据 '" 
                                    + tokens[i] + "' 超出整数范围";
                    Logger::error(err);
                    return ParseResult<int>(err);
                }
                
                result.push_back(static_cast<int>(val));
            } catch (const std::invalid_argument&) {
                std::string err = "第 " + std::to_string(i + 1) + " 个数据 '" 
                                + tokens[i] + "' 无法转换为整数";
                Logger::error(err);
                return ParseResult<int>(err);
            } catch (const std::out_of_range&) {
                std::string err = "第 " + std::to_string(i + 1) + " 个数据 '" 
                                + tokens[i] + "' 数值溢出";
                Logger::error(err);
                return ParseResult<int>(err);
            }
        }

        Logger::info("成功解析 " + std::to_string(result.size()) + " 个整数");
        return ParseResult<int>(result);
    }

    /**
     * @brief 解析字符数组
     * @param tokens 字符串数组
     * @return 解析结果
     */
    static ParseResult<char> parseCharacters(const std::vector<std::string>& tokens) {
        std::vector<char> result;
        result.reserve(tokens.size());

        for (const auto& t : tokens) {
            if (t.size() != 1) {
                std::string err = "数据 '" + t + "' 不是单个字符";
                Logger::error(err);
                return ParseResult<char>(err);
            }
            result.push_back(t[0]);
        }

        Logger::info("成功解析 " + std::to_string(result.size()) + " 个字符");
        return ParseResult<char>(result);
    }

    /**
     * @brief 验证数据个数
     * @param expected 期望个数
     * @param actual 实际个数
     * @return 是否匹配
     */
    static bool validateCount(int expected, size_t actual, std::string& errorMsg) {
        if (actual < static_cast<size_t>(expected)) {
            errorMsg = "数据不足: 期望 " + std::to_string(expected) 
                     + " 个，实际只有 " + std::to_string(actual) + " 个";
            Logger::error(errorMsg);
            return false;
        }
        if (actual > static_cast<size_t>(expected)) {
            Logger::warn("数据过多: 期望 " + std::to_string(expected) 
                       + " 个，实际有 " + std::to_string(actual) + " 个，将忽略多余数据");
        }
        return true;
    }
};

#endif // INPUT_PARSER_H
