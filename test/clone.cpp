#include <fslp/clone.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/catch/begin.hpp>
#include <fcppt/catch/end.hpp>
#include <fcppt/container/make.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace
{
class test
{
public:
  explicit test(int const _i) : i_{_i} {}

  [[nodiscard]] fcppt::unique_ptr<test> clone() const
  {
    return fcppt::make_unique_ptr<test>(this->i_);
  }
  [[nodiscard]] int value() const { return i_; }
private:
  int const i_;
};
}

FCPPT_CATCH_BEGIN

TEST_CASE("fslp::clone", "[fslp]")
{
  CHECK(fslp::clone(fcppt::make_unique_ptr<test>(42))->value() == 42);

  using ptr_vector = std::vector<fcppt::unique_ptr<test>>;
  ptr_vector const tmp{
      fcppt::container::make<ptr_vector>(
          fcppt::make_unique_ptr<test>(2), fcppt::make_unique_ptr<test>(3))};
}

FCPPT_CATCH_END