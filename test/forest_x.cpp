#include <fslp/forest_fix.hpp>
#include <fslp/forest_x_fix.hpp>
#include <fslp/forest_x_r.hpp>
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
  using forest_x_r = fslp::forest_x_r<tree_x>;

  forest const e{std::vector<tree>{}};

  forest_x const x{std::make_tuple(e,forest_x_r{fslp::var{}},e)};

  fcppt::variant::match(
      std::get<1>(x.get()),
      [](fslp::var) { CHECK(true); },
      [](tree_x const &) { CHECK(false); });

  tree_x const xt{std::make_tuple('a',x)};

  forest_x const xe{std::make_tuple(e,forest_x_r{xt},e)};

  fcppt::variant::match(
      std::get<1>(xe.get()),
      [](fslp::var) { CHECK(false); },
      [&xt](tree_x const &v) {
        CHECK(v == xt);
      });
}
