#ifndef FSLP_FIX_HPP_INCLUDED
#define FSLP_FIX_HPP_INCLUDED

#include <fslp/fix_fwd.hpp>
#include <fslp/detail/make_fix.hpp>
#include <fcppt/recursive.hpp>
#include <fcppt/type_traits/remove_cv_ref_t.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace fslp
{

template <template <typename...> class... Cs>
struct fix
{
  using rec = typename fslp::detail::make_fix<Cs...>::type;

  template<typename U, typename = std::enable_if_t<std::is_same_v<fcppt::type_traits::remove_cv_ref_t<U>,rec>>>
  fix(U &&_val) : v{std::forward<U>(_val)} {}

  rec const &get() const { return v.get(); }
  rec const *operator->() const { return &this->get(); }

  fcppt::recursive<rec> v;
};

}

#endif
