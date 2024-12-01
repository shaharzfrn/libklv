
#include "logger.h"

static std::string CurrentDateTime() {
  std::time_t now = std::time(nullptr);
  char buf[80];
  std::strftime(buf, sizeof(buf), "%Y-%m-%d %X", std::localtime(&now));
  return std::string(buf);
}

static std::string LogLevelToString(LogLevel level) {
  switch (level) {
  case LogLevel::DEBUG:
    return "DEBUG";
  case LogLevel::INFO:
    return "INFO";
  case LogLevel::WARNING:
    return "WARNING";
  case LogLevel::ERROR:
    return "ERROR";
  default:
    return "UNKNOWN";
  }
}

LoggerStream::LoggerStream(const LogLevel level, const LogLevel system_level,
                           std::ostream &output_stream, std::mutex &io_lock)
    : m_log_level(level), m_system_log_level(system_level),
      m_output_stream(output_stream), m_io_lock(io_lock) {}

LoggerStream::~LoggerStream() {

  if (m_system_log_level >= m_log_level) {

    std::lock_guard<std::mutex> guard(m_io_lock);
    std::string log_message = "[" + CurrentDateTime() + "] " +
                              LogLevelToString(m_log_level) + ": " +
                              m_stream.str() + "\n";

    // Log to the selected output stream
    m_output_stream << log_message;
  }
}

Logger::Logger() : m_output_stream(std::cout) {}

Logger &Logger::GetReference() {
  static Logger instance;
  return instance;
}
void Logger::SetLogLevel(const LogLevel level) {
  Logger::GetReference().m_system_log_level = level;
}

LoggerStream Logger::Log(const LogLevel level) {
  return LoggerStream(level, m_system_log_level, m_output_stream, m_io_lock);
}
