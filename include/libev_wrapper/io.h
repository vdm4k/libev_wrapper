#pragma once
#include <ev.h>
#include <functional>
#include <memory>
#include "event.h"

namespace bro::ev {

/** @addtogroup libev_modern_api
 *  @{
 */

/*!\brief specific event
 */
class io : public event {
public:
  /*!\brief event type
 */
  enum class type {
    e_none,  ///< not set
    e_write, ///< write
    e_read   ///< read
  };

  ~io();

  /*! \brief stop event. if non active - do nothing
  */
  void stop() noexcept override;

  /*! \brief check if event is active
  * \result true if active, false otherwise
  */
  bool is_active() const noexcept;

  /*! \brief start event
   * \param [in] file_descriptor file descriptor
   * \param [in] callback which we call when event happened
   * \result true if io started, false otherwise
   */
  bool start(int file_descriptor, std::function<void()> &&callback);

  /*! \brief start event
   * \param [in] file_descriptor file descriptor
   * \result true if io started, false otherwise
   *
   * \note assume that we callback already set or will set before call proceed
   */
  bool start(int file_descriptor) noexcept;

  /*! \brief set callback to io
   * \param [in] callback which we call when event happened
   */
  void set_callback(std::function<void()> &&callback);

private:
  /*! \brief ctor
   * \param [in] fact pointer on generate factory
   * \param [in] type type of event
  */
  io(factory *fact, type tp);
  friend class factory;
  friend void cb(struct ev_loop *, ev_io *w, int);

  ev_io _io{0, 0, 0, 0, 0, 0, 0, 0}; ///< current event
  std::function<void()> _callback;   ///< callback to call
  type _type{type::e_none};          ///< type of event
};

using io_t = std::unique_ptr<io>; ///< default pointer to hold event

} // namespace bro::ev
