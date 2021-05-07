#ifndef FSLP_MAKE_NONEMPTY_HPP_INCLUDED
#define FSLP_MAKE_NONEMPTY_HPP_INCLUDED

#include <fslp/nonempty.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace fslp
{
template <typename T>
[[nodiscard]] fslp::nonempty<std::remove_cvref_t<T>> make_nonempty(T &&_value)
{
  return fslp::nonempty<std::remove_cvref_t<T>>{std::forward<T>(_value)};
}
}

#endif
