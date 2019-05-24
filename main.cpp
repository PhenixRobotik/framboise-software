#include "config.h"

#include "gui/gui.hpp"

#include <iostream>
#include <gtkmm.h>

int main() {
  std::cout << PROJECT << " " << VERSION << std::endl;
  auto app = Gtk::Application::create("fr.phenixrobotik.framboise-brain");


  auto window = buildBrainWindow();
  return app->run(*window);
}
