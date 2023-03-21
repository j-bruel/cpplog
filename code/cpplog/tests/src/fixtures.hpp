#pragma once

#include "gtest/gtest.h"
#include <filesystem>

namespace centor::log
{

  class centor_log : public ::testing::Test
  {
  protected:
    std::filesystem::path log_file;

    centor_log();
  };

}