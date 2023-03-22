#pragma once

#include "level.hpp"

#include <chrono>
#include <filesystem>
#include <optional>

namespace cpplog::log
{
  struct conf final
  {
    struct rotation final
    {
      explicit rotation(std::size_t max_allowed_files, std::size_t max_size_per_file) :
        max_files(max_allowed_files), max_size(max_size_per_file)
      {
      }

      std::size_t max_files;
      std::size_t max_size;
    };

    struct file final
    {
      std::string file_name;
      std::optional<rotation> file_rotation;
      std::optional<std::size_t> backtrace_size;
      std::optional<std::chrono::seconds> flush_period;
    };

    level log_level = level::off;
    std::string pattern = "[%Y-%m-%d %H:%M:%S.%f %z][%^%l%$][%P][%t]%v";
    std::optional<file> file_configuration;
    bool enable_console = false;
  };
}