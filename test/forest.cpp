#include <fslp/forest_fix.hpp>
#include <fslp/tree_fix.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


TEST_CASE("fslp::forest","[fslp]")
{
  using forest = fslp::forest_fix<char>;
  using tree = fslp::tree_fix<char>;

  CHECK(forest{std::vector<tree>{}}.get().empty());
}
