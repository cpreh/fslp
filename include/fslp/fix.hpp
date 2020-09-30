#ifndef FSLP_FIX_HPP_INCLUDED
#define FSLP_FIX_HPP_INCLUDED

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

  template <typename U>
  fix(U &&_val) : v{rec{std::forward<U>(_val)}}
  {
  }

  rec const &get() const { return v.get(); }

  fcppt::recursive<rec> v;
};

}

#endif
