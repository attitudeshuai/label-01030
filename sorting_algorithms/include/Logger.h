/**
 * @file Logger.h
 * @brief 简易日志工具类
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>

enum class LogLevel {
    DEBUG,
    INFO,
    WARN,
    ERROR
};

class Logger {
private:
    static LogLevel currentLevel;
    static bool enabled;

    static std::string getCurrentTime() {
        std::time_t now = std::time(nullptr);
        std::tm* ltm = std::localtime(&now);
        std::ostringstream oss;
        oss << std::put_time(ltm, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

    static std::string levelToString(LogLevel level) {
        switch (level) {
            case LogLevel::DEBUG: return "DEBUG";
            case LogLevel::INFO:  return "INFO ";
            case LogLevel::WARN:  return "WARN ";
            case LogLevel::ERROR: return "ERROR";
            default: return "UNKNOWN";
        }
    }

public:
    static void setLevel(LogLevel level) { currentLevel = level; }
    static void enable() { enabled = true; }
    static void disable() { enabled = false; }

    static void log(LogLevel level, const std::string& message) {
        if (!enabled || level < currentLevel) return;
        std::cerr << "[" << getCurrentTime() << "] "
                  << "[" << levelToString(level) << "] "
                  << message << std::endl;
    }

    static void debug(const std::string& msg) { log(LogLevel::DEBUG, msg); }
    static void info(const std::string& msg)  { log(LogLevel::INFO, msg); }
    static void warn(const std::string& msg)  { log(LogLevel::WARN, msg); }
    static void error(const std::string& msg) { log(LogLevel::ERROR, msg); }
};

// 静态成员初始化
inline LogLevel Logger::currentLevel = LogLevel::INFO;
inline bool Logger::enabled = false;

#endif // LOGGER_H
