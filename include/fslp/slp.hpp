#ifndef FSLP_SLP_HPP_INCLUDED
#define FSLP_SLP_HPP_INCLUDED

#include <fcppt/container/tuple/map.hpp>
#include <fcppt/variant/apply.hpp>
#include <fcppt/variant/object.hpp>
#include <unordered_map>
#include <tuple>

namespace fslp
{

template<typename... Ns>
struct slp
{
  template<template<typename...> class... Cs>
  using type = std::tuple<std::unordered_map<Ns,Cs<Ns...>>...>;
};

}

#if 0
template<typename... Ns, template<typename...> class... Cs, typename T>
auto unfold(typename slp<Ns>:: template type<Cs...> const &_slp, T const &_val)
{
  return map([](auto const &_inner) { return unfold(_slp, _val
}

enum class N
{
  A,
  B
};

enum class NX
{
  C,
  D
};

using rhs_0_map = std::unordered_map<N,forest_alg_f<char>::type<N,NX>>;
rhs_0_map rhs_0{rhs_0_map::value_type{N::A, forest_alg_f<char>::type<N,NX>{fcppt::unit{}}}};

using slp2 = slp<N,NX>::type<forest_alg_f<char>::type,forest_alg_fx<char>::type>;
slp2 map{rhs_0,{}};
#endif
