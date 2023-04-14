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

io_t factory::generate_io(io::type type) {
  if (io::type::e_read != type && io::type::e_write != type)
    return nullptr;
  auto new_event = std::unique_ptr<io>(new io(this, type));
  _active_events.insert(new_event.get());
  return new_event;
}

timer_t factory::generate_timer() {
  auto new_timer = std::unique_ptr<timer>(new timer(this));
  _active_events.insert(new_timer.get());
  return new_timer;
}

} // namespace bro::ev
