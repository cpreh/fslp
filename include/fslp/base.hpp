#ifndef FSLP_BASE_HPP_INCLUDED
#define FSLP_BASE_HPP_INCLUDED

#include <fslp/base_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace fslp
{
template<typename T>
struct base
{
  explicit base(T &&x) : v{std::move(x)} {}

  T v;

  [[nodiscard]] T const &get() const { return v; }
};

template<typename T>
base(T) -> base<T>;

template<typename T>
bool operator==(fslp::base<T> const &a, fslp::base<T> const &b)
{
  return a.get() == b.get();
}

}

#endif
