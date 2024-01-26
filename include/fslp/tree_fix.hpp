#ifndef FSLP_TREE_FIX_HPP_INCLUDED
#define FSLP_TREE_FIX_HPP_INCLUDED

#include <fslp/fix.hpp>
#include <fslp/forest.hpp> // IWYU pragma: keep
#include <fslp/tree.hpp> // IWYU pragma: keep

namespace fslp
{
template<typename Ch>
using tree_fix = fslp::fix<fslp::tree<Ch>:: template type, fslp::forest<Ch>:: template type>;
}

#endif
