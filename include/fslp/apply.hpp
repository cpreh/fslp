#ifndef FSLP_APPLY_HPP_INCLUDED
#define FSLP_APPLY_HPP_INCLUDED

#include <fslp/forest_t.hpp>
#include <fslp/forest_x_t.hpp>
#include <fcppt/container/join.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <tuple>
#include <fcppt/config/external_end.hpp>

namespace fslp
{

template<typename Ch>
fslp::forest_t<Ch> apply(fslp::forest_x_t<Ch> const &x, fslp::forest_t<Ch> const &f)
{
  return fcppt::variant::match(x,
    [&f](var) { return f; },
    [&f](std::tuple<fslp::forest<Ch>, fslp::forest_x<Ch>> const &r) {
      return fcppt::container::join(std::get<0>(r),fslp::apply(std::get<1>(r),f));
    },
    [&f](std::tuple<fslp::forest_x<Ch>, fslp::forest<Ch>> const &r) {
      return fcppt::container::join(fslp::apply(std::get<0>(r),f),std::get<1>(r));
    });
}

}

#endif
