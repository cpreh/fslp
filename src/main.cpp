#include <fcppt/copy.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/variant/object.hpp>
#include <fslp/fix.hpp>
#include <fcppt/config/external_begin.hpp>
#include <tuple>
#include <fcppt/config/external_end.hpp>


template <typename Ch>
struct forest_alg_f
{
  template <typename R, typename Rx>
  using type = fcppt::variant::object<fcppt::unit, std::tuple<R,R>, std::tuple<Rx, R>, std::tuple<Ch, R>>;
};

template <typename Ch>
struct forest_alg_fx
{
  template <typename Rx, typename R>
  using type = fcppt::variant::object<std::tuple<Ch, R, R>, std::tuple<Rx, Rx>>;
};

using fslp_fix = fslp::fix<forest_alg_f<char>::type,forest_alg_fx<char>::type>;
using fslp_fix_f = fslp::fix<forest_alg_fx<char>::type,forest_alg_f<char>::type>;

int main()
{
  fslp_fix e{fcppt::unit{}};
  fslp_fix_f f1{std::make_tuple('a', fcppt::copy(e), fcppt::copy(e))};
  fslp_fix test2{std::make_tuple(fcppt::copy(f1), fcppt::copy(e))};
}
