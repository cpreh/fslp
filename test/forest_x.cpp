#include <fslp/forest_x_fix.hpp>
#include <fslp/tree_x_fix.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


TEST_CASE("fslp::forest_x","[fslp]")
{
  using forest_x = fslp::forest_x_fix<char>;
  using tree_x = fslp::tree_x_fix<char>;

  CHECK(forest_x{std::vector<tree_x>{}}->empty());
}
