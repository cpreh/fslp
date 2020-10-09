#ifndef FSLP_UNFOLD_HPP_INCLUDED
#define FSLP_UNFOLD_HPP_INCLUDED

#include <fslp/fix.hpp>

namespace fslp
{

/*
template<template<typename...>... Cs, typename... F>
auto unfold(fslp::fix<Cs...> const &x, F const &...f)
{
  return fslp::unfold(f...(x.get()));
}*/
template<typename<typename,typename> C1, template<typename,typename> C2, typename F1, typename F2>
auto unfold(fslp::fix<C1,C2> const &x, F1 const &f1, F2 const &f2)
{
  return fslp::unfold(f2(f1(x.unfix())));
}

}

#endif
