#ifndef FSLP_SLP_HPP_INCLUDED
#define FSLP_SLP_HPP_INCLUDED

#include <fslp/detail/make_slp.hpp>
#include <fcppt/mpl/list/object.hpp>

namespace fslp
{

template<template<typename...> class... Cs>
struct slp
{
  template<typename... Ns>
  using type = typename fslp::detail::make_slp<fcppt::mpl::list::object<Ns...>,Cs...>::type;
};

}

#endif
