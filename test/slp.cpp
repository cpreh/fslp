#include <fslp/base.hpp>
#include <fslp/fold.hpp>
#include <fslp/forest_fix.hpp>
#include <fslp/forest_t.hpp>
#include <fslp/slp.hpp>
#include <fslp/tree_fix.hpp>
#include <fslp/tree_t.hpp>
#include <fcppt/function_impl.hpp>
#include <fcppt/overload.hpp>
#include <fcppt/catch/begin.hpp>
#include <fcppt/catch/end.hpp>
#include <fcppt/mpl/map/element.hpp>
#include <fcppt/mpl/map/object.hpp>
#include <fcppt/tuple/get.hpp>
#include <fcppt/tuple/make.hpp>
#include <fcppt/tuple/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch_test_macros.hpp>
#include <cstdint>
#include <type_traits>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace
{
enum class N1 : std::uint8_t
{
  A
};
enum class N2 : std::uint8_t
{
  A
};

template <typename F, typename T>
using forest_c = fslp::forest_t<char, F, T>;

template <typename T, typename F>
using tree_c = fslp::tree_t<char, T, F>;

using test_slp = fslp::slp<forest_c, tree_c>::type<N1, N2>;

using forest_N = forest_c<N1, N2>;
using tree_N = tree_c<N2, N1>;

static_assert(std::is_same_v<
              test_slp,
              fcppt::tuple::object<fcppt::function<forest_N(N1)>, fcppt::function<tree_N(N2)>>>);
}

FCPPT_CATCH_BEGIN
// NOLINTBEGIN(misc-const-correctness,cert-err58-cpp,fuchsia-statically-constructed-objects,misc-use-anonymous-namespace,cppcoreguidelines-avoid-do-while)

TEST_CASE("fslp::fold slp", "[fslp]")
{
  test_slp const slp{fcppt::tuple::make(
      fcppt::function<forest_N(N1)>{[](N1) { return forest_N{std::vector<N2>{}}; }},
      fcppt::function<tree_N(N2)>{
          [](N2) { return tree_N{fcppt::tuple::make(fslp::base{'a'}, N1::A)}; }})};

  auto const eval{fcppt::overload(
      [&slp](N1 const v) -> forest_N { return fcppt::tuple::get<0>(slp)(v); },
      [&slp](N2 const v) -> tree_N { return fcppt::tuple::get<1>(slp)(v); })};

  using forest = fslp::forest_fix<char>;
  using tree = fslp::tree_fix<char>;

  using types = fcppt::mpl::map::
      object<fcppt::mpl::map::element<N1, forest>, fcppt::mpl::map::element<N2, tree>>;
  CHECK(fslp::fold<types>(N1::A, eval) == forest{std::vector<tree>{}});
}

// NOLINTEND(misc-const-correctness,cert-err58-cpp,fuchsia-statically-constructed-objects,misc-use-anonymous-namespace,cppcoreguidelines-avoid-do-while)
FCPPT_CATCH_END
