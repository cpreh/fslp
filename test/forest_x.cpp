#include <fslp/base.hpp>
#include <fslp/forest_fix.hpp>
#include <fslp/forest_x_fix.hpp>
#include <fslp/forest_x_r.hpp>
#include <fslp/tree_fix.hpp>
#include <fslp/tree_x_fix.hpp>
#include <fslp/var.hpp>
#include <fcppt/catch/begin.hpp>
#include <fcppt/catch/end.hpp>
#include <fcppt/tuple/get.hpp>
#include <fcppt/tuple/make.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch_test_macros.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

FCPPT_CATCH_BEGIN
// NOLINTBEGIN(misc-const-correctness,cert-err58-cpp,fuchsia-statically-constructed-objects,misc-use-anonymous-namespace,cppcoreguidelines-avoid-do-while)

TEST_CASE("fslp::forest_x","[fslp]")
{
  using forest = fslp::forest_fix<char>;
  using tree = fslp::tree_fix<char>;
  using forest_x = fslp::forest_x_fix<char>;
  using tree_x = fslp::tree_x_fix<char>;
  using forest_x_r = fslp::forest_x_r<tree_x>;

  forest const e{std::vector<tree>{}};

  forest_x const x{fcppt::tuple::make(e,forest_x_r{fslp::var{}},e)};

  fcppt::variant::match(
      fcppt::tuple::get<1>(x.unfix()),
      [](fslp::var) { CHECK(true); },
      [](tree_x const &) { CHECK(false); });

  tree_x const xt{fcppt::tuple::make(fslp::base{'a'},x)};

  forest_x const xe{fcppt::tuple::make(e,forest_x_r{xt},e)};

  fcppt::variant::match(
      fcppt::tuple::get<1>(xe.unfix()),
      [](fslp::var) { CHECK(false); },
      [&xt](tree_x const &v) {
        CHECK(v == xt);
      });
}

// NOLINTEND(misc-const-correctness,cert-err58-cpp,fuchsia-statically-constructed-objects,misc-use-anonymous-namespace,cppcoreguidelines-avoid-do-while)
FCPPT_CATCH_END
