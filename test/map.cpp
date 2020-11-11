#include <fslp/base.hpp>
#include <fslp/map.hpp>
#include <fcppt/overload.hpp>
#include <fcppt/widen.hpp>
#include <fcppt/catch/variant.hpp>
#include <fcppt/variant/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
#include <string>
#include <tuple>
#include <vector>
#include <fcppt/config/external_end.hpp>

TEST_CASE("fslp::map","[fslp]")
{
  CHECK(fslp::map([]{}, fslp::base{10}) == fslp::base{10});

  CHECK(
      fslp::map([](std::string const &x) { return fcppt::widen(x); }, std::string{"test"}) ==
      std::wstring{L"test"});

  CHECK(
      fslp::map(
          [](std::string const &x) { return fcppt::widen(x); },
          std::make_tuple(std::string{"test"})) == std::make_tuple(std::wstring{L"test"}));

  using long_t = long; // NOLINT(google-runtime-int)
  auto const func{fcppt::overload(
      [](int const x) { return long_t{x}; }, [](std::string const &s) { return fcppt::widen(s); })};

  CHECK(
      fslp::map(func, std::make_tuple(4, std::string{"test"})) ==
      std::make_tuple(4L, std::wstring{L"test"}));

  CHECK(fslp::map([](int const x) { return long_t{x}; }, std::vector<int>{1,2,3}) == std::vector<long_t>{1L,2L,3L});

  using variant = fcppt::variant::object<std::string, int>;
  using variant_r = fcppt::variant::object<std::wstring, long_t>;

  CHECK(fslp::map(func, variant{std::string{"test"}}) == variant_r{std::wstring{L"test"}});
  CHECK(fslp::map(func, variant{4}) == variant_r{4L});

  using variant2 = fcppt::variant::object<std::tuple<std::string>,std::vector<std::string>>;
  using variant2_r = fcppt::variant::object<std::tuple<std::wstring>,std::vector<std::wstring>>;

  CHECK(
      fslp::map(
          [](std::string const &x) { return fcppt::widen(x); },
          variant2{std::make_tuple(std::string{"test"})}) ==
      variant2_r{std::make_tuple(std::wstring{L"test"})});
}
