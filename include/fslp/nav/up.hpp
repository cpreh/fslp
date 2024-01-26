#ifndef FSLP_NAV_UP_HPP_INCLUDED
#define FSLP_NAV_UP_HPP_INCLUDED

#include <fslp/clone.hpp>
#include <fslp/nav/spine_alph.hpp>
#include <fslp/nav/string.hpp>
#include <fslp/nav/vert.hpp>
#include <fcppt/unique_ptr.hpp>
#include <fcppt/optional/make.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace fslp::nav
{
template <typename Ch, typename N>
[[nodiscard]] fcppt::optional::object<fslp::nav::vert<Ch, N>> up(fslp::nav::vert<Ch, N> const &_nav)
{
  return fcppt::optional::maybe(
      _nav.back()->prev(),
      [&_nav] { return fslp::clone(_nav).pop_back(); },
      [&_nav](fcppt::unique_ptr<fslp::nav::string<fslp::nav::spine_alph<Ch, N>>> &&_new_back) {
        fslp::nav::vert<Ch, N> res{fslp::clone(_nav)};
        res.back() = std::move(_new_back);
        return fcppt::optional::make(std::move(res));
      });
}
}

#endif
