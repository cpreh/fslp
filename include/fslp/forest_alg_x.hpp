#ifndef FSLP_FOREST_ALG_X_HPP_INCLUDED
#define FSLP_FOREST_ALG_X_HPP_INCLUDED

#include <fcppt/variant/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <tuple>
#include <fcppt/config/external_end.hpp>

namespace fslp
{

template <typename Ch>
struct forest_alg_x
{
  template <typename Rx, typename R>
  using type = fcppt::variant::object<std::tuple<Ch, R, R>, std::tuple<Rx, Rx>>;
};

}

#endif
