#include <fcppt/copy.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/variant/object.hpp>
#include <fslp/fix.hpp>
#include <fcppt/config/external_begin.hpp>
#include <tuple>
#include <vector>
#include <fcppt/config/external_end.hpp>


using fslp_fix = fslp::fix<fslp::forest_alg_t<char>,forest_alg_x<char>::type>;
using fslp_fix_f = fslp::fix<forest_alg_x<char>::type,fslp::forest_alg_t<char>>;

template <typename Ch>
struct forest_alg_def
{
  auto eval(forest_alg_f_t<Ch, forest_t<Ch>, forest_x_t<Ch>> const &exp)
  {
    return fcppt::variant::match(
        exp,
        [](fcppt::unit) { return forest_t<Ch>{}; },
        [](std::tuple<forest_t<Ch>, forest_t<Ch>> const &r) {
          return fcppt::container::join(std::get<0>(r), std::get<1>(r));
        },
        [](std::tuple<forest_x_t<Ch>, forest_t<Ch>> const &r) {
          return apply(std::get<0>(r), std::get<1>(r));
        },
        [](std::tuple<Ch, forest_t<Ch>> const &r) {
          return forest_t<Ch>{tree_t<Ch>{std::get<0>(r)}};
        });
  }
};

int main()
{
  fslp_fix e{fcppt::unit{}};
  fslp_fix_f f1{std::make_tuple('a', fcppt::copy(e), fcppt::copy(e))};
  fslp_fix test2{std::make_tuple(fcppt::copy(f1), fcppt::copy(e))};

}
