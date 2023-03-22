#pragma once

#include "gtest/gtest.h"
#include <filesystem>

namespace cpplog::test
{

  class cpplog : public ::testing::Test
  {
  protected:
    std::filesystem::path log_file;

    cpplog();
  };

}