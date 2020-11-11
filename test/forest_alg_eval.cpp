#include <fslp/forest_alg_eval.hpp>
#include <fslp/forest_alg_t.hpp>
#include <fslp/forest_alg_x_t.hpp>
#include <fslp/forest_fix.hpp>
#include <fslp/forest_x_fix.hpp>
#include <fslp/forest_x_r.hpp>
#include <fslp/tree.hpp>
#include <fslp/tree_fix.hpp>
#include <fslp/tree_x_fix.hpp>
#include <fslp/var.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
#include <tuple>
#include <vector>
#include <fcppt/config/external_end.hpp>


TEST_CASE("fslp::forest_alg_eval","[fslp]")
{
  using forest = fslp::forest_fix<char>;
  using tree = fslp::tree_fix<char>;
  using forest_x = fslp::forest_x_fix<char>;
  using tree_x = fslp::tree_x_fix<char>;
  using forest_x_r = fslp::forest_x_r<tree_x>;
  using forest_alg_t = fslp::forest_alg_t<char,forest,forest_x>;
  using forest_alg_x_t = fslp::forest_alg_x_t<char,forest_x,forest>;

  forest const e{std::vector<tree>{}};

  CHECK(fslp::forest_alg_eval<char>(forest_alg_t{fslp::base{fcppt::unit{}}}) == e);

  forest_x const i{std::make_tuple(e, forest_x_r{fslp::var{}}, e)};

  CHECK(
      fslp::forest_alg_eval<char>(forest_alg_x_t{std::make_tuple(fslp::base{'a'}, e, e)}) ==
      forest_x{std::make_tuple(e, forest_x_r{tree_x{std::make_tuple(fslp::base{'a'}, i)}}, e)});
}
