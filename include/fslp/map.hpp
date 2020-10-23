#ifndef FSLP_MAP_HPP_INCLUDED
#define FSLP_MAP_HPP_INCLUDED

#include <fslp/map_result.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/container/tuple/map.hpp>
#include <fcppt/variant/apply.hpp>
#include <fcppt/variant/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <tuple>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace fslp
{
template <typename F>
inline fcppt::unit map(F const &, fcppt::unit)
{
  return fcppt::unit{};
}

template <typename F, typename... Ts>
fslp::map_result<F, std::tuple<Ts...>> map(F const &f, std::tuple<Ts...> const &t)
{
  return fcppt::container::tuple::map(t, f);
}

template <typename F, typename... Ts>
fslp::map_result<F, fcppt::variant::object<Ts...>>
map(F const &f, fcppt::variant::object<Ts...> const &v)
{
  using result = fslp::map_result<F, fcppt::variant::object<Ts...>>;
  return fcppt::variant::apply([&f](auto const &x) { return result{f(x)}; }, v);
}

template <typename F, typename T>
fslp::map_result<F, std::vector<T>> map(F const &f, std::vector<T> const &v)
{
  using result = fslp::map_result<F, std::vector<T>>;
  return fcppt::algorithm::map<result>(v, f);
}
}

#endif