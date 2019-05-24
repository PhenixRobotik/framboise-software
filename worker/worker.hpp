#pragma once

#include "gui/gui.hpp"

#include <thread>
#include <chrono>

class Worker {
public:
  Worker(BrainWindow* the_window);
  virtual ~Worker();

  void start();
  void stop();

private:
  BrainWindow* m_brain_window;

  std::chrono::steady_clock::time_point debut_match;

  bool timer_continue = true;
  std::thread timer_thread;
};
