#ifndef FSLP_UNFOLD_HPP_INCLUDED
#define FSLP_UNFOLD_HPP_INCLUDED

#include <fslp/fix.hpp>
#include <fslp/map.hpp>

namespace fslp
{

template<typename T, typename F>
T unfold(T const &t, F const &)
{
  return t;
}

template <typename R, template <typename...> class... Cs, typename F>
R unfold(fslp::fix<Cs...> const &x, F const &f)
{
  return f(fslp::map([&f](auto const &i) { return fslp::unfold<R>(i, f); }, x.unfix()));
}

}

#endif
