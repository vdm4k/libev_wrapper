#pragma once
#include <ev.h>
#include <unordered_set>
#include "event.h"
#include "timer.h"

namespace bro::ev {

/** @defgroup libev_modern_api libev_modern_api
 *  @{
 */

/*!\brief produce new events
 */
class factory {
public:
  /**
   * default constructor
   */
  factory() noexcept;

  /**
   * \brief disabled copy ctor
   */
  factory(factory const &) = delete;

  /**
   * \brief disabled move ctor
   */
  factory(factory &&) = delete;

  /**
   * \brief disabled move assign operator
   */
  factory &operator=(factory &&) = delete;

  /**
   * \brief disabled assign operator
   */
  factory &operator=(factory const &) = delete;

  ~factory();

  /*! \brief proceed event loop
   *
   *  This function is a main funcion to generate/handle in/out events.
   *  Hence we need to call it periodically
   */
  void proceed() noexcept;

  /*! \brief generate new events which assigned to this factory
   * \param [in] type of generated events (must be legal event::type)
   * \result new event
   *
   * \note check type is in range from event::type::e_write to event::type::e_read,
   * if it's not return nullptr
   */
  event_t generate_new_event(event::type type);

  timer_t generate_new_timer();

private:
  friend class base_event;
  struct ev_loop *_loop = nullptr;                 ///< pointer on main loop
  std::unordered_set<base_event *> _active_events; ///< active events generated with this factory
};

} // namespace bro::ev
