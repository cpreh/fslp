#include <fslp/forest_alg_eval.hpp>
#include <fslp/forest_alg_t.hpp>
#include <fslp/forest_fix.hpp>
#include <fslp/forest_x_fix.hpp>
#include <fslp/tree_fix.hpp>
#include <fcppt/catch/begin.hpp>
#include <fcppt/catch/end.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch_test_macros.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

FCPPT_CATCH_BEGIN
// NOLINTBEGIN(misc-const-correctness,cert-err58-cpp,fuchsia-statically-constructed-objects,misc-use-anonymous-namespace,cppcoreguidelines-avoid-do-while)

TEST_CASE("fslp::forest_alg_eval","[fslp]")
{
  using forest = fslp::forest_fix<char>;
  using tree = fslp::tree_fix<char>;
  using forest_x = fslp::forest_x_fix<char>;
  using forest_alg_t = fslp::forest_alg_t<char,forest,forest_x>;

  forest const e{std::vector<tree>{}};

  CHECK(fslp::forest_alg_eval<char>(forest_alg_t{fslp::base{fcppt::unit{}}}) == e);
}

// NOLINTEND(misc-const-correctness,cert-err58-cpp,fuchsia-statically-constructed-objects,misc-use-anonymous-namespace,cppcoreguidelines-avoid-do-while)
FCPPT_CATCH_END
