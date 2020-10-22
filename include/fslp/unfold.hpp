#ifndef FSLP_UNFOLD_HPP_INCLUDED
#define FSLP_UNFOLD_HPP_INCLUDED

#include <fslp/fix.hpp>
#include <fslp/map.hpp>
#include <fslp/unfold_result.hpp>

namespace fslp
{

template<typename T, typename F>
T unfold(T const &t, F const &)
{
  return t;
}

template <template <typename...> class... Cs, typename F>
fslp::unfold_result<fslp::fix<Cs...>,F> unfold(fslp::fix<Cs...> const &x, F const &f)
{
  return f(fslp::map([&f](auto const &i) { return fslp::unfold(i, f); }, x.unfix()));
}

}

#endif
