#include "worker.hpp"

#include <chrono>
using namespace std::chrono_literals;

Worker::Worker(BrainWindow* the_window)
: m_brain_window(the_window)
{

}

Worker::~Worker() {
  stop();
}


void Worker::start() {


  // TODO : wait for tirette
  debut_match = std::chrono::steady_clock::now();


  timer_thread = std::thread([&]() {
    while (timer_continue) {
      auto now = std::chrono::steady_clock::now();
      auto x = now + 100ms;

      double secs_from_start =
        std::chrono::duration_cast<std::chrono::milliseconds>(now - debut_match)
          .count() / 1000.0;
      m_brain_window->timer_update_timer(secs_from_start);
      m_brain_window->can_textview_append(std::string("le sang de tes morts\n"));

      std::this_thread::sleep_until(x);
    }
  });
}

void Worker::stop() {
  timer_continue = false;
  if (timer_thread.joinable())
    timer_thread.join();
}
