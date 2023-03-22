#include "log/current_process_folder.hpp"
#if defined(WIN32)
  #include "Windows.h"
#endif

namespace cpplog::log
{

  std::filesystem::path current_process_folder()
  {
    // if multiple call think about caching and std::call_once
    std::filesystem::path folder;

#if defined(WIN32)
    std::vector<wchar_t> buff(2048);
    int nWrite = GetModuleFileNameW(NULL, buff.data(), static_cast<int>(buff.size()));
    folder = std::filesystem::path{buff.cbegin(), buff.cbegin() + nWrite}.remove_filename();
#else// LINUX
    folder = std::filesystem::canonical("/proc/self/exe").remove_filename();
#endif
    return folder;
  }


}