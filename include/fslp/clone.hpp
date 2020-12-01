#ifndef FSLP_CLONE_HPP_INCLUDED
#define FSLP_CLONE_HPP_INCLUDED

#include <fslp/map.hpp>
#include <fcppt/unique_ptr.hpp>

namespace fslp
{
namespace detail
{
template <typename T>
[[nodiscard]] inline T clone(T const &v)
{
  return v;
}

template <typename T>
[[nodiscard]] fcppt::unique_ptr<T> clone(fcppt::unique_ptr<T> const &v)
{
  return v->clone();
}
}

template <typename T>
[[nodiscard]] inline T clone(T const &v)
{
  return fslp::map([](auto const &x) { return fslp::detail::clone(x); }, v);
}
}

#endif
