#ifndef FSLP_FOREST_FIX_HPP_INCLUDED
#define FSLP_FOREST_FIX_HPP_INCLUDED

#include <fslp/fix.hpp>
#include <fslp/forest.hpp> // IWYU pragma: keep
#include <fslp/tree.hpp> // IWYU pragma: keep

namespace fslp
{
template<typename Ch>
using forest_fix = fslp::fix<fslp::forest<Ch>:: template type, fslp::tree<Ch>:: template type>;
}

#endif
