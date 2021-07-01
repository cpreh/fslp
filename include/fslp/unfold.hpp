#ifndef FSLP_UNFOLD_HPP_INCLUDED
#define FSLP_UNFOLD_HPP_INCLUDED

#include <fslp/fix.hpp>
#include <fslp/map.hpp>
#include <fcppt/mpl/map/at.hpp>

namespace fslp
{
template <typename Types, template <typename...> class... Cs, typename F>
fcppt::mpl::map::at<Types, fslp::fix<Cs...>> unfold(fslp::fix<Cs...> const &x, F const &f)
{
  return f(fslp::map([&f](auto const &i) { return fslp::unfold<Types>(i, f); }, x.unfix()));
}
}

#endif
