#ifndef FSLP_TREE_X_HPP_INCLUDED
#define FSLP_TREE_X_HPP_INCLUDED

#include <fslp/forest_x_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <tuple>
#include <fcppt/config/external_end.hpp>

namespace fslp
{

template <typename Ch>
struct tree_x
{
  using type = std::tuple<Ch, fslp::forest_x<Ch>>;
};

}

#endif
