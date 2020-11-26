#ifndef FSLP_STRING_ALG_HPP_INCLUDED
#define FSLP_STRING_ALG_HPP_INCLUDED

#include <fslp/base.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/variant/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <tuple>
#include <fcppt/config/external_end.hpp>

namespace fslp
{
template <typename Ch>
struct string_alg
{
  template <typename R>
  using type = fcppt::variant::object<fslp::base<fcppt::unit>, fslp::base<Ch>, std::tuple<R, R>>;
};

}

#endif
