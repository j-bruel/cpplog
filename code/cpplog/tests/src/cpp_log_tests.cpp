#include "fixtures.hpp"

#include <centor/log.hpp>
#include <chrono>
#include <future>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <thread>

namespace centor::log
{

  TEST_F(centor_log, ConsoleCaptureTest)
  {
    testing::internal::CaptureStdout();

    centor::log::debug("#1");
    centor::log::info("#2");
    centor::log::warning("#3");
    centor::log::error("#4");
    centor::log::critical("#5");

    const auto console_stdcout_captured = testing::internal::GetCapturedStdout();

    EXPECT_THAT(console_stdcout_captured, testing::HasSubstr("debug"));
    EXPECT_THAT(console_stdcout_captured, testing::HasSubstr("info"));
    EXPECT_THAT(console_stdcout_captured, testing::HasSubstr("warning"));
    EXPECT_THAT(console_stdcout_captured, testing::HasSubstr("error"));
    EXPECT_THAT(console_stdcout_captured, testing::HasSubstr("critical"));// Checking all severity
  }

  TEST_F(centor_log, FileTest)
  {
    using namespace std::chrono_literals;// ns, us, ms, s, h, etc.

    constexpr auto five_seconds = 5s;

    centor::log::info("My file has been correctly created?");
    std::this_thread::sleep_for(five_seconds);// Waiting for the logger to flush into the file.
    EXPECT_TRUE(std::filesystem::is_regular_file(log_file));
  }

  TEST_F(centor_log, MultiThreadedTest)
  {
    auto big_log_loop = []()
    {
      constexpr auto random_loop_number = 1000;

      for (int i = 0; i < random_loop_number; ++i)
        centor::log::info("It's a big loop into multiple thread test.");
    };

    (void)std::async(std::launch::async, big_log_loop);
    (void)std::async(std::launch::async, big_log_loop);
    (void)std::async(std::launch::async, big_log_loop);
    (void)std::async(std::launch::async, big_log_loop);
  }

}