#ifndef FSLP_NAV_SPINE_ALPH_HPP_INCLUDED
#define FSLP_NAV_SPINE_ALPH_HPP_INCLUDED

#include <fcppt/variant/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <tuple>
#include <fcppt/config/external_end.hpp>

namespace fslp::nav
{
template <typename Ch, typename N>
using spine_alph = fcppt::variant::object<std::tuple<Ch, N>, std::tuple<Ch, N, N>>;
}

#endif
