#ifndef FSLP_TREE_X_HPP_INCLUDED
#define FSLP_TREE_X_HPP_INCLUDED

#include <fslp/base.hpp>
#include <fcppt/tuple/object.hpp>

namespace fslp
{

template <typename Ch>
struct tree_x
{
  template<typename T, typename F>
  using type = fcppt::tuple::object<fslp::base<Ch>, F>;
};

}

#endif
