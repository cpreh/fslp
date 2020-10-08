#ifndef FSLP_COMPOSE_HPP_INCLUDED
#define FSLP_COMPOSE_HPP_INCLUDED

#include <fslp/forest_fix.hpp>
#include <fslp/forest_x_fix.hpp>
#include <fslp/forest_x_r.hpp>
#include <fslp/tree_x_fix.hpp>
#include <fslp/var.hpp>
#include <fcppt/container/join.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <tuple>
#include <fcppt/config/external_end.hpp>

namespace fslp
{

template <typename Ch>
fslp::forest_x_fix<Ch> compose(fslp::forest_x_fix<Ch> const &, fslp::forest_x_fix<Ch> const &);

template <typename Ch>
fslp::tree_x_fix<Ch> compose(fslp::tree_x_fix<Ch> const &x, fslp::forest_x_fix<Ch> const &f)
{
  return fslp::tree_x_fix<Ch>{std::make_tuple(std::get<0>(x.unfix()), fslp::compose<Ch>(std::get<1>(x.unfix()),f))};
}

template <typename Ch>
fslp::forest_x_fix<Ch> compose(fslp::forest_x_fix<Ch> const &x, fslp::forest_x_fix<Ch> const &f)
{
  using tree_x = fslp::tree_x_fix<Ch>;
  using forest_r = fslp::forest_x_r<tree_x>;
  using forest = fslp::forest_fix<Ch>;
  using forest_x = fslp::forest_x_fix<Ch>;

  return fcppt::variant::match(
      std::get<1>(x.unfix()),
      [&x,&f](fslp::var) {
        return forest_x{std::make_tuple(
            forest{fcppt::container::join(std::get<0>(x.unfix()).unfix(), std::get<0>(f.unfix()).unfix())},
            std::get<1>(f.unfix()),
            forest{fcppt::container::join(std::get<2>(f.unfix()).unfix(), std::get<2>(x.unfix()).unfix())})};
      },
      [&x,&f](tree_x const &t) {
        return forest_x{std::make_tuple(
            std::get<0>(x.unfix()), forest_r{fslp::compose<Ch>(t, f)}, std::get<2>(x.unfix()))};
      });
}
}

#endif
