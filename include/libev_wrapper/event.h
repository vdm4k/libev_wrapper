#pragma once

namespace bro::ev {

/** @addtogroup libev_modern_api
 *  @{
 */

class factory;

/**
  * \brief base class for all events
  */
class event {
public:
  /**
   * \brief ctor
   * \param fact pointer on factory
   */
  explicit event(factory *fact)
    : _factory(fact) {}

  virtual ~event();

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

  /**
   * \brief stop current event
   */
  virtual void stop() noexcept = 0;

protected:
  friend class factory;

  /**
   * \brief stop current event
   * \return pointer on main loop
   */
  struct ev_loop *get_loop() const noexcept;

private:
  factory *_factory = nullptr; ///< pointer on factory
};

} // namespace bro::ev
