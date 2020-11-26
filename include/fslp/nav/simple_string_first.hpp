#ifndef FSLP_NAV_SIMPLE_STRING_FIRST_HPP_INCLUDED
#define FSLP_NAV_SIMPLE_STRING_FIRST_HPP_INCLUDED

#include <fslp/nav/simple_string.hpp>
#include <fslp/nav/string.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/optional/make_if.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace fslp::nav
{
template <typename Ch>
[[nodiscard]] fcppt::optional::object<fcppt::unique_ptr<fslp::nav::string<Ch>>>
simple_string_first(std::vector<Ch> &&_string)
{
  return fcppt::optional::make_if(!_string.empty(), [&_string] {
    return fcppt::unique_ptr_to_base<fslp::nav::string<Ch>>(
        fcppt::make_unique_ptr<fslp::nav::simple_string<Ch>>(std::move(_string), 0U));
  });
}
}

#endif
