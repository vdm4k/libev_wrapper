#include <ev.h>
#include <libev_wrapper/timer.h>
#include <libev_wrapper/factory.h>

namespace bro::ev {

void cb(struct ev_loop * /*loop*/, ev_timer *w, int /*revents*/) {
  auto *tmr = reinterpret_cast<timer *>(w->data);
  tmr->_callback();
}

timer::timer(factory *fact)
  : event(fact) {}

void timer::stop() noexcept {
  if (is_active() && get_loop()) {
    ev_timer_stop(get_loop(), &_io);
  }
}

bool timer::is_active() const noexcept {
  return ev_is_active(&_io);
}

bool timer::start(std::chrono::milliseconds const &timeout, std::function<void()> &&callback) noexcept {
  if (!get_loop())
    return false;
  stop();
  ev_init(&_io, cb);
  //  _io.repeat = time.count();
  double sec = std::chrono::duration_cast<std::chrono::seconds>(timeout).count();
  double millisec = (timeout.count() % 1000) * 0.001;
  _io.repeat = sec + millisec;
  _io.data = this;
  ev_timer_again(get_loop(), &_io);
  _callback = std::move(callback);
  return true;
}
} // namespace bro::ev
