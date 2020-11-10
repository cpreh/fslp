#ifndef FSLP_UNFOLD_HPP_INCLUDED
#define FSLP_UNFOLD_HPP_INCLUDED

#include <fslp/fix.hpp>
#include <fslp/is_fix.hpp>
#include <fslp/map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace fslp
{
namespace detail
{

template<typename... Rs, typename T, typename F, typename = std::enable_if_t<!fslp::is_fix<T>::value>>
T unfold(T t, F const &)
{
  return t;
}

template <typename R, typename... Rs, template <typename...> class... Cs, typename F>
R unfold(fslp::fix<Cs...> const &x, F const &f)
{
  return f(fslp::map([&f](auto const &i) { return fslp::detail::unfold<Rs...,R>(i, f); }, x.unfix()));
}

}

template <typename R, typename... Rs, template <typename...> class... Cs, typename F>
R unfold(fslp::fix<Cs...> const &x, F const &f)
{
  return fslp::detail::unfold<R,Rs...>(x,f);
}

}

#endif
