#include "fixtures.hpp"

namespace centor::log
{

  centor_log::centor_log()
  {
    log_file = std::filesystem::current_path() / "/log/centor_cpplog.log";
  }

}