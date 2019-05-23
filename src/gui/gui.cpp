#include "gui.hpp"

#include <gtkmm.h>

int gui_blocking_run() {
  auto app = Gtk::Application::create("fr.phenixrobotik.framboise-brain");

  Gtk::Window window;
  window.set_default_size(200, 200);
  window.fullscreen();
  window.show_all();


  return app->run(window);
}
