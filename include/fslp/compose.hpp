#ifndef FSLP_COMPOSE_HPP_INCLUDED
#define FSLP_COMPOSE_HPP_INCLUDED

#include <fslp/forest_fix.hpp>
#include <fslp/forest_x_fix.hpp>
#include <fslp/forest_x_t.hpp>
#include <fslp/tree_x_fix.hpp>
#include <fslp/var.hpp>
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
  return fslp::tree_x_fix<Ch>{std::make_tuple(std::get<0>(x.get()), fslp::compose<Ch>(std::get<1>(x.get()),f))};
}

template <typename Ch>
fslp::forest_x_fix<Ch> compose(fslp::forest_x_fix<Ch> const &x, fslp::forest_x_fix<Ch> const &f)
{
  return fcppt::variant::match(
      x.get(),
      [&f](fslp::var) { return f; },
      [&f](std::tuple<fslp::forest_fix<Ch>, fslp::tree_x_fix<Ch>, fslp::forest_fix<Ch>> const &r) {
        return fslp::forest_x_fix<Ch>{
            fslp::forest_x_t<Ch, fslp::forest_x_fix<Ch>,fslp::tree_x_fix<Ch>>{
	      std::make_tuple(std::get<0>(r), fslp::compose<Ch>(std::get<1>(r), f), std::get<2>(r))}};
      });
}

}

#endif
