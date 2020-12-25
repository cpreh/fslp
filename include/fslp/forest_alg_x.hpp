#ifndef FSLP_FOREST_ALG_X_HPP_INCLUDED
#define FSLP_FOREST_ALG_X_HPP_INCLUDED

#include <fslp/base.hpp>
#include <fcppt/tuple/object.hpp>
#include <fcppt/variant/object.hpp>

namespace fslp
{
template <typename Ch>
struct forest_alg_x
{
  template <typename Rx, typename R>
  using type = fcppt::variant::
      object<fcppt::tuple::object<fslp::base<Ch>, R, R>, fcppt::tuple::object<Rx, Rx>>;
};
}

#endif
