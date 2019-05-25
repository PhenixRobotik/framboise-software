#pragma once

#include <gtkmm.h>

class BrainWindow
: public Gtk::Window {
public:
  BrainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
  virtual ~BrainWindow() = default;


  bool get_side();
  void timer_set_max(int seconds) {
    m_timer_max_seconds = seconds;
    timer_update();
  }
  void timer_update_timer(double seconds) {
    m_timer_current_seconds = seconds;
    timer_update();
  }

  void can_textview_set_content(std::string const& content) {
    m_can_textview_content = content;
    can_textview_update();
  }
  void can_textview_append(std::string const& content) {
    m_can_textview_content += content;
    can_textview_update();
  }

private:
  const Glib::RefPtr<Gtk::Builder> m_builder;

  // true = left, false = right, cuz communism is real
  void on_table_side_button_clicked(bool side);
  bool m_side = true; // sorry, default value

  // Match timer
  Glib::Dispatcher m_timer_dispatcher;
  void timer_update() { m_timer_dispatcher.emit(); }
  void on_timer_update();

  double m_timer_current_seconds = 0;
  int m_timer_max_seconds = 100;

  // Text view content
  Glib::Dispatcher m_can_textview_dispatcher;
  void can_textview_update() { m_can_textview_dispatcher.emit(); };
  void on_can_textview_update();

  std::string m_can_textview_content;
};

BrainWindow* buildBrainWindow();
