#pragma once
#include <ev.h>
#include <functional>
#include <memory>
#include <chrono>
#include "event.h"

namespace bro::ev {

/** @addtogroup libev_modern_api
 *  @{
 */

class factory;

/*!\brief timer event
 */
class timer : public event {
public:
  /*! \brief stop timer. if non active - do nothing
  */
  void stop() noexcept override;

  /*! \brief check if event is active
  * \result true if active, false otherwise
  */
  bool is_active() const noexcept;

  /*! \brief start timer
   * \param [in] timeout
   * \param [in] callback call when the timer expiered
   * \result true
   *
   * \note precision millisecond only
   */
  bool start(std::chrono::milliseconds const &timeout, std::function<void()> &&callback) noexcept;

private:
  /*! \brief ctor
   * \param [in] fact pointer on generate factory
  */
  timer(factory *fact);
  friend class factory;
  friend void cb(struct ev_loop * /*loop*/, ev_timer *w, int /*revents*/);

  ev_timer _io{0, 0, 0, 0, 0, 0, 0}; ///< current timer
  std::function<void()> _callback;   ///< callback to call
};

using timer_t = std::unique_ptr<timer>; ///< default pointer to hold event

} // namespace bro::ev
