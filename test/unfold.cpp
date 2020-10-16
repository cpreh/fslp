#include <fslp/forest_fix.hpp>
#include <fslp/forest_t.hpp>
#include <fslp/tree_fix.hpp>
#include <fslp/tree_t.hpp>
#include <fslp/unfold.hpp>
#include <fcppt/overload.hpp>
#include <fcppt/algorithm/fold.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
#include <functional>
#include <tuple>
#include <vector>
#include <fcppt/config/external_end.hpp>

TEST_CASE("fslp::unfold","[fslp]")
{
  using forest = fslp::forest_fix<char>;
  using tree = fslp::tree_fix<char>;
  using forest_i = fslp::forest_t<char,int,int>;
  using tree_i = fslp::tree_t<char,int,int>;

  auto const func{fcppt::overload(
      [](forest_i const &f) { return fcppt::algorithm::fold(f, 0, std::plus<int>{} ); },
      [](tree_i const &t) { return 1 + std::get<1>(t); })};

  forest const e{std::vector<tree>{}};
  tree const t{std::make_tuple('a',e)};
  forest const tt{std::vector<tree>{t,t}};

  CHECK(fslp::unfold<int>(tt,func) == 2);
}
