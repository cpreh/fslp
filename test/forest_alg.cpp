
#include <fslp/forest_alg_fix.hpp>
#include <fslp/forest_alg_x_fix.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
#include <tuple>
#include <fcppt/config/external_end.hpp>


TEST_CASE("fslp::forest_alg","[fslp]")
{
  using forest_alg = fslp::forest_alg_fix<char>;
  using forest_alg_x = fslp::forest_alg_x_fix<char>;

  forest_alg const e{fcppt::unit{}};
  forest_alg_x const f1{std::make_tuple('a', e, e)};
  forest_alg const test2{std::make_tuple(f1, e)};
}