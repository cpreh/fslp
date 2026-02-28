#ifndef FSLP_FOREST_ALG_X_T_HPP_INCLUDED
#define FSLP_FOREST_ALG_X_T_HPP_INCLUDED

#include <fslp/forest_alg_x.hpp>

namespace fslp
{

template <typename Ch, typename R, typename Rx>
using forest_alg_x_t = fslp::forest_alg_x<Ch>:: template type<R,Rx>;

}

#endif
