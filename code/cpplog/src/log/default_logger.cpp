#include "log/default_logger.hpp"

#include "log/level.hpp"
#include "log/conf.hpp"

#include <chrono>
#include <memory>

namespace cpplog::log
{
  using namespace std::chrono_literals;// Can declare easily time, ref 5s

  constexpr auto max_log_size = 1024 * 1024 * 10;// max_log_size 10mb
  constexpr auto max_log_file = 200000;// Maximum number of files allowed by spdlog.
  constexpr auto five_seconds = 5s;

  static inline conf::file log_file_configuration{.file_name = "cpplog.log",
                                                  .file_rotation = conf::rotation(max_log_file, max_log_size),
                                                  .backtrace_size = std::nullopt,
                                                  .flush_period = five_seconds};
  //!< Configuration is hardly set for now. Later on, if needed, we can load this configuration from a json file.

  static inline conf log_configuration{.log_level = level::debug,
                                       .file_configuration = log_file_configuration,
                                       .enable_console = true};

  logger &default_logger()
  {
    static logger instance(log_configuration);

    return instance;
  }

}