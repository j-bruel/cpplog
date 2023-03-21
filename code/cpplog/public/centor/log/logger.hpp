#pragma once

#include "cpplog_export.hpp"
#include "level.hpp"

#include <memory>
#include <string_view>

namespace centor::log
{
  struct conf;

  class CPPLOG_EXPORT logger final
  {
  public:
    explicit logger(const conf &configuration);
    ~logger();

    [[nodiscard]] auto current_level() const noexcept;
    void change_level(level new_level) noexcept;

    void debug(std::string_view msg) const noexcept;
    void info(std::string_view msg) const noexcept;
    void warning(std::string_view msg) const noexcept;
    void error(std::string_view msg) const noexcept;
    void critical(std::string_view msg) const noexcept;

  private:
    struct log_impl;
    std::unique_ptr<log_impl> impl;
  };

}