#ifndef FSLP_NAV_SPINE_ALPH_HPP_INCLUDED
#define FSLP_NAV_SPINE_ALPH_HPP_INCLUDED

#include <fcppt/tuple/object.hpp>
#include <fcppt/variant/object.hpp>

namespace fslp::nav
{
template <typename Ch, typename N>
using spine_alph =
    fcppt::variant::object<fcppt::tuple::object<Ch, N>, fcppt::tuple::object<Ch, N, N>>;
}

#endif
