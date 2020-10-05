#include <fslp/forest_fix.hpp>
#include <fslp/forest_x_fix.hpp>
#include <fslp/forest_x_t.hpp>
#include <fslp/tree_fix.hpp>
#include <fslp/tree_x_fix.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
#include <tuple>
#include <vector>
#include <fcppt/config/external_end.hpp>


TEST_CASE("fslp::forest_x","[fslp]")
{
  using forest = fslp::forest_fix<char>;
  using tree = fslp::tree_fix<char>;
  using forest_x = fslp::forest_x_fix<char>;
  using tree_x = fslp::tree_x_fix<char>;
  using forest_x_t = fslp::forest_x_t<char,forest_x,tree_x>;

  forest_x const x{forest_x_t{fslp::var{}}};

  fcppt::variant::match(
      x.get(),
      [](fslp::var) { CHECK(true); },
      [](std::tuple<forest, tree_x, forest> const &) { CHECK(false); });

  forest const e{std::vector<tree>{}};

  tree_x const xt{std::make_tuple('a',x)};

  forest_x const xe{forest_x_t{std::make_tuple(e,xt,e)}};

  fcppt::variant::match(
      xe.get(),
      [](fslp::var) { CHECK(false); },
      [&xt](std::tuple<forest, tree_x, forest> const &v) {
        CHECK(std::get<0>(v)->empty());
        CHECK(std::get<1>(v) == xt);
        CHECK(std::get<2>(v)->empty());
      });
}
