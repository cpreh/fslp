#include <fslp/base.hpp>
#include <fslp/forest_fix.hpp>
#include <fslp/tree_fix.hpp>
#include <fcppt/catch/begin.hpp>
#include <fcppt/catch/end.hpp>
#include <fcppt/tuple/get.hpp>
#include <fcppt/tuple/make.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch_test_macros.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

FCPPT_CATCH_BEGIN
// NOLINTBEGIN(misc-const-correctness,cert-err58-cpp,fuchsia-statically-constructed-objects,misc-use-anonymous-namespace,cppcoreguidelines-avoid-do-while)

TEST_CASE("fslp::forest","[fslp]")
{
  using forest = fslp::forest_fix<char>;
  using tree = fslp::tree_fix<char>;

  forest const e{std::vector<tree>{}};

  CHECK(e.unfix().empty());

  tree const t{fcppt::tuple::make(fslp::base{'a'},e)};

  CHECK(fcppt::tuple::get<0>(t.unfix()).get() == 'a');

  forest const tt{std::vector<tree>{t,t}};

  CHECK(fcppt::tuple::get<0>(tt.unfix().at(0U).unfix()).get() == 'a');
}

// NOLINTEND(misc-const-correctness,cert-err58-cpp,fuchsia-statically-constructed-objects,misc-use-anonymous-namespace,cppcoreguidelines-avoid-do-while)
FCPPT_CATCH_END
