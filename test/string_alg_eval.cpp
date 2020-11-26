#include <fslp/base.hpp>
#include <fslp/string_alg_eval.hpp>
#include <fslp/string_alg_t.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

TEST_CASE("fslp::string_alg_eval","[fslp]")
{
  using string = std::vector<char>;
  using string_alg_t = fslp::string_alg_t<char, string>;

  string const e{};

  CHECK(fslp::string_alg_eval<char>(string_alg_t{fslp::base{fcppt::unit{}}}) == e);
}
