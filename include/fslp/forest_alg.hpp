#ifndef FSLP_FOREST_ALG_HPP_INCLUDED
#define FSLP_FOREST_ALG_HPP_INCLUDED

#include <fslp/base.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/tuple/object.hpp>
#include <fcppt/variant/object.hpp>

namespace fslp
{

template <typename Ch>
struct forest_alg
{
  template <typename R, typename Rx>
  using type = fcppt::variant::object<
      fslp::base<fcppt::unit>,
      fcppt::tuple::object<R, R>,
      fcppt::tuple::object<Rx, R>,
      fcppt::tuple::object<fslp::base<Ch>, R>>;
};

}

#endif
