#ifndef FSLP_IS_CV_FIX_HPP_INCLUDED
#define FSLP_IS_CV_FIX_HPP_INCLUDED

#include <fslp/is_fix.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace fslp
{
template <typename T>
using is_cv_fix = fslp::is_fix<fcppt::type_traits::remove_cv_ref_t<T>>;
}

#endif
