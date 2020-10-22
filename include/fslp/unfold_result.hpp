#ifndef FSLP_UNFOLD_RESULT_HPP_INCLUDED
#define FSLP_UNFOLD_RESULT_HPP_INCLUDED

#include <fslp/fix.hpp>
#include <fslp/map_result.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

namespace fslp
{
namespace detail
{
template<typename T, typename F>
struct unfold_result
{
  using type = T;
};

template<typename F>
struct unfold_inner;

template<template<typename...> class... Cs, typename F>
struct unfold_result<fslp::fix<Cs...>,F>
{
  using fix_t = fslp::fix<Cs...>;

  using mapped = fslp::map_result<fslp::detail::unfold_inner<F>, typename fix_t::rec>;

  using type = std::invoke_result_t<F,mapped>;
};

template<typename F>
struct unfold_inner
{
  template <typename A>
  auto operator()(A const &) -> typename fslp::detail::unfold_result<A, F>::type;
};

}

template<typename T, typename F>
using unfold_result = typename fslp::detail::unfold_result<T,F>::type;

}

#endif
