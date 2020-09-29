#include <fcppt/copy.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/variant/object.hpp>
#include <fslp/fix.hpp>
#include <fcppt/config/external_begin.hpp>
#include <tuple>
#include <fcppt/config/external_end.hpp>

#include <fcppt/container/tuple/map.hpp>
#include <fcppt/variant/apply.hpp>
#include <fcppt/variant/object.hpp>
#include <unordered_map>
#include <tuple>

template <typename Ch>
struct forest_alg_f
{
  template <typename R, typename Rx>
  using type = fcppt::variant::object<fcppt::unit, std::tuple<R,R>, std::tuple<Rx, R>, std::tuple<Ch, R>>;
};

template <typename Ch>
struct forest_alg_fx
{
  template <typename Rx, typename R>
  using type = fcppt::variant::object<std::tuple<Ch, R, R>, std::tuple<Rx, Rx>>;
};

using fslp_fix = fslp::fix<forest_alg_f<char>::type,forest_alg_fx<char>::type>;
using fslp_fix_f = fslp::fix<forest_alg_fx<char>::type,forest_alg_f<char>::type>;

template<typename N1, typename N2>
struct slp2
{
  template<template<typename,typename> class C1, template<typename,typename> class C2>
  using type = std::tuple<std::unordered_map<N1,C1<N1,N2>>, std::unordered_map<N2,C2<N1,N2>>>;
};

template<
    typename N1,
    typename N2,
    template <typename, typename>
    class C1,
    template <typename, typename>
    class C2,
    typename... Ts
>
auto unfold(
  typename slp2<N1, N2>::template type<C1, C2> const &_slp,
  std::tuple<Ts...> const &_arg)
{
  return fcppt::container::tuple::map(_arg,[&_slp](auto const &_inner) { return unfold(_slp,_inner); });
}

template<
    typename N1,
    typename N2,
    template <typename, typename>
    class C1,
    template <typename, typename>
    class C2,
    typename... Ts
>
auto unfold(
  typename slp2<N1, N2>::template type<C1, C2> const &_slp,
  fcppt::variant::object<Ts...> const &_arg)
{
  return fcppt::variant::apply(_arg,[&_slp](auto const &_inner) { return unfold(_slp,_inner); });
}

template <
    typename N1,
    typename N2,
    template <typename, typename>
    class C1,
    template <typename, typename>
    class C2>
auto unfold(
    fslp::fix<C1, C2> const &_expr, typename slp2<N1, N2>::template type<C1, C2> const &_slp)
{
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

int main()
{
  fslp_fix e{fcppt::unit{}};
  fslp_fix_f f1{std::make_tuple('a', fcppt::copy(e), fcppt::copy(e))};
  fslp_fix test2{std::make_tuple(fcppt::copy(f1), fcppt::copy(e))};

  using rhs_0_map = std::unordered_map<N,forest_alg_f<char>::type<N,NX>>;
  rhs_0_map rhs_0{rhs_0_map::value_type{N::A, forest_alg_f<char>::type<N,NX>{fcppt::unit{}}}};

  slp2<N,NX>::type<forest_alg_f<char>::type,forest_alg_fx<char>::type> slp{rhs_0,{}};

}
