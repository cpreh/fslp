#ifndef FSLP_NAV_VERT_HPP_INCLUDED
#define FSLP_NAV_VERT_HPP_INCLUDED

#include <fslp/nonempty.hpp>
#include <fslp/nav/spine_alph.hpp>
#include <fslp/nav/string.hpp>
#include <fcppt/unique_ptr.hpp>

namespace fslp::nav
{
template <typename Ch, typename N>
using vert = fslp::nonempty<fcppt::unique_ptr<fslp::nav::string<fslp::nav::spine_alph<Ch, N>>>>;
}

#endif
