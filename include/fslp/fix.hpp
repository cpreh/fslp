#ifndef FSLP_FIX_HPP_INCLUDED
#define FSLP_FIX_HPP_INCLUDED

#include <fcppt/recursive.hpp>
#include <fcppt/metal/interval.hpp>
#include <fcppt/metal/to_number.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <metal.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace fslp
{

template <template <typename...> class... Cs>
struct fix;

namespace detail
{

template <typename L, typename Index>
using rotate_at = metal::join<
    metal::drop<L, fcppt::metal::to_number<Index>>,
    metal::take<L, fcppt::metal::to_number<Index>>>;

template<typename>
struct apply_fix_impl;

template<template<typename...> class ...Ts>
struct apply_fix_impl<
  ::metal::list<
    ::metal::lambda<
      Ts
    >...
  >
>
{
  using type = fix<Ts...>;
};

template<typename L>
using apply_fix = typename apply_fix_impl<L>::type;

template <template <typename...> class C1, template <typename...> class... Cs>
struct make_fix
{
  using constructors = metal::list<metal::lambda<C1>, metal::lambda<Cs>...>;
  using positions = fcppt::metal::interval<std::size_t, 0U, metal::size<constructors>::value>;
  using rotations = metal::transform<
      metal::bind<metal::lambda<rotate_at>, metal::always<constructors>, metal::_1>,
      positions>;
  using arguments = metal::transform<metal::lambda<apply_fix>, rotations>;
  using type = metal::apply<metal::lambda<C1>, arguments>;
};

}

template <template <typename...> class... Cs>
struct fix
{
  using rec = typename detail::make_fix<Cs...>::type;

  template<typename U>
  fix(U &&_val) : val_{rec{std::forward<U>(_val)}} {}

  fcppt::recursive<rec> val_;
};

}

#endif
