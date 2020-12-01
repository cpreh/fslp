#ifndef FSLP_NONEMPTY_HPP_INCLUDED
#define FSLP_NONEMPTY_HPP_INCLUDED

#include <fslp/nonempty_fwd.hpp>
#include <fcppt/container/pop_back.hpp>
#include <fcppt/optional/map.hpp>
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
  nonempty(std::vector<T> &&_front, T &&_back) : front_{std::move(_front)}, back_{std::move(_back)}
  {
  }

  explicit nonempty(T &&v) : nonempty{std::vector<T>{},std::move(v)} {}

  [[nodiscard]] T const &back() const { return this->back_; }
  [[nodiscard]] T &back() { return this->back_; }

  [[nodiscard]] std::vector<T> const &front() const { return this->front_; }
  [[nodiscard]] std::vector<T> &front() { return this->front_; }

  [[nodiscard]] fcppt::optional::object<nonempty> pop_back() &&
  {
    return fcppt::optional::map(
      fcppt::container::pop_back(this->front_),
      [this](T &&_back)
      {
        return nonempty{std::move(this->front_),std::move(_back)};
      });
  }
private:
  std::vector<T> front_;
  T back_;
};

template <typename T>
[[nodiscard]] inline bool operator==(fslp::nonempty<T> const &a, fslp::nonempty<T> const &b)
{
  return a.back() == b.back() && a.front() == b.front();
}
}

#endif
