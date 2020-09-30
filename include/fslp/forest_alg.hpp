#ifndef FSLP_FOREST_ALG_HPP_INCLUDED
#define FSLP_FOREST_ALG_HPP_INCLUDED

#include <fcppt/unit.hpp>
#include <fcppt/variant/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <tuple>
#include <fcppt/config/external_end.hpp>

namespace fslp
{

template <typename Ch>
struct forest_alg
{
  template <typename R, typename Rx>
  using type = fcppt::variant::object<fcppt::unit, std::tuple<R,R>, std::tuple<Rx, R>, std::tuple<Ch, R>>;
};

}

#endif
