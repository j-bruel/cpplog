#include "fixtures.hpp"
#include "centor/log/current_process_folder.hpp"

namespace centor::log
{

  centor_log::centor_log()
  {
    log_file = current_process_folder() / "log" / "centor.log";
  }

}