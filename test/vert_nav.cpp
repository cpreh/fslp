#include <fslp/clone.hpp>
#include <fslp/nav/root.hpp>
#include <fslp/nav/spine_alph.hpp>
#include <fslp/nav/up.hpp>
#include <fslp/nav/vert.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
#include <utility>
#include <tuple>
#include <vector>
#include <fcppt/config/external_end.hpp>

TEST_CASE("vert nav","[fslp]")
{
  using Z = char;
  using N = char;
  using sa = fslp::nav::spine_alph<Z, N>;

  std::vector<sa> spine{sa{std::make_tuple('a', 'L', 'R')}, sa{std::make_tuple('b', 'C')}};

  fcppt::optional::object<fslp::nav::vert<Z, N>> start{fslp::nav::root(std::move(spine))};

  fcppt::optional::maybe(
      start,
      [] { CHECK(false); },
      [](fslp::nav::vert<Z, N> const &v) {
        CHECK_FALSE(fslp::nav::up(fslp::clone(v)).has_value());
      });
}
