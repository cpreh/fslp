#ifndef FSLP_STRING_ALG_HPP_INCLUDED
#define FSLP_STRING_ALG_HPP_INCLUDED

#include <fslp/base.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/tuple/object.hpp>
#include <fcppt/variant/object.hpp>

namespace fslp
{
template <typename Ch>
struct string_alg
{
  template <typename R>
  using type =
      fcppt::variant::object<fslp::base<fcppt::unit>, fslp::base<Ch>, fcppt::tuple::object<R, R>>;
};

}

#endif
