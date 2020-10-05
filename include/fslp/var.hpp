#ifndef FSLP_VAR_HPP_INCLUDED
#define FSLP_VAR_HPP_INCLUDED

namespace fslp
{

struct var {};

[[nodiscard]] inline bool operator==(fslp::var const &, fslp::var const &) { return true; }
}

#endif
