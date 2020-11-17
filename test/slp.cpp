#include <fslp/base.hpp>
#include <fslp/forest.hpp>
#include <fslp/forest_t.hpp>
#include <fslp/tree.hpp>
#include <fslp/tree_t.hpp>
#include <fslp/slp.hpp>
#include <fcppt/function_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
#include <tuple>
#include <type_traits>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace
{

enum class N1 { A };
enum class N2 { A };

using test_slp = fslp::slp<fslp::forest<char>::type, fslp::tree<char>::type>::type<N1, N2>;

using forest_N = fslp::forest_t<char,N1,N2>;
using tree_N = fslp::tree_t<char,N2,N1>;

static_assert(std::is_same_v<
              test_slp,
              std::tuple<fcppt::function<forest_N(N1)>, fcppt::function<tree_N(N2)>>>);
}

TEST_CASE("fslp::fold slp","[fslp]")
{
  test_slp const slp{std::make_tuple(
      fcppt::function<forest_N(N1)>{[](N1) { return forest_N{std::vector<N2>{}}; }},
      fcppt::function<tree_N(N2)>{
          [](N2) { return tree_N{std::make_tuple(fslp::base{'a'}, N1::A)}; }})};
}
