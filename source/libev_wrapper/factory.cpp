#include <ev.h>
#include <libev_wrapper/factory.h>

namespace bro::ev {

factory::factory() noexcept
  : _loop(ev_loop_new(EVFLAG_AUTO)) {}

factory::~factory() {
  for (auto ev : _active_events) {
    ev->stop();
    ev->_factory = nullptr;
  }
  ev_loop_destroy(_loop);
}

void factory::proceed() noexcept {
  ev_loop(_loop, EVRUN_ONCE | EVRUN_NOWAIT);
}

std::unique_ptr<event> factory::generate_new_event(event::type type) noexcept {
  if (event::type::e_read != type && event::type::e_write != type)
    return nullptr;
  auto new_event = std::unique_ptr<event>(new event(this, type));
  _active_events.insert(new_event.get());
  return new_event;
}

} // namespace bro::ev
