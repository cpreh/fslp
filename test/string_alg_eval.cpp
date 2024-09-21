#include <fslp/base.hpp>
#include <fslp/string_alg_eval.hpp>
#include <fslp/string_alg_t.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/catch/begin.hpp>
#include <fcppt/catch/end.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch_test_macros.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

FCPPT_CATCH_BEGIN
// NOLINTBEGIN(clang-analyzer-optin.core.EnumCastOutOfRange,misc-const-correctness,cert-err58-cpp,fuchsia-statically-constructed-objects,misc-use-anonymous-namespace,cppcoreguidelines-avoid-do-while)

TEST_CASE("fslp::string_alg_eval","[fslp]")
{
  using string = std::vector<char>;
  using string_alg_t = fslp::string_alg_t<char, string>;

  string const e{};

  CHECK(fslp::string_alg_eval<char>(string_alg_t{fslp::base{fcppt::unit{}}}) == e);
}

// NOLINTEND(clang-analyzer-optin.core.EnumCastOutOfRange,misc-const-correctness,cert-err58-cpp,fuchsia-statically-constructed-objects,misc-use-anonymous-namespace,cppcoreguidelines-avoid-do-while)
FCPPT_CATCH_END
