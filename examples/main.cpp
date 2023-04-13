#include <libev_wrapper/factory.h>
#include <iostream>

int main() {
  {
    std::vector<bro::ev::event_t> events;
    {
      bro::ev::factory factory;
      events.push_back(factory.generate_new_event(bro::ev::event::type::e_write));
      events.push_back(factory.generate_new_event(bro::ev::event::type::e_read));
      factory.proceed();
    }
    for (auto &ev : events) {
      ev->is_active();
      ev->start(2, []() {});
      ev->stop();
    }
  }

  {
    bro::ev::factory factory;
    {
      std::vector<bro::ev::event_t> events;
      events.push_back(factory.generate_new_event(bro::ev::event::type::e_write));
      events.push_back(factory.generate_new_event(bro::ev::event::type::e_read));
      for (auto &ev : events) {
        ev->is_active();
        ev->start(2, []() {});
        ev->stop();
      }
    }
    factory.proceed();
  }

  {
    bro::ev::factory factory;
    auto timer = factory.generate_new_timer();
    bool timer_fired = false;
    auto const start = std::chrono::system_clock::now();
    timer->start(std::chrono::milliseconds(1000), [&]() { timer_fired = true; });
    while (!timer_fired) {
      factory.proceed();
    }
    auto const end = std::chrono::system_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds"
              << std::endl;
  }
  return 0;
}
