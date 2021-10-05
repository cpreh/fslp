#include <fslp/apply.hpp>
#include <fslp/forest_fix.hpp>
#include <fslp/forest_t.hpp>
#include <fslp/forest_x_fix.hpp>
#include <fslp/forest_x_r.hpp>
#include <fslp/tree_fix.hpp>
#include <fslp/tree_x_fix.hpp>
#include <fslp/var.hpp>
#include <fcppt/catch/begin.hpp>
#include <fcppt/catch/end.hpp>
#include <fcppt/tuple/make.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
#include <fcppt/config/external_end.hpp>

FCPPT_CATCH_BEGIN

TEST_CASE("fslp::apply","[fslp]")
{
  using forest = fslp::forest_fix<char>;
  using tree = fslp::tree_fix<char>;
  using forest_x = fslp::forest_x_fix<char>;
  using tree_x = fslp::tree_x_fix<char>;
  using forest_t = fslp::forest_t<char,forest,tree>;
  using forest_x_r = fslp::forest_x_r<tree_x>;

  forest const e{forest_t{}};

  CHECK(fslp::apply<char>(forest_x{fcppt::tuple::make(e, forest_x_r{fslp::var{}}, e)}, e) == e);
}

FCPPT_CATCH_END
