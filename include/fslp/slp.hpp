#ifndef FSLP_SLP_HPP_INCLUDED
#define FSLP_SLP_HPP_INCLUDED

#include <fslp/detail/make_slp.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
#include <fcppt/config/external_end.hpp>

namespace fslp
{

template<template<typename...> class... Cs>
struct slp
{
  template<typename... Ns>
  using type = typename fslp::detail::make_slp<metal::list<Ns...>,Cs...>::type;
};

}

#endif
