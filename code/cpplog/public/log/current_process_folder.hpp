#pragma once

#include "cpplog_export.hpp"

#include <filesystem>

namespace cpplog::log
{

  CPPLOG_EXPORT [[nodiscard]] std::filesystem::path current_process_folder();
}