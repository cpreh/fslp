#include <fslp/apply.hpp>
#include <fslp/forest_t.hpp>
#include <fslp/forest_x_t.hpp>
#include <fslp/var.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
#include <fcppt/config/external_end.hpp>


TEST_CASE("fslp::apply","[fslp]")
{
  using forest = fslp::forest_t<char>;
  using forest_x = fslp::forest_x_t<char>;

  CHECK(fslp::apply<char>(forest_x{fslp::var{}}, forest{}) == forest{});
}
