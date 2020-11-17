#ifndef FSLP_FOLD_HPP_INCLUDED
#define FSLP_FOLD_HPP_INCLUDED

#include <fslp/fix.hpp>
#include <fslp/map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
#include <fcppt/config/external_end.hpp>

namespace fslp
{
template <typename Types, typename T, typename F>
metal::at_key<Types, T> fold(T const &x, F const &f)
{
  return metal::at_key<Types, T>{fslp::map([&f](auto const &i) { return fslp::fold<Types>(i, f); }, f(x))};
}
}

#endif
