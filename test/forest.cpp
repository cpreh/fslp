#include <fslp/forest_fix.hpp>
#include <fslp/tree_fix.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
#include <tuple>
#include <vector>
#include <fcppt/config/external_end.hpp>

TEST_CASE("fslp::forest","[fslp]")
{
  using forest = fslp::forest_fix<char>;
  using tree = fslp::tree_fix<char>;

  forest const e{std::vector<tree>{}};

  CHECK(e->empty());

  tree const t{std::make_tuple('a',e)};

  CHECK(std::get<0>(t.get()) == 'a');

  forest const tt{std::vector<tree>{t,t}};

  CHECK(std::get<0>(tt->at(0U).get()) == 'a');
}
