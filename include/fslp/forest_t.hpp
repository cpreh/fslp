#ifndef FSLP_FOREST_T_HPP_INCLUDED
#define FSLP_FOREST_T_HPP_INCLUDED

#include <fslp/forest.hpp>

namespace fslp
{

template <typename Ch, typename F, typename T>
using forest_t = typename fslp::forest<Ch>:: template type<F,T>;

}

#endif
