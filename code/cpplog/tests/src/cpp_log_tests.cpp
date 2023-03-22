#include "fixtures.hpp"

#include <chrono>
#include <future>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <log.hpp>
#include <thread>

namespace cpplog::test
{

  TEST_F(cpplog, ConsoleCaptureTest)
  {
    testing::internal::CaptureStdout();

    ::cpplog::debug("#1");
    ::cpplog::info("#2");
    ::cpplog::warning("#3");
    ::cpplog::error("#4");
    ::cpplog::critical("#5");

    const auto console_stdcout_captured = testing::internal::GetCapturedStdout();

    EXPECT_THAT(console_stdcout_captured, testing::HasSubstr("debug"));
    EXPECT_THAT(console_stdcout_captured, testing::HasSubstr("info"));
    EXPECT_THAT(console_stdcout_captured, testing::HasSubstr("warning"));
    EXPECT_THAT(console_stdcout_captured, testing::HasSubstr("error"));
    EXPECT_THAT(console_stdcout_captured, testing::HasSubstr("critical"));// Checking all severity
  }

  TEST_F(cpplog, FileTest)
  {
    using namespace std::chrono_literals;// ns, us, ms, s, h, etc.

    constexpr auto five_seconds = 5s;

    ::cpplog::info("My file has been correctly created?");
    std::this_thread::sleep_for(five_seconds);// Waiting for the logger to flush into the file.
    EXPECT_TRUE(std::filesystem::is_regular_file(log_file));
  }

  TEST_F(cpplog, MultiThreadedTest)
  {
    auto big_log_loop = []()
    {
      constexpr auto random_loop_number = 1000;

      for (int i = 0; i < random_loop_number; ++i)
        ::cpplog::info("It's a big loop into multiple thread test.");
    };

    (void)std::async(std::launch::async, big_log_loop);
    (void)std::async(std::launch::async, big_log_loop);
    (void)std::async(std::launch::async, big_log_loop);
    (void)std::async(std::launch::async, big_log_loop);
  }

}