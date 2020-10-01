#ifndef FSLP_TREE_X_HPP_INCLUDED
#define FSLP_TREE_X_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <tuple>
#include <fcppt/config/external_end.hpp>

namespace fslp
{

template <typename Ch>
struct tree_x
{
  template<typename T, typename F>
  using type = std::tuple<Ch, T>;
};

}

#endif
