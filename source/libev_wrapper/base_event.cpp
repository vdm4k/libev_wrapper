#include <libev_wrapper/base_event.h>
#include <libev_wrapper/factory.h>

namespace bro::ev {

base_event::~base_event() {
  if (_factory) {
    _factory->_active_events.erase(this);
  }
}

struct ev_loop *base_event::get_loop() const noexcept {
  if (!_factory)
    return nullptr;
  return _factory->_loop;
}

} // namespace bro::ev
