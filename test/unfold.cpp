#include <fslp/forest_alg_eval.hpp>
#include <fslp/forest_alg_fix.hpp>
#include <fslp/forest_alg_t.hpp>
#include <fslp/forest_alg_x_fix.hpp>
#include <fslp/forest_alg_x_t.hpp>
#include <fslp/forest_fix.hpp>
#include <fslp/forest_t.hpp>
#include <fslp/forest_x.hpp>
#include <fslp/tree_fix.hpp>
#include <fslp/tree_t.hpp>
#include <fslp/unfold.hpp>
#include <fcppt/overload.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/algorithm/fold.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
#include <functional>
#include <tuple>
#include <vector>
#include <fcppt/config/external_end.hpp>

TEST_CASE("fslp::unfold forest","[fslp]")
{
  using forest_i = fslp::forest_t<char,int,int>;
  using tree_i = fslp::tree_t<char,int,int>;

  auto const size{fcppt::overload(
      [](forest_i const &f) -> int { return fcppt::algorithm::fold(f, 0, std::plus<int>{} ); },
      [](tree_i const &t) -> int { return 1 + std::get<1>(t); })};

  using forest = fslp::forest_fix<char>;
  using tree = fslp::tree_fix<char>;

  forest const e{std::vector<tree>{}};
  tree const t{std::make_tuple('a',e)};
  forest const tt{std::vector<tree>{t,t}};

  CHECK(fslp::unfold<int>(tt,size) == 2);
}

TEST_CASE("fslp::unfold forest_alg","[fslp]")
{
  using forest = fslp::forest_fix<char>;
  using forest_x = fslp::forest_x_fix<char>;
  using tree = fslp::tree_fix<char>;

  auto const func{fcppt::overload(
      //[](fslp::forest_alg_t<char, forest, forest_x> const &f) -> forest {
      [](auto const &) -> forest {
        return forest{std::vector<tree>{}};
      },
      [](fslp::forest_alg_x_t<char, forest_x, forest> const &f) -> forest_x {
        return fslp::forest_alg_eval<char>(f);
      })};

  using forest_alg_fix = fslp::forest_alg_fix<char>;
  using forest_alg_x_fix = fslp::forest_alg_x_fix<char>;
  using forest_alg_t = fslp::forest_alg_t<char,forest_alg_fix,forest_alg_x_fix>;

  forest_alg_fix const e{forest_alg_t{fcppt::unit{}}};

  forest const fe{std::vector<tree>{}};

  CHECK(fslp::unfold<forest,forest_x>(e,func) == fe);
}
