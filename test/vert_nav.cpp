#include <fslp/nav/root.hpp>
#include <fslp/nav/spine_alph.hpp>
#include <fslp/nav/up.hpp>
#include <fslp/nav/vert.hpp>
#include <fcppt/catch/begin.hpp>
#include <fcppt/catch/end.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/tuple/make.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch_test_macros.hpp>
#include <utility>
#include <vector>
#include <fcppt/config/external_end.hpp>

FCPPT_CATCH_BEGIN

TEST_CASE("vert nav","[fslp]")
{
  using Z = char;
  using N = char;
  using sa = fslp::nav::spine_alph<Z, N>;

  std::vector<sa> spine{sa{fcppt::tuple::make('a', 'L', 'R')}, sa{fcppt::tuple::make('b', 'C')}};

  fcppt::optional::object<fslp::nav::vert<Z, N>> start{fslp::nav::root(std::move(spine))};

  fcppt::optional::maybe(
      start,
      [] { CHECK(false); },
      [](fslp::nav::vert<Z, N> const &v) {
        CHECK_FALSE(fslp::nav::up(v).has_value());
      });
}

FCPPT_CATCH_END
