#pragma once

#include <iostream>
#include <string_view>

namespace centor::log
{

  template<typename... Args>
  inline void debug(std::string_view formatted_msg, const Args &...args)
  {
    std::cout << "debug" << std::endl;
  }

  template<typename... Args>
  inline void info(std::string_view formatted_msg, const Args &...args)
  {
    std::cout << "info" << std::endl;
  }

  template<typename... Args>
  inline void warning(std::string_view formatted_msg, const Args &...args)
  {
    std::cout << "warning" << std::endl;
  }

  template<typename... Args>
  inline void error(std::string_view formatted_msg, const Args &...args)
  {
    std::cout << "error" << std::endl;
  }

  template<typename... Args>
  inline void critical(std::string_view formatted_msg, const Args &...args)
  {
    std::cout << "critical" << std::endl;
  }

}