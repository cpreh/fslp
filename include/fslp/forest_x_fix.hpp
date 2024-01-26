#ifndef FSLP_FOREST_X_FIX_HPP_INCLUDED
#define FSLP_FOREST_X_FIX_HPP_INCLUDED

#include <fslp/fix.hpp>
#include <fslp/forest_x.hpp> // IWYU pragma: keep
#include <fslp/tree_x.hpp> // IWYU pragma: keep

namespace fslp
{
template<typename Ch>
using forest_x_fix = fslp::fix<fslp::forest_x<Ch>:: template type, fslp::tree_x<Ch>:: template type>;
}

#endif
