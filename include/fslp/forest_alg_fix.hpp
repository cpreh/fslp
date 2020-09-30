#ifndef FSLP_FOREST_ALG_FIX_HPP_INCLUDED
#define FSLP_FOREST_ALG_FIX_HPP_INCLUDED

#include <fslp/fix.hpp>
#include <fslp/forest_alg.hpp>
#include <fslp/forest_alg_x.hpp>

namespace fslp
{
template<typename Ch>
using forest_alg_fix = fslp::fix<fslp::forest_alg<Ch>:: template type, fslp::forest_alg_x<Ch>:: template type>;
}

#endif
