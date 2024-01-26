#ifndef FSLP_TREE_X_FIX_HPP_INCLUDED
#define FSLP_TREE_X_FIX_HPP_INCLUDED

#include <fslp/fix.hpp>
#include <fslp/forest_x.hpp> // IWYU pragma: keep
#include <fslp/tree_x.hpp> // IWYU pragma: keep

namespace fslp
{
template<typename Ch>
using tree_x_fix = fslp::fix<fslp::tree_x<Ch>:: template type, fslp::forest_x<Ch>:: template type>;
}

#endif
