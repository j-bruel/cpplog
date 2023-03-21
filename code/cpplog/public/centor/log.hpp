#pragma once

#include "cpplog_export.hpp"
#include "log/default_logger.hpp"

#include <fmt/format.h>
#include <iostream>
#include <string_view>
#include <utility>

namespace centor::log
{

  template<typename... log_msg_args>
  [[nodiscard]] static auto format(std::string_view formatted_msg, const log_msg_args &...args) noexcept
  {
    if constexpr (sizeof...(args) != 0)
      return fmt::vformat(formatted_msg, fmt::make_format_args(args...));
    return formatted_msg;
  }

  template<typename... log_msg_args>
  inline void debug(std::string_view formatted_msg, const log_msg_args &...args)
  {
    centor::log::default_logger().debug(format(formatted_msg, args...));
  }

  template<typename... log_msg_args>
  inline void info(std::string_view formatted_msg, const log_msg_args &...args)
  {
    centor::log::default_logger().info(format(formatted_msg, args...));
  }

  template<typename... log_msg_args>
  inline void warning(std::string_view formatted_msg, const log_msg_args &...args)
  {
    centor::log::default_logger().warning(format(formatted_msg, args...));
  }

  template<typename... log_msg_args>
  inline void error(std::string_view formatted_msg, const log_msg_args &...args)
  {
    centor::log::default_logger().error(format(formatted_msg, args...));
  }

  template<typename... log_msg_args>
  inline void critical(std::string_view formatted_msg, const log_msg_args &...args)
  {
    centor::log::default_logger().critical(format(formatted_msg, args...));
  }

}