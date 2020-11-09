#ifndef FSLP_FOREST_ALG_EVAL_HPP_INCLUDED
#define FSLP_FOREST_ALG_EVAL_HPP_INCLUDED

#include <fslp/apply.hpp>
#include <fslp/compose.hpp>
#include <fslp/forest_alg_t.hpp>
#include <fslp/forest_alg_x_t.hpp>
#include <fslp/forest_fix.hpp>
#include <fslp/forest_x_fix.hpp>
#include <fslp/forest_x_r.hpp>
#include <fslp/tree.hpp>
#include <fslp/tree_fix.hpp>
#include <fslp/tree_x_fix.hpp>
#include <fslp/var.hpp>
#include <fcppt/container/join.hpp>
#include <fcppt/variant/match.hpp>

namespace fslp
{
template <typename Ch>
fslp::forest_fix<Ch>
forest_alg_eval(fslp::forest_alg_t<Ch, fslp::forest_fix<Ch>, fslp::forest_x_fix<Ch>> const &v)
{
  using forest = fslp::forest_fix<Ch>;
  using forest_x = fslp::forest_x_fix<Ch>;
  using tree = fslp::tree_fix<Ch>;

  return fcppt::variant::match(
      v,
      [](fcppt::unit) { return forest{std::vector<tree>{}}; },
      [](std::tuple<forest, forest> const &r) {
        return forest{fcppt::container::join(std::get<0>(r).unfix(), std::get<1>(r).unfix())};
      },
      [](std::tuple<forest_x, forest> const &r) {
        return fslp::apply<Ch>(std::get<0>(r), std::get<1>(r));
      },
      [](std::tuple<Ch, forest> const &r) {
        return forest{std::vector<tree>{tree{std::make_tuple(std::get<0>(r), std::get<1>(r))}}};
      });
}

template <typename Ch>
fslp::forest_x_fix<Ch>
forest_alg_eval(fslp::forest_alg_x_t<Ch, fslp::forest_x_fix<Ch>, fslp::forest_fix<Ch>> const &v)
{
  using forest = fslp::forest_fix<Ch>;
  using forest_x = fslp::forest_x_fix<Ch>;
  using tree = fslp::tree_fix<Ch>;
  using tree_x = fslp::tree_x_fix<Ch>;
  using forest_x_r = fslp::forest_x_r<tree_x>;

  return fcppt::variant::match(
      v,
      [](std::tuple<Ch, forest, forest> const &r) {
        forest_x const i{std::make_tuple(std::get<1>(r), forest_x_r{fslp::var{}}, std::get<2>(r))};
        forest const e{std::vector<tree>{}};
        return forest_x{
            std::make_tuple(e, forest_x_r{tree_x{std::make_tuple(std::get<0>(r), i)}}, e)};
      },
      [](std::tuple<forest_x, forest_x> const &r) {
        return fslp::compose<Ch>(std::get<0>(r), std::get<1>(r));
      });
}
}

#endif
