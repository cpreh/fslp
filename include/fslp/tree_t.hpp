#ifndef FSLP_TREE_T_HPP_INCLUDED
#define FSLP_TREE_T_HPP_INCLUDED

#include <fslp/tree.hpp>

namespace fslp
{

template <typename Ch, typename T, typename F>
using tree_t = fslp::tree<Ch>:: template type<T,F>;

}

#endif
