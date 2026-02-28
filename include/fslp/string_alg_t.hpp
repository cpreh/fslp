#ifndef FSLP_STRING_ALG_T_HPP_INCLUDED
#define FSLP_STRING_ALG_T_HPP_INCLUDED

#include <fslp/string_alg.hpp>

namespace fslp
{

template <typename Ch, typename R>
using string_alg_t = fslp::string_alg<Ch>:: template type<R>;

}

#endif
