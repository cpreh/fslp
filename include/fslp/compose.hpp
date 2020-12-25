#ifndef FSLP_COMPOSE_HPP_INCLUDED
#define FSLP_COMPOSE_HPP_INCLUDED

#include <fslp/forest_fix.hpp>
#include <fslp/forest_x_fix.hpp>
#include <fslp/forest_x_r.hpp>
#include <fslp/tree_x_fix.hpp>
#include <fslp/var.hpp>
#include <fcppt/container/join.hpp>
#include <fcppt/tuple/get.hpp>
#include <fcppt/tuple/make.hpp>
#include <fcppt/variant/match.hpp>

namespace fslp
{

template <typename Ch>
fslp::forest_x_fix<Ch> compose(fslp::forest_x_fix<Ch> const &, fslp::forest_x_fix<Ch> const &);

template <typename Ch>
fslp::tree_x_fix<Ch> compose(fslp::tree_x_fix<Ch> const &x, fslp::forest_x_fix<Ch> const &f)
{
  return fslp::tree_x_fix<Ch>{fcppt::tuple::make(
      fcppt::tuple::get<0>(x.unfix()), fslp::compose<Ch>(fcppt::tuple::get<1>(x.unfix()), f))};
}

template <typename Ch>
fslp::forest_x_fix<Ch> compose(fslp::forest_x_fix<Ch> const &x, fslp::forest_x_fix<Ch> const &f)
{
  using tree_x = fslp::tree_x_fix<Ch>;
  using forest_r = fslp::forest_x_r<tree_x>;
  using forest = fslp::forest_fix<Ch>;
  using forest_x = fslp::forest_x_fix<Ch>;

  return fcppt::variant::match(
      fcppt::tuple::get<1>(x.unfix()),
      [&x, &f](fslp::var) {
        return forest_x{fcppt::tuple::make(
            forest{fcppt::container::join(
                fcppt::tuple::get<0>(x.unfix()).unfix(), fcppt::tuple::get<0>(f.unfix()).unfix())},
            fcppt::tuple::get<1>(f.unfix()),
            forest{fcppt::container::join(
                fcppt::tuple::get<2>(f.unfix()).unfix(),
                fcppt::tuple::get<2>(x.unfix()).unfix())})};
      },
      [&x, &f](tree_x const &t) {
        return forest_x{fcppt::tuple::make(
            fcppt::tuple::get<0>(x.unfix()),
            forest_r{fslp::compose<Ch>(t, f)},
            fcppt::tuple::get<2>(x.unfix()))};
      });
}
}

#endif
