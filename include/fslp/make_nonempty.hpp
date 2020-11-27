#ifndef FSLP_MAKE_NONEMPTY_HPP_INCLUDED
#define FSLP_MAKE_NONEMPTY_HPP_INCLUDED

#include <fslp/nonempty.hpp>
#include <fcppt/type_traits/remove_cv_ref_t.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace fslp
{
template <typename T>
[[nodiscard]] fslp::nonempty<fcppt::type_traits::remove_cv_ref_t<T>> make_nonempty(T &&_value)
{
  return fslp::nonempty<fcppt::type_traits::remove_cv_ref_t<T>>{std::forward<T>(_value)};
}
}

#endif
