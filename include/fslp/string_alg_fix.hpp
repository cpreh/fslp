#ifndef FSLP_STRING_ALG_FIX_HPP_INCLUDED
#define FSLP_STRING_ALG_FIX_HPP_INCLUDED

#include <fslp/fix.hpp>
#include <fslp/string_alg.hpp>

namespace fslp
{
template <typename Ch>
using string_alg_fix = fslp::fix<fslp::string_alg<Ch>::template type>;
}

#endif
