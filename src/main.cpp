#include <fslp/forest_alg_fix.hpp>
#include <fslp/forest_alg_x_fix.hpp>
#include <fcppt/copy.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/config/external_begin.hpp>
#include <tuple>
#include <fcppt/config/external_end.hpp>


#if 0
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
#endif

int main()
{
  fslp::forest_alg_fix<char> e{fcppt::unit{}};
  fslp::forest_alg_x_fix<char> f1{std::make_tuple('a', fcppt::copy(e), fcppt::copy(e))};
  fslp::forest_alg_fix<char> test2{std::make_tuple(fcppt::copy(f1), fcppt::copy(e))};

}
