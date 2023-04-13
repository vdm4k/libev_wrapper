#pragma once
#include <ev.h>
#include <functional>
#include <memory>

namespace bro::ev {

/** @addtogroup libev_modern_api
 *  @{
 */

class factory;

/*!\brief specific event
 */
class event {
public:
  /*!\brief event type
 */
  enum class type {
    e_none,  ///< not set
    e_write, ///< write
    e_read   ///< read
  };

  /**
   * \brief disabled copy ctor
   */
  event(event const &) = delete;

  /**
   * \brief disabled move ctor
   */
  event(event &&) = delete;

  /**
   * \brief disabled move assign operator
   */
  event &operator=(event &&) = delete;

  /**
   * \brief disabled assign operator
   */
  event &operator=(event const &) = delete;
  ~event();

  /*! \brief stop event. if non active - do nothing
  */
  void stop() noexcept;

  /*! \brief check if event is active
  * \result true if active, false otherwise
  */
  bool is_active() const noexcept;

  /*! \brief start event
   * \param [in] file_descriptor file descriptor
   * \param [in] callback which we call when event happened
   * \result true
   */
  bool start(int file_descriptor, std::function<void()> &&callback) noexcept;

private:
  /*! \brief ctor
   * \param [in] fact pointer on generate factory
   * \param [in] type type of event
  */
  event(factory *fact, type tp);
  friend class factory;
  friend void cb(struct ev_loop *, ev_io *w, int);

  ev_io _io{0, 0, 0, 0, 0, 0, 0, 0}; ///< current event
  factory *_factory = nullptr;       ///< pointer on factory
  std::function<void()> _callback;   ///< callback to call
  type _type{type::e_none};          ///< type of event
};

using event_t = std::unique_ptr<event>; ///< default pointer to hold event

} // namespace bro::ev
