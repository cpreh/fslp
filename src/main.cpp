#include <fcppt/copy.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/variant/object.hpp>
#include <fslp/fix.hpp>
#include <fcppt/config/external_begin.hpp>
#include <tuple>
#include <vector>
#include <fcppt/config/external_end.hpp>

#include <fcppt/container/join.hpp>
#include <fcppt/variant/match.hpp>

template <typename Ch>
struct forest_alg_f
{
  template <typename R, typename Rx>
  using type = fcppt::variant::object<fcppt::unit, std::tuple<R,R>, std::tuple<Rx, R>, std::tuple<Ch, R>>;
};

template <typename Ch, typename R, typename Rx>
using forest_alg_f_t = typename forest_alg_f<Ch>:: template type<R,Rx>;

template <typename Ch>
struct forest_alg_fx
{
  template <typename Rx, typename R>
  using type = fcppt::variant::object<std::tuple<Ch, R, R>, std::tuple<Rx, Rx>>;
};

using fslp_fix = fslp::fix<forest_alg_f<char>::type,forest_alg_fx<char>::type>;
using fslp_fix_f = fslp::fix<forest_alg_fx<char>::type,forest_alg_f<char>::type>;

template <typename Ch>
struct tree;

template <typename Ch>
struct forest;

template <typename Ch>
struct tree
{
  using type = std::tuple<Ch, forest<Ch>>;
};

template<typename Ch>
using tree_t = typename tree<Ch>::type;

template <typename Ch>
struct forest
{
  using type = std::vector<tree<Ch>>;
};

template <typename Ch>
using forest_t = typename forest<Ch>::type;

template <typename Ch>
struct tree_x;

template <typename Ch>
struct forest_x;

template <typename Ch>
struct tree_x
{
  using type = std::tuple<Ch, forest_x<Ch>>;
};

struct var {};

template <typename Ch>
struct forest_x
{
  using type = fcppt::variant::
      object<var, std::tuple<forest<Ch>, forest_x<Ch>>, std::tuple<forest_x<Ch>, forest<Ch>>>;
};

template <typename Ch>
using forest_x_t = typename forest_x<Ch>::type;

template<typename Ch>
forest_t<Ch> apply(forest_x_t<Ch> const &x, forest_t<Ch> const &f)
{
  return fcppt::variant::match(x,
    [&f](var) { return f; },
    [&f](std::tuple<forest<Ch>, forest_x<Ch>> const &r) {
      return fcppt::container::join(std::get<0>(r),apply(std::get<1>(r),f));
    },
    [&f](std::tuple<forest_x<Ch>, forest<Ch>> const &r) {
      return fcppt::container::join(apply(std::get<0>(r),f),std::get<1>(r));
    });
}

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
