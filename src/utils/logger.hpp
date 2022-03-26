// SPDX-License-Identifier: MIT

#pragma once

#include <cstdio>
#include <string_view>

/*
 * How to use logging:
 * For logging we use printf like macro's.
 * Most of the logging should be used with LOG, WARNING and ERROR, but there are also two special ones: DBG_LOG and TEST_LOG
 * - LOG:      Anything that is relevant when reading the logs but is not odd.
 * - WARNING:  Something odd but not nessesary a bug.
 * - ERROR:    A runtime detected problem.
 * - DBG_LOG:  A log message relevant when debugging certain subsystems. These are usually disabled but can be enabled on a file basis.
 * - TEST_LOG: A log message specifically for tests. They will not compile in release, forcing the user to remove it.
 */

#define LOG(format, ...) utils::logger::log_impl(utils::logger::LogLevel::Log, __FILE__, __LINE__, format, __VA_ARGS__)
#define WARNING(format, ...) utils::logger::log_impl(utils::logger::LogLevel::Warning, __FILE__, __LINE__, format, __VA_ARGS__)
#define ERROR(format, ...) utils::logger::log_impl(utils::logger::LogLevel::Error, __FILE__, __LINE__, format, __VA_ARGS__)

#ifdef ENABLE_DBG_LOG
#define DBG_LOG(format, ...) utils::logger::log_impl(utils::logger::LogLevel::DebugLog, __FILE__, __LINE__, format, __VA_ARGS__)
#else
#define DBG_LOG(format, ...)
#endif

#ifdef _DEBUG
#define TEST_LOG(format, ...) utils::logger::log_impl(utils::logger::LogLevel::TestLog, __FILE__, __LINE__, format, __VA_ARGS__)
#endif

namespace utils::logger {
enum class LogLevel {
    Log,
    TestLog,
    DebugLog,
    Warning,
    Error,
};

void log_impl2(LogLevel level, const char *file, int line, std::string_view msg);

inline void log_impl(LogLevel level, const char *file, int line, const char *format, auto... args) {
    const int MAX_BUFFER = 1024;
    char buffer[MAX_BUFFER];
    snprintf(buffer, MAX_BUFFER, format, args...);
    log_impl2(level, file, line, buffer);
}
} // namespace utils::logger
