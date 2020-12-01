#include <fslp/nav/string.hpp>
#include <fslp/nav/simple_string_first.hpp>
#include <fcppt/unique_ptr.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

TEST_CASE("fslp::string_nav","[fslp]")
{
  fcppt::optional::object<fcppt::unique_ptr<fslp::nav::string<char>>> const start{
    fslp::nav::simple_string_first<char>(std::vector<char>{})};

  CHECK_FALSE(start.has_value());
}