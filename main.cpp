#include "config.h"

#include "gui/gui.hpp"
#include "worker/worker.hpp"

#include <iostream>
#include <gtkmm.h>
#include <thread>

int main() {
  std::cout << PROJECT << " " << VERSION << std::endl;
  auto app = Gtk::Application::create("fr.phenixrobotik.framboise-brain");


  auto window = buildBrainWindow();

  Worker worker(window);
  std::thread worker_thread([&]() {
    worker.start();
  });

  auto return_value = app->run(*window);
  worker.stop();
  worker_thread.join();
  return return_value;
}
