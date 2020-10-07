#ifndef FSLP_FOREST_X_HPP_INCLUDED
#define FSLP_FOREST_X_HPP_INCLUDED

#include <fslp/forest_fix.hpp>
#include <fslp/var.hpp>
#include <fcppt/variant/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <tuple>
#include <fcppt/config/external_end.hpp>

namespace fslp
{
template <typename Ch>
struct forest_x
{
  template <typename F, typename T>
  using type =
      std::tuple<fslp::forest_fix<Ch>, fcppt::variant::object<fslp::var, T>, fslp::forest_fix<Ch>>;
};
}

#endif
