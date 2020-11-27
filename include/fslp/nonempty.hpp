#ifndef FSLP_NONEMPTY_HPP_INCLUDED
#define FSLP_NONEMPTY_HPP_INCLUDED

#include <fcppt/container/make.hpp>
#include <fcppt/optional/make_if.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace fslp
{
template <typename T>
class nonempty
{
public:
  explicit nonempty(T &&_v) : c_{fcppt::container::make<std::vector<T>>(std::move(_v))} {}

  [[nodiscard]] T const &back() const { return this->c_.back(); }
  [[nodiscard]] T &back() { return this->c_.back(); }

  [[nodiscard]] fcppt::optional::object<nonempty> pop_back() &&
  {
    return fcppt::optional::make_if(!this->c_.empty(), [this] {
      this->c_.pop_back();
      return std::move(*this);
    });
  }

private:
  std::vector<T> c_;
};
}

#endif
