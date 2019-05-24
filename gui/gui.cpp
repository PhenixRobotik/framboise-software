#include "config.h"

#include "gui.hpp"

#include <iostream>

BrainWindow* buildBrainWindow() {
  auto glade_file_path = std::string(DATA_DIR) + "/interface.glade";
  auto builder = Gtk::Builder::create_from_file(glade_file_path);

  BrainWindow* window = nullptr;
  builder->get_widget_derived("window_brain", window);
  return window;
}

BrainWindow::BrainWindow(
  BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder
)
: Gtk::Window(cobject)
, m_builder(builder)
{

  this->fullscreen();
  Gtk::Button* table_button;


  m_builder->get_widget("button_table_left", table_button);
  table_button->override_background_color(Gdk::RGBA("#FFBF00")); // Jaune
  table_button->override_color(Gdk::RGBA("black"));
  table_button->signal_clicked()
    .connect(sigc::bind<bool>(
      sigc::mem_fun(this, &BrainWindow::on_table_side_button_clicked),
      true
    ));

  m_builder->get_widget("button_table_right", table_button);
  table_button->override_background_color(Gdk::RGBA("#8019FF")); // Violet
  table_button->override_color(Gdk::RGBA("white"));
  table_button->signal_clicked()
    .connect(sigc::bind<bool>(
      sigc::mem_fun(this, &BrainWindow::on_table_side_button_clicked),
      false
    ));

}

void BrainWindow::on_table_side_button_clicked(bool side) {
  std::string color = side ? "yellow" : "purple";
  std::cout << "table " + color + " side button clicked" << std::endl;
}
