#include "config.h"

#include "gui/gui.hpp"

#include <iostream>

int main() {
  std::cout << PROJECT << " " << VERSION << std::endl;

  std::cout << "hello world" << std::endl;


  return gui_blocking_run();

  return 0;
}
