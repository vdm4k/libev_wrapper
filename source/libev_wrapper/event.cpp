#include <libev_wrapper/event.h>
#include <libev_wrapper/factory.h>

namespace bro::ev {

event::~event() {
  if (_factory) {
    _factory->_active_events.erase(this);
  }
}

struct ev_loop *event::get_loop() const noexcept {
  if (!_factory)
    return nullptr;
  return _factory->_loop;
}

} // namespace bro::ev
