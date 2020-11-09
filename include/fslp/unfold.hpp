#ifndef FSLP_UNFOLD_HPP_INCLUDED
#define FSLP_UNFOLD_HPP_INCLUDED

#include <fslp/fix.hpp>
#include <fslp/map.hpp>

namespace fslp
{

namespace detail
{

template<typename... Rs, typename T, typename F>
T unfold(T const &t, F const &)
{
  return t;
}

template <typename R, typename... Rs, template <typename...> class... Cs, typename F>
R unfold(fslp::fix<Cs...> const &x, F const &f)
{
  return f(fslp::map([&f](auto const &i) { return fslp::detail::unfold<Rs..., R>(i, f); }, x.unfix()));
}

}

template <typename R, typename... Rs, template <typename...> class... Cs, typename F>
R unfold(fslp::fix<Cs...> const &x, F const &f)
{
  return fslp::detail::unfold<R,Rs...>(x,f);
}

}

#endif
