#ifndef FSLP_FOREST_X_HPP_INCLUDED
#define FSLP_FOREST_X_HPP_INCLUDED

#include <fslp/forest_fix.hpp>
#include <fslp/forest_x_r.hpp>
#include <fcppt/tuple/object.hpp>

namespace fslp
{
template <typename Ch>
struct forest_x
{
  template <typename F, typename T>
  using type =
      fcppt::tuple::object<fslp::forest_fix<Ch>, fslp::forest_x_r<T>, fslp::forest_fix<Ch>>;
};
}

#endif
