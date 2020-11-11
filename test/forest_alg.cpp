#include <fslp/base.hpp>
#include <fslp/forest_alg_fix.hpp>
#include <fslp/forest_alg_t.hpp>
#include <fslp/forest_alg_x_fix.hpp>
#include <fslp/forest_alg_x_t.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
#include <tuple>
#include <fcppt/config/external_end.hpp>


TEST_CASE("fslp::forest_alg","[fslp]")
{
  using forest_alg = fslp::forest_alg_fix<char>;
  using forest_alg_x = fslp::forest_alg_x_fix<char>;
  using forest_alg_t = fslp::forest_alg_t<char,forest_alg,forest_alg_x>;
  using forest_alg_x_t = fslp::forest_alg_x_t<char,forest_alg_x,forest_alg>;

  forest_alg const e{forest_alg_t{fslp::base{fcppt::unit{}}}};
  forest_alg_x const f1{forest_alg_x_t{std::make_tuple(fslp::base{'a'}, e, e)}};
  forest_alg const test2{forest_alg_t{std::make_tuple(f1, e)}};


}
