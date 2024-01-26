#ifndef FSLP_NAV_ROOT_HPP_INCLUDED
#define FSLP_NAV_ROOT_HPP_INCLUDED

#include <fslp/make_nonempty.hpp>
#include <fslp/nav/simple_string_first.hpp>
#include <fslp/nav/spine_alph.hpp>
#include <fslp/nav/string.hpp>
#include <fslp/nav/vert.hpp>
#include <fcppt/unique_ptr.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace fslp::nav
{

template <typename Ch, typename N>
[[nodiscard]] fcppt::optional::object<fslp::nav::vert<Ch, N>> root(std::vector<fslp::nav::spine_alph<Ch, N>> &&_spine)
{
  return fcppt::optional::map(
      fslp::nav::simple_string_first(std::move(_spine)),
      [](fcppt::unique_ptr<fslp::nav::string<fslp::nav::spine_alph<Ch, N>>> &&_nav) {
        return fslp::make_nonempty(std::move(_nav));
      });
}

}

#endif
