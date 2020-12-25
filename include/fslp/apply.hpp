#ifndef FSLP_APPLY_HPP_INCLUDED
#define FSLP_APPLY_HPP_INCLUDED

#include <fslp/forest_fix.hpp>
#include <fslp/forest_x_fix.hpp>
#include <fslp/tree_fix.hpp>
#include <fslp/tree_x_fix.hpp>
#include <fslp/var.hpp>
#include <fcppt/container/join.hpp>
#include <fcppt/tuple/get.hpp>
#include <fcppt/tuple/make.hpp>
#include <fcppt/variant/match.hpp>

namespace fslp
{

template <typename Ch>
fslp::forest_fix<Ch> apply(fslp::forest_x_fix<Ch> const &, fslp::forest_fix<Ch> const &);

template <typename Ch>
fslp::tree_fix<Ch> apply(fslp::tree_x_fix<Ch> const &x, fslp::forest_fix<Ch> const &f)
{
  return fslp::tree_fix<Ch>{fcppt::tuple::make(
      fcppt::tuple::get<0>(x.get()), fslp::apply<Ch>(fcppt::tuple::get<1>(x.get()), f))};
}

template <typename Ch>
fslp::forest_fix<Ch> apply(fslp::forest_x_fix<Ch> const &x, fslp::forest_fix<Ch> const &f)
{
  return fslp::forest_fix<Ch>{fcppt::container::join(
      fcppt::tuple::get<0>(x.unfix()).unfix(),
      fcppt::variant::match(
          fcppt::tuple::get<1>(x.unfix()),
          [&f](fslp::var) -> std::vector<fslp::tree_fix<Ch>> const & { return f.unfix(); },
          [&f](fslp::tree_x_fix<Ch> const &r) -> std::vector<fslp::tree_fix<Ch>> const & {
            return fslp::apply<Ch>(fcppt::tuple::get<1>(r.unfix()), f).unfix();
          }),
      fcppt::tuple::get<2>(x.unfix()).unfix())};
}
}

#endif
