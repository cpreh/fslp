#include <fslp/base.hpp>
#include <fslp/fix.hpp>
#include <fslp/forest_alg_eval.hpp>
#include <fslp/forest_alg_fix.hpp>
#include <fslp/forest_alg_t.hpp>
#include <fslp/forest_alg_x_eval.hpp>
#include <fslp/forest_alg_x_fix.hpp>
#include <fslp/forest_alg_x_t.hpp>
#include <fslp/forest_fix.hpp>
#include <fslp/forest_t.hpp>
#include <fslp/forest_x_fix.hpp>
#include <fslp/tree_fix.hpp>
#include <fslp/tree_t.hpp>
#include <fslp/unfold.hpp>
#include <fcppt/overload.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/algorithm/fold.hpp>
#include <fcppt/catch/begin.hpp>
#include <fcppt/catch/end.hpp>
#include <fcppt/mpl/map/element.hpp>
#include <fcppt/mpl/map/object.hpp>
#include <fcppt/tuple/get.hpp>
#include <fcppt/tuple/make.hpp>
#include <fcppt/tuple/object.hpp>
#include <fcppt/variant/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch_test_macros.hpp>
#include <functional>
#include <vector>
#include <fcppt/config/external_end.hpp>

FCPPT_CATCH_BEGIN
// NOLINTBEGIN(misc-const-correctness,cert-err58-cpp,fuchsia-statically-constructed-objects,misc-use-anonymous-namespace,cppcoreguidelines-avoid-do-while)

TEST_CASE("fslp::unfold forest", "[fslp]")
{
  using forest_i = fslp::forest_t<char, int, int>;
  using tree_i = fslp::tree_t<char, int, int>;

  auto const size{fcppt::overload(
      [](forest_i const &f) -> int { return fcppt::algorithm::fold(f, 0, std::plus<int>{}); },
      [](tree_i const &t) -> int { return 1 + fcppt::tuple::get<1>(t); })};

  using forest = fslp::forest_fix<char>;
  using tree = fslp::tree_fix<char>;

  forest const e{std::vector<tree>{}};
  tree const t{fcppt::tuple::make(fslp::base{'a'}, e)};
  forest const tt{std::vector<tree>{t, t}};

  using types = fcppt::mpl::map::
      object<fcppt::mpl::map::element<forest, int>, fcppt::mpl::map::element<tree, int>>;

  CHECK(fslp::unfold<types>(tt, size) == 2);
}

TEST_CASE("fslp::unfold forest_alg", "[fslp]")
{
  using forest = fslp::forest_fix<char>;
  using forest_x = fslp::forest_x_fix<char>;
  using tree = fslp::tree_fix<char>;

  auto const func{fcppt::overload(
      [](fslp::forest_alg_t<char, forest, forest_x> const &f) -> forest {
        return fslp::forest_alg_eval<char>(f);
      },
      [](fslp::forest_alg_x_t<char, forest_x, forest> const &f) -> forest_x {
        return fslp::forest_alg_x_eval<char>(f);
      })};

  using forest_alg_fix = fslp::forest_alg_fix<char>;
  using forest_alg_x_fix = fslp::forest_alg_x_fix<char>;
  using forest_alg_t = fslp::forest_alg_t<char, forest_alg_fix, forest_alg_x_fix>;

  forest_alg_fix const e{forest_alg_t{fslp::base{fcppt::unit{}}}};

  forest const fe{std::vector<tree>{}};

  using types = fcppt::mpl::map::object<
      fcppt::mpl::map::element<forest_alg_fix, forest>,
      fcppt::mpl::map::element<forest_alg_x_fix, forest_x>>;
  CHECK(fslp::unfold<types>(e, func) == fe);
}

namespace
{
struct S1
{
};
bool operator==(S1, S1) { return true; }
struct S2
{
};

template <typename T1, typename T2>
using test1 = fcppt::variant::object<fslp::base<int>, T2>;

template <typename T2, typename T1>
using test2 = fcppt::tuple::object<fslp::base<char>, std::vector<T1>>;

}

TEST_CASE("fslp::unfold two types", "[fslp]")
{
  using test_fix_1 = fslp::fix<test1, test2>;
  using test_fix_2 = fslp::fix<test2, test1>;
  using test_1_t = test1<test_fix_1, test_fix_2>;
  using test_2_t = test2<test_fix_2, test_fix_1>;

  auto const func{fcppt::overload(
      [](test1<S1, S2> const &) -> S1 { return S1{}; },
      [](test2<S2, S1> const &) -> S2 { return S2{}; })};

  test_fix_2 const i{test_2_t{fcppt::tuple::make(fslp::base{'c'}, std::vector<test_fix_1>{})}};
  test_fix_1 const e{test_1_t{i}};

  using types = fcppt::mpl::map::
      object<fcppt::mpl::map::element<test_fix_1, S1>, fcppt::mpl::map::element<test_fix_2, S2>>;

  CHECK(fslp::unfold<types>(e, func) == S1{});
}

// NOLINTEND(misc-const-correctness,cert-err58-cpp,fuchsia-statically-constructed-objects,misc-use-anonymous-namespace,cppcoreguidelines-avoid-do-while)
FCPPT_CATCH_END
