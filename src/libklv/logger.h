
#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <ctime>
#include <iostream>
#include <mutex>
#include <sstream>

enum class LogLevel { NONE, ERROR, WARNING, INFO, DEBUG };

class LoggerStream {

  friend class Logger;

public:
  ~LoggerStream();

  template <typename T> LoggerStream &operator<<(const T &message) {
    if (m_system_log_level >= m_log_level) {
      m_stream << message;
    }
    return *this;
  }

private:
  LoggerStream(const LogLevel level, const LogLevel system_level,
               std::ostream &output_stream, std::mutex &io_lock);

  const LogLevel m_system_log_level;
  const LogLevel m_log_level;

  std::mutex &m_io_lock;
  std::ostream &m_output_stream;
  std::ostringstream m_stream;
};

class Logger {

public:
  static Logger &GetReference();
  static void SetLogLevel(const LogLevel level);

  LoggerStream Log(const LogLevel level);

private:
  Logger();

  LogLevel m_system_log_level = LogLevel::ERROR;

  std::ostream &m_output_stream;
  std::mutex m_io_lock;
};

#define LOG_ERROR() Logger::GetReference().Log(LogLevel::ERROR)
#define LOG_WARNING() Logger::GetReference().Log(LogLevel::WARNING)
#define LOG_INFO() Logger::GetReference().Log(LogLevel::INFO)
#define LOG_DEBUG() Logger::GetReference().Log(LogLevel::DEBUG)

#endif //__LOGGER_H__
