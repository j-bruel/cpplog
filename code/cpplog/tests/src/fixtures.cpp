#include "fixtures.hpp"
#include "log/current_process_folder.hpp"

namespace cpplog::test
{

  cpplog::cpplog()
  {
    log_file = ::cpplog::log::current_process_folder() / "log" / "cpplog.log";
  }

}