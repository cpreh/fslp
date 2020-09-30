#ifndef FSLP_TREE_HPP_INCLUDED
#define FSLP_TREE_HPP_INCLUDED

#include <fslp/forest_fwd.hpp>
#include <fslp/tree_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <tuple>
#include <fcppt/config/external_end.hpp>

namespace fslp
{

template <typename Ch>
struct tree
{
  using type = std::tuple<Ch, fslp::forest<Ch>>;
};

}

#endif
