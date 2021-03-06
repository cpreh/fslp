#include <fslp/compose.hpp>
#include <fslp/forest_fix.hpp>
#include <fslp/forest_x_fix.hpp>
#include <fslp/forest_x_r.hpp>
#include <fslp/tree_fix.hpp>
#include <fslp/tree_x_fix.hpp>
#include <fslp/var.hpp>
#include <fcppt/catch/begin.hpp>
#include <fcppt/catch/end.hpp>
#include <fcppt/tuple/make.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch_test_macros.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


FCPPT_CATCH_BEGIN

TEST_CASE("fslp::compose","[fslp]")
{
  using forest = fslp::forest_fix<char>;
  using tree = fslp::tree_fix<char>;
  using forest_x = fslp::forest_x_fix<char>;
  using tree_x = fslp::tree_x_fix<char>;
  using forest_x_r = fslp::forest_x_r<tree_x>;

  forest const e{std::vector<tree>{}};
  forest_x const x{fcppt::tuple::make(e,forest_x_r{fslp::var{}},e)};

  CHECK(fslp::compose<char>(x,x) == x);
}

FCPPT_CATCH_END
