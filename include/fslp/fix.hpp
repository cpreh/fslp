#ifndef FSLP_FIX_HPP_INCLUDED
#define FSLP_FIX_HPP_INCLUDED

#include <fslp/fix_fwd.hpp>
#include <fslp/detail/make_fix.hpp>
#include <fcppt/recursive.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace fslp
{

template <template <typename...> class... Cs>
struct fix
{
  using rec = typename fslp::detail::make_fix<Cs...>::type;

  fix(rec const &_val) : v{_val} {}
  fix(rec &&_val) : v{std::move(_val)} {}

  rec const &get() const { return v.get(); }
  rec const *operator->() const { return &this->get(); }

  fcppt::recursive<rec> v;
};

}

#endif
