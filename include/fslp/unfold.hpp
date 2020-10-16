#ifndef FSLP_UNFOLD_HPP_INCLUDED
#define FSLP_UNFOLD_HPP_INCLUDED

#include <fslp/fix.hpp>
#include <fslp/map.hpp>

namespace fslp
{
template <template <typename...> class... Cs, typename F>
auto unfold(fslp::fix<Cs...> const &x, F const &f)
{
  return f(fslp::map([&f](auto const &i) { return unfold(i, f); }, x.unfix()));
}
}

#endif
