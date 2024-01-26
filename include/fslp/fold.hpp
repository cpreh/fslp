#ifndef FSLP_FOLD_HPP_INCLUDED
#define FSLP_FOLD_HPP_INCLUDED

#include <fslp/map.hpp>
#include <fcppt/mpl/map/at.hpp>

namespace fslp
{
template <typename Types, typename T, typename F>
fcppt::mpl::map::at<Types, T> fold(T const &x, F const &f)
{
  return fcppt::mpl::map::at<Types, T>{fslp::map([&f](auto const &i) { return fslp::fold<Types>(i, f); }, f(x))};
}
}

#endif
