#include <fslp/compose.hpp>
#include <fslp/forest_x_fix.hpp>
#include <fslp/forest_x_t.hpp>
#include <fslp/tree_x_fix.hpp>
#include <fslp/var.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
#include <fcppt/config/external_end.hpp>


TEST_CASE("fslp::compose","[fslp]")
{
  using forest_x = fslp::forest_x_fix<char>;
  using tree_x = fslp::tree_x_fix<char>;
  using forest_x_t = fslp::forest_x_t<char,forest_x,tree_x>;

  forest_x const x{forest_x_t{fslp::var{}}};

  CHECK(fslp::compose<char>(x,x) == x);
}
