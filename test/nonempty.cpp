#include <fslp/make_nonempty.hpp>
#include <fslp/nonempty.hpp>
#include <fslp/nonempty_catch.hpp>
#include <fcppt/catch/begin.hpp>
#include <fcppt/catch/end.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch_test_macros.hpp>
#include <fcppt/config/external_end.hpp>

FCPPT_CATCH_BEGIN

TEST_CASE("fslp::nonempty","[fslp]")
{
  CHECK(fslp::make_nonempty(1) == fslp::nonempty<int>{1});

  fslp::nonempty<int> v{1};

  CHECK(v.back() == 1);
  CHECK(v.front().empty());
}

FCPPT_CATCH_END
