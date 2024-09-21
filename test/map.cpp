#include <fslp/base.hpp>
#include <fslp/make_nonempty.hpp>
#include <fslp/map.hpp>
#include <fslp/nonempty_catch.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/output_to_std_string.hpp>
#include <fcppt/overload.hpp>
#include <fcppt/widen.hpp>
#include <fcppt/catch/begin.hpp>
#include <fcppt/catch/end.hpp>
#include <fcppt/catch/tuple.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/catch/variant.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/tuple/make.hpp>
#include <fcppt/tuple/object.hpp>
#include <fcppt/variant/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch_test_macros.hpp>
#include <string>
#include <vector>
#include <fcppt/config/external_end.hpp>

FCPPT_CATCH_BEGIN
// NOLINTBEGIN(clang-analyzer-optin.core.EnumCastOutOfRange,misc-const-correctness,cert-err58-cpp,fuchsia-statically-constructed-objects,misc-use-anonymous-namespace,cppcoreguidelines-avoid-do-while)

TEST_CASE("fslp::map","[fslp]")
{
  CHECK(fslp::map([]{}, fslp::base{10}) == fslp::base{10});

  CHECK(
      fslp::map([](std::string const &x) { return fcppt::widen(x); }, std::string{"test"}) ==
      std::wstring{L"test"});

  CHECK(
      fslp::map(
          [](std::string const &x) { return fcppt::widen(x); },
          fcppt::tuple::make(std::string{"test"})) == fcppt::tuple::make(std::wstring{L"test"}));

  using long_t = long; // NOLINT(google-runtime-int)
  auto const func{fcppt::overload(
      [](int const x) { return long_t{x}; }, [](std::string const &s) { return fcppt::widen(s); })};

  CHECK(
      fslp::map(func, fcppt::tuple::make(4, std::string{"test"})) ==
      fcppt::tuple::make(4L, std::wstring{L"test"}));

  CHECK(fslp::map([](int const x) { return long_t{x}; }, std::vector<int>{1,2,3}) == std::vector<long_t>{1L,2L,3L});

  using variant = fcppt::variant::object<std::string, int>;
  using variant_r = fcppt::variant::object<std::wstring, long_t>;

  CHECK(fslp::map(func, variant{std::string{"test"}}) == variant_r{std::wstring{L"test"}});
  CHECK(fslp::map(func, variant{4}) == variant_r{4L});

  using variant2 =
      fcppt::variant::object<fcppt::tuple::object<std::string>, std::vector<std::string>>;
  using variant2_r =
      fcppt::variant::object<fcppt::tuple::object<std::wstring>, std::vector<std::wstring>>;

  CHECK(
      fslp::map(
          [](std::string const &x) { return fcppt::widen(x); },
          variant2{fcppt::tuple::make(std::string{"test"})}) ==
      variant2_r{fcppt::tuple::make(std::wstring{L"test"})});

  CHECK(
      fslp::map(
          [](int const i) { return fcppt::output_to_std_string(i); }, fslp::make_nonempty(4)) ==
      fslp::make_nonempty(std::string{"4"}));
}

// NOLINTEND(clang-analyzer-optin.core.EnumCastOutOfRange,misc-const-correctness,cert-err58-cpp,fuchsia-statically-constructed-objects,misc-use-anonymous-namespace,cppcoreguidelines-avoid-do-while)
FCPPT_CATCH_END
