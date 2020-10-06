#include <fslp/apply.hpp>
#include <fslp/forest_alg_t.hpp>
#include <fslp/forest_fix.hpp>
#include <fslp/forest_x_fix.hpp>
#include <fslp/tree_fix.hpp>
#include <fcppt/container/join.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
#include <tuple>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace
{
template <typename Ch>
fslp::forest_fix<Ch>
eval(fslp::forest_alg_t<Ch, fslp::forest_fix<Ch>, fslp::forest_x_fix<Ch>> const &v)
{
  using forest = fslp::forest_fix<Ch>;
  using forest_x = fslp::forest_x_fix<Ch>;
  using tree = fslp::tree_fix<Ch>;

  return fcppt::variant::match(
      v,
      [](fcppt::unit) { return forest{std::vector<tree>{}}; },
      [](std::tuple<forest, forest> const &r) {
        return forest{fcppt::container::join(std::get<0>(r).get(), std::get<1>(r).get())};
      },
      [](std::tuple<forest_x, forest> const &r) {
        return fslp::apply<Ch>(std::get<0>(r), std::get<1>(r));
      },
      [](std::tuple<Ch, forest> const &r) {
        return forest{std::vector<tree>{tree{std::make_tuple(std::get<0>(r), std::get<1>(r))}}};
      });
}
}

TEST_CASE("fslp::forest_alg_eval","[fslp]")
{
  using forest = fslp::forest_fix<char>;
  using tree = fslp::tree_fix<char>;
  using forest_x = fslp::forest_x_fix<char>;
  using forest_alg_t = fslp::forest_alg_t<char,forest,forest_x>;

  CHECK(eval<char>(forest_alg_t{fcppt::unit{}}) == forest{std::vector<tree>{}});
}