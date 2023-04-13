#pragma once

namespace bro::ev {

/** @addtogroup libev_modern_api
 *  @{
 */

class factory;

class base_event {
public:
  explicit base_event(factory *fact)
    : _factory(fact) {}

  virtual ~base_event();

  /**
   * \brief disabled copy ctor
   */
  base_event(base_event const &) = delete;

  /**
   * \brief disabled move ctor
   */
  base_event(base_event &&) = delete;

  /**
   * \brief disabled move assign operator
   */
  base_event &operator=(base_event &&) = delete;

  /**
   * \brief disabled assign operator
   */
  base_event &operator=(base_event const &) = delete;

  virtual void stop() noexcept = 0;

protected:
  friend class factory;

  struct ev_loop *get_loop() const noexcept;

private:
  factory *_factory = nullptr; ///< pointer on factory
};

} // namespace bro::ev
