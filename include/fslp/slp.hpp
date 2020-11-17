#ifndef FSLP_SLP_HPP_INCLUDED
#define FSLP_SLP_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <unordered_map>
#include <tuple>
#include <fcppt/config/external_end.hpp>

namespace fslp
{

template<typename... Ns>
struct slp
{
  // N_1,N_2,C_1,C_2,
  // (N_1 -> C_1<N_1,N_2>, N_2 -> C_2<N_2,N_1>)
  template<template<typename...> class... Cs>
  using type = std::tuple<std::unordered_map<Ns,Cs<Ns...>>...>;
};

}

#endif
