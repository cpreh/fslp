#ifndef FSLP_MAP_HPP_INCLUDED
#define FSLP_MAP_HPP_INCLUDED

#include <fcppt/unit.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/container/tuple/map.hpp>
#include <fcppt/variant/apply.hpp>
#include <fcppt/variant/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <tuple>
#include <type_traits>
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
auto map(F const &f, std::tuple<Ts...> const &t)
{
  return fcppt::container::tuple::map(t,f);
}

template <typename F, typename... Ts>
auto map(F const &f, fcppt::variant::object<Ts...> const &v)
{
  using result = fcppt::variant::object<decltype(f(std::declval<Ts>()))...>;
  return fcppt::variant::apply([&f](auto const &x) { return result{f(x)}; },v);
}

template <typename F, typename T>
auto map(F const &f, std::vector<T> const &v)
{
  return fcppt::algorithm::map<std::vector<decltype(f(std::declval<T>()))>>(v,f);
}

}

#endif
