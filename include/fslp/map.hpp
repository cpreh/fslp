#ifndef FSLP_MAP_HPP_INCLUDED
#define FSLP_MAP_HPP_INCLUDED

#include <fslp/base_fwd.hpp>
#include <fslp/map_result.hpp>
#include <fslp/nonempty.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/tuple/map.hpp>
#include <fcppt/tuple/object.hpp>
#include <fcppt/variant/apply.hpp>
#include <fcppt/variant/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace fslp
{
template <typename F, typename T>
inline fslp::map_result<F, T> map(F const &f, T const &t)
{
  return f(t);
}

template <typename F, typename T>
inline fslp::map_result<F, fslp::base<T>> map(F const &, fslp::base<T> t)
{
  return t;
}

template <typename F, typename T>
fslp::map_result<F, std::vector<T>> map(F const &, std::vector<T> const &);

template <typename F, typename... Ts>
fslp::map_result<F, fcppt::tuple::object<Ts...>>
map(F const &, fcppt::tuple::object<Ts...> const &);

template <typename F, typename... Ts>
fslp::map_result<F, fcppt::variant::object<Ts...>>
map(F const &f, fcppt::variant::object<Ts...> const &v)
{
  using result = fslp::map_result<F, fcppt::variant::object<Ts...>>;
  return fcppt::variant::apply([&f](auto const &x) { return result{fslp::map(f,x)}; }, v);
}

template <typename F, typename T>
fslp::map_result<F, std::vector<T>> map(F const &f, std::vector<T> const &v)
{
  using result = fslp::map_result<F, std::vector<T>>;
  return fcppt::algorithm::map<result>(v, [&](auto const &i) { return fslp::map(f,i); });
}

template <typename F, typename T>
fslp::map_result<F, fslp::nonempty<T>> map(F const &f, fslp::nonempty<T> const &v)
{
  using result = fslp::map_result<F,fslp::nonempty<T>>;
  return result{fslp::map(f,v.front()), fslp::map(f,v.back())};
}

template <typename F, typename... Ts>
fslp::map_result<F, fcppt::tuple::object<Ts...>>
map(F const &f, fcppt::tuple::object<Ts...> const &t)
{
  return fcppt::tuple::map(t, [&f](auto const &i) { return fslp::map(f, i); });
}
}

#endif
