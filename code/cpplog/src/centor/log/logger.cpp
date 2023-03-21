#include "centor/log/logger.hpp"

#include "centor/log/conf.hpp"
#include "centor/log/current_process_folder.hpp"

#include <filesystem>
#include <magic_enum.hpp>
#include <memory>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

namespace centor::log
{
  struct logger::log_impl final
  {
    explicit log_impl(const log::conf &configuration);
    ~log_impl();

    std::shared_ptr<spdlog::logger> spd_logger;
  };

  logger::log_impl::log_impl(const log::conf &configuration)
  {
    std::vector<std::shared_ptr<spdlog::sinks::sink>> sinks;

    if (configuration.file_configuration && !configuration.file_configuration->file_name.empty())
    {
      const auto &file_configuration = configuration.file_configuration;
      const auto file_path = current_process_folder() / "log" / file_configuration->file_name;

      if (file_configuration->file_rotation)
        sinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
          file_path.string(), file_configuration->file_rotation->max_size,
          file_configuration->file_rotation->max_files));
      else
        sinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>(file_path.string()));
      if (file_configuration->backtrace_size)
        spdlog::enable_backtrace(*file_configuration->backtrace_size);
      if (file_configuration->flush_period)
        spdlog::flush_every(*file_configuration->flush_period);
      spdlog::flush_on(spdlog::level::critical);// Whenever a critical error appears, force flush before program exits
    }
    if (configuration.enable_console)
      sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
    spd_logger = std::make_shared<spdlog::logger>("centor_logger", sinks.begin(), sinks.end());
    spdlog::register_logger(spd_logger);
    spd_logger->set_pattern(configuration.pattern);
    spd_logger->set_level(spdlog::level::level_enum(magic_enum::enum_integer(configuration.log_level)));
  }

  logger::log_impl::~log_impl()
  {
    spdlog::drop(spd_logger->name());
  }

  logger::logger(const log::conf &configuration) : impl(std::make_unique<logger::log_impl>(configuration)) { }

  logger::~logger() = default;

  auto logger::current_level() const noexcept
  {
    return magic_enum::enum_cast<level>(impl->spd_logger->level());
  }

  void logger::change_level(level new_level) noexcept
  {
    impl->spd_logger->set_level(spdlog::level::level_enum(magic_enum::enum_integer(new_level)));
  }

  void logger::debug(std::string_view msg) const noexcept
  {
    impl->spd_logger->debug(msg);
  }

  void logger::info(std::string_view msg) const noexcept
  {
    impl->spd_logger->info(msg);
  }

  void logger::warning(std::string_view msg) const noexcept
  {
    impl->spd_logger->warn(msg);
  }

  void logger::error(std::string_view msg) const noexcept
  {
    impl->spd_logger->error(msg);
  }

  void logger::critical(std::string_view msg) const noexcept
  {
    impl->spd_logger->critical(msg);
  }

}