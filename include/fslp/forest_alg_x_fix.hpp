#ifndef FSLP_FOREST_ALG_X_FIX_HPP_INCLUDED
#define FSLP_FOREST_ALG_X_FIX_HPP_INCLUDED

#include <fslp/fix.hpp>
#include <fslp/forest_alg.hpp> // IWYU pragma: keep
#include <fslp/forest_alg_x.hpp> // IWYU pragma: keep

namespace fslp
{

template<typename Ch>
using forest_alg_x_fix = fslp::fix<fslp::forest_alg_x<Ch>:: template type, fslp::forest_alg<Ch>:: template type>;

}

#endif
