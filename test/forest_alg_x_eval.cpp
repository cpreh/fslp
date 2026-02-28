#include <fslp/base.hpp>
#include <fslp/forest_alg_x_eval.hpp>
#include <fslp/forest_alg_x_t.hpp>
#include <fslp/forest_fix.hpp>
#include <fslp/forest_x_fix.hpp>
#include <fslp/forest_x_r.hpp>
#include <fslp/tree_fix.hpp>
#include <fslp/tree_x_fix.hpp>
#include <fslp/var.hpp>
#include <fcppt/catch/begin.hpp>
#include <fcppt/catch/end.hpp>
#include <fcppt/tuple/make.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch_test_macros.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

FCPPT_CATCH_BEGIN
// NOLINTBEGIN(bugprone-throwing-static-initialization,clang-analyzer-optin.core.EnumCastOutOfRange,misc-const-correctness,cert-err58-cpp,fuchsia-statically-constructed-objects,misc-use-anonymous-namespace,cppcoreguidelines-avoid-do-while)

TEST_CASE("fslp::forest_alg_x_eval","[fslp]")
{
  using forest = fslp::forest_fix<char>;
  using tree = fslp::tree_fix<char>;
  using forest_x = fslp::forest_x_fix<char>;
  using tree_x = fslp::tree_x_fix<char>;
  using forest_x_r = fslp::forest_x_r<tree_x>;
  using forest_alg_x_t = fslp::forest_alg_x_t<char,forest_x,forest>;

  forest const e{std::vector<tree>{}};
  forest_x const i{fcppt::tuple::make(e, forest_x_r{fslp::var{}}, e)};

  CHECK(
      fslp::forest_alg_x_eval<char>(forest_alg_x_t{fcppt::tuple::make(fslp::base{'a'}, e, e)}) ==
      forest_x{
          fcppt::tuple::make(e, forest_x_r{tree_x{fcppt::tuple::make(fslp::base{'a'}, i)}}, e)});
}

// NOLINTEND(bugprone-throwing-static-initialization,clang-analyzer-optin.core.EnumCastOutOfRange,misc-const-correctness,cert-err58-cpp,fuchsia-statically-constructed-objects,misc-use-anonymous-namespace,cppcoreguidelines-avoid-do-while)
FCPPT_CATCH_END
