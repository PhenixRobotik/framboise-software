#pragma once

#include <gtkmm.h>

class BrainWindow
: public Gtk::Window {
public:
  BrainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);
  virtual ~BrainWindow() = default;

private:

  const Glib::RefPtr<Gtk::Builder>& m_builder;

  // true = left, false = right, cuz communism is real
  void on_table_side_button_clicked(bool side);

};

BrainWindow* buildBrainWindow();
