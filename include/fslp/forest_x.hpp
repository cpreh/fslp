#ifndef FSLP_FOREST_X_HPP_INCLUDED
#define FSLP_FOREST_X_HPP_INCLUDED

#include <fslp/forest.hpp>
#include <fslp/forest_x_fwd.hpp>
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
  using type = fcppt::variant::object<
      fslp::var,
      std::tuple<fslp::forest<Ch>, fslp::forest_x<Ch>>,
      std::tuple<fslp::forest_x<Ch>, fslp::forest<Ch>>>;
};

}

#endif
