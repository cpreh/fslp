#ifndef FSLP_FOREST_X_T_HPP_INCLUDED
#define FSLP_FOREST_X_T_HPP_INCLUDED

#include <fslp/forest_x.hpp>

namespace fslp
{

template <typename Ch, typename F, typename T>
using forest_x_t = typename fslp::forest_x<Ch>:: template type<F,T>;

}

#endif
