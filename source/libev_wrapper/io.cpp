#include <ev.h>
#include <libev_wrapper/io.h>
#include <libev_wrapper/factory.h>

namespace bro::ev {

void cb(struct ev_loop *, ev_io *w, int) {
  auto *ev = reinterpret_cast<io *>(w->data);
  ev->_callback();
}

io::~io() {
  io::stop();
}

io::io(factory *fact, type tp)
  : event(fact)
  , _type(tp) {}

void io::stop() noexcept {
  if (is_active() && get_loop()) {
    ev_io_stop(get_loop(), &_io);
  }
}

bool io::is_active() const noexcept {
  return ev_is_active(&_io);
}

bool io::start(int file_descriptor) noexcept {
  if (!get_loop())
    return false;
  stop();
  switch (_type) {
  case type::e_read:
    ev_io_init(&_io, cb, file_descriptor, EV_READ);
    break;
  case io::type::e_write:
    ev_io_init(&_io, cb, file_descriptor, EV_WRITE);
    break;
  default:
    return false;
  }
  _io.data = this;
  ev_io_start(get_loop(), &_io);
  return true;
}

void io::set_callback(std::function<void()> &&callback) {
  _callback = std::move(callback);
}

bool io::start(int file_descriptor, std::function<void()> &&callback) {
  if (!start(file_descriptor))
    return false;
  set_callback(std::move(callback));
  return true;
}
} // namespace bro::ev
