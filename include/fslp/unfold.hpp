#ifndef FSLP_UNFOLD_HPP_INCLUDED
#define FSLP_UNFOLD_HPP_INCLUDED

#include <fslp/fix.hpp>

namespace fslp
{

template<template<typename...>... Cs, typename... F>
auto unfold(fslp::fix<Cs...> const &x, F const &...f)
{
  return fslp::unfold(f...(x.get()));
}

}

#endif
