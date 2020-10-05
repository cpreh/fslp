#ifndef FSLP_TREE_X_T_HPP_INCLUDED
#define FSLP_TREE_X_T_HPP_INCLUDED

#include <fslp/tree_x.hpp>

namespace fslp
{

template <typename Ch, typename T, typename F>
using tree_x_t = typename fslp::tree_x<Ch>:: template type<T,F>;

}

#endif
