#ifndef FSLP_FOREST_ALG_T_HPP_INCLUDED
#define FSLP_FOREST_ALG_T_HPP_INCLUDED

#include <fslp/forest_alg.hpp>

namespace fslp
{

template <typename Ch, typename R, typename Rx>
using forest_alg_t = fslp::forest_alg<Ch>:: template type<R,Rx>;

}

#endif
