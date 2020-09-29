#include <fcppt/copy.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/recursive.hpp>
#include <fcppt/unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/container/make.hpp>
#include <fcppt/metal/from_number.hpp>
#include <fcppt/metal/interval.hpp>
#include <fcppt/metal/to_number.hpp>
#include <fcppt/optional/make.hpp>
#include <fcppt/optional/make_if.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/type_traits/remove_cv_ref_t.hpp>
#include <fcppt/variant/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
#include <cstddef>
#include <tuple>
#include <utility>
#include <vector>
#include <fcppt/config/external_end.hpp>

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

template <typename L, typename Index>
using rotate_at = metal::join<
    metal::drop<L, fcppt::metal::to_number<Index>>,
    metal::take<L, fcppt::metal::to_number<Index>>>;

template<typename>
struct apply_fix_impl;

template <template <typename...> class... Cs>
struct fix;

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

template <template <typename...> class... Cs>
struct fix
{
  using mkfix = make_fix<Cs...>;
  using rec = typename make_fix<Cs...>::type;

  template<typename U>
  fix(U &&_val) : val_{rec{std::forward<U>(_val)}} {}

  fcppt::recursive<rec> val_;
};

using fslp_fix = fix<forest_alg_f<char>::type,forest_alg_fx<char>::type>;
using fslp_fix_f = fix<forest_alg_fx<char>::type,forest_alg_f<char>::type>;

int main()
{
  fslp_fix e{fcppt::unit{}};
  fslp_fix_f f1{std::make_tuple('a', fcppt::copy(e), fcppt::copy(e))};
  fslp_fix test2{std::make_tuple(fcppt::copy(f1), fcppt::copy(e))};
}
