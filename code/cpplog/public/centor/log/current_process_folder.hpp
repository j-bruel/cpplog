#pragma once

#include "cpplog_export.hpp"

#include <filesystem>

namespace centor::log
{

  CPPLOG_EXPORT [[nodiscard]] std::filesystem::path current_process_folder();
}