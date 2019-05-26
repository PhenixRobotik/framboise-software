#include "config.h"

#include "gui.hpp"

#include <iostream>
#include <chrono>

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
    )
  );

  m_builder->get_widget("button_table_right", table_button);
  table_button->override_background_color(Gdk::RGBA("#8019FF")); // Violet
  table_button->override_color(Gdk::RGBA("white"));
  table_button->signal_clicked().connect(
    sigc::bind<bool>(
      sigc::mem_fun(this, &BrainWindow::on_table_side_button_clicked),
      false
    )
  );

  m_timer_dispatcher.connect(sigc::mem_fun(this, &BrainWindow::on_timer_update));
  on_timer_update();

  m_can_textview_dispatcher.connect(sigc::mem_fun(this, &BrainWindow::on_can_textview_update));
  on_can_textview_update();
}

void BrainWindow::on_table_side_button_clicked(bool side) {
  std::string color = side ? "yellow" : "purple";
  std::cout << "table " + color + " side button clicked" << std::endl;
  m_side = side;

  // Disable to prevent unwanted clicks
  Gtk::Box* box;
  m_builder->get_widget("buttons_box", box);
  box->set_sensitive(false);
  // box->override_background_color(Gdk::RGBA("#000000"));
}

void BrainWindow::on_timer_update() {
  std::string timer_string =
      std::to_string(int(m_timer_current_seconds))
    + "/"
    + std::to_string(m_timer_max_seconds)
    + "s";

  std::cout << timer_string << std::endl;

  Gtk::ProgressBar* bar;
  m_builder->get_widget("match_progress_bar", bar);
  bar->set_fraction(m_timer_current_seconds / m_timer_max_seconds);
  bar->set_text(timer_string);
}


void BrainWindow::on_can_textview_update() {
  Gtk::TextView* view;
  m_builder->get_widget("can_values_viewer", view);

  view->get_buffer()->set_text(m_can_textview_content);
  view->get_buffer()->get_end_iter()

}
