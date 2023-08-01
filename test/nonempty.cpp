#include <fslp/make_nonempty.hpp>
#include <fslp/nonempty.hpp>
#include <fslp/nonempty_catch.hpp>
#include <fcppt/catch/begin.hpp>
#include <fcppt/catch/end.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch_test_macros.hpp>
#include <fcppt/config/external_end.hpp>

FCPPT_CATCH_BEGIN
// NOLINTBEGIN(misc-const-correctness,cert-err58-cpp,fuchsia-statically-constructed-objects,misc-use-anonymous-namespace,cppcoreguidelines-avoid-do-while)

TEST_CASE("fslp::nonempty","[fslp]")
{
  CHECK(fslp::make_nonempty(1) == fslp::nonempty<int>{1});

  fslp::nonempty<int> v{1};

  CHECK(v.back() == 1);
  CHECK(v.front().empty());
}

// NOLINTEND(misc-const-correctness,cert-err58-cpp,fuchsia-statically-constructed-objects,misc-use-anonymous-namespace,cppcoreguidelines-avoid-do-while)
FCPPT_CATCH_END
