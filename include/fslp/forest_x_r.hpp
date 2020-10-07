#ifndef FSLP_FOREST_X_R_HPP_INCLUDED
#define FSLP_FOREST_X_R_HPP_INCLUDED

#include <fslp/var.hpp>
#include <fcppt/variant/object.hpp>

namespace fslp
{
template<typename T>
using forest_x_r = fcppt::variant::object<fslp::var, T>;
}

#endif
