#ifndef FSLP_APPLY_HPP_INCLUDED
#define FSLP_APPLY_HPP_INCLUDED

#include <fslp/forest_fix.hpp>
#include <fslp/forest_x_fix.hpp>
#include <fslp/tree_fix.hpp>
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
fslp::forest_fix<Ch> apply(fslp::forest_x_fix<Ch> const &, fslp::forest_fix<Ch> const &);

template <typename Ch>
fslp::tree_fix<Ch> apply(fslp::tree_x_fix<Ch> const &x, fslp::forest_fix<Ch> const &f)
{
  return fslp::tree_fix<Ch>{std::make_tuple(std::get<0>(x.get()), fslp::apply<Ch>(std::get<1>(x.get()),f))};
}

template <typename Ch>
fslp::forest_fix<Ch> apply(fslp::forest_x_fix<Ch> const &x, fslp::forest_fix<Ch> const &f)
{
  return fslp::forest_fix<Ch>{fcppt::container::join(
      std::get<0>(x.unfix()).unfix(),
      fcppt::variant::match(
          std::get<1>(x.unfix()),
          [&f](fslp::var) -> std::vector<fslp::tree_fix<Ch>> const & { return f.unfix(); },
          [&f](fslp::tree_x_fix<Ch> const &r) -> std::vector<fslp::tree_fix<Ch>> const & {
            return fslp::apply<Ch>(std::get<1>(r.unfix()), f).unfix();
          }),
      std::get<2>(x.unfix()).unfix())};
}
}

#endif
