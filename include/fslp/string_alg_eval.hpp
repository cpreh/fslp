#ifndef FSLP_STRING_ALG_EVAL_HPP_INCLUDED
#define FSLP_STRING_ALG_EVAL_HPP_INCLUDED

#include <fslp/base.hpp>
#include <fslp/string_alg_t.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/container/join.hpp>
#include <fcppt/tuple/get.hpp>
#include <fcppt/tuple/object.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace fslp
{
template <typename Ch>
std::vector<Ch> string_alg_eval(fslp::string_alg_t<Ch, std::vector<Ch>> const &v)
{
  return fcppt::variant::match(
      v,
      [](fslp::base<fcppt::unit>) { return std::vector<Ch>{}; },
      [](fslp::base<Ch> const &x) { return std::vector<Ch>{x.get()}; },
      [](fcppt::tuple::object<std::vector<Ch>, std::vector<Ch>> const &x) {
        return fcppt::container::join(fcppt::tuple::get<0>(x), fcppt::tuple::get<1>(x));
      });
}
}

#endif
