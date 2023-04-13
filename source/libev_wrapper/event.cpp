#include <ev.h>
#include <libev_wrapper/event.h>
#include <libev_wrapper/factory.h>

namespace bro::ev {

void cb(struct ev_loop *, ev_io *w, int) {
  auto *ev = reinterpret_cast<event *>(w->data);
  ev->_callback();
}

event::event(factory *fact, type tp)
  : _factory(fact)
  , _type(tp) {}

event::~event() {
  if (_factory) {
    _factory->_active_events.erase(this);
  }
}

void event::stop() noexcept {
  if (is_active() && _factory) {
    ev_io_stop(_factory->_loop, &_io);
  }
}

bool event::is_active() const noexcept {
  return ev_is_active(&_io);
}

bool event::start(int file_descriptor, std::function<void()> &&callback) noexcept {
  if (!_factory)
    return false;
  switch (_type) {
  case type::e_read:
    ev_io_init(&_io, cb, file_descriptor, EV_READ);
    break;
  case event::type::e_write:
    ev_io_init(&_io, cb, file_descriptor, EV_WRITE);
    break;
  default:
    return false;
  }
  _io.data = this;
  _callback = std::move(callback);
  return true;
}
} // namespace bro::ev
