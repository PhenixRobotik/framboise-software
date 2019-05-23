#include "config.h"

#include "gui.hpp"

#include <gtkmm.h>

int gui_blocking_run() {
  auto app = Gtk::Application::create("fr.phenixrobotik.framboise-brain");

  Gtk::Window* window;

  auto glade_file_path = std::string(DATA_DIR) + "/interface.glade";
  auto builder = Gtk::Builder::create_from_file(glade_file_path);

  builder->get_widget("window_brain", window);
  window->fullscreen();

  Gtk::Button* table_button;


  builder->get_widget("button_table_left", table_button);
  table_button->override_background_color(Gdk::RGBA("#FFBF00"));
  table_button->override_color(Gdk::RGBA("black"));


  builder->get_widget("button_table_right", table_button);
  table_button->override_background_color(Gdk::RGBA("#8019FF"));
  table_button->override_color(Gdk::RGBA("white"));


  return app->run(*window);
}
