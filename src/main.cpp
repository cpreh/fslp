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

template <typename T>
class nonempty
{
public:
  explicit nonempty(T &&_v) : c_{fcppt::container::make<std::vector<T>>(std::move(_v))} {}

  [[nodiscard]] T const &back() const { return this->c_.back(); }
  [[nodiscard]] T &back() { return this->c_.back(); }

  [[nodiscard]] fcppt::optional::object<nonempty> pop_back() &&
  {
    return fcppt::optional::make_if(!this->c_.empty(), [this] {
      this->c_.pop_back();
      return std::move(*this);
    });
  }

private:
  std::vector<T> c_;
};

template <typename T>
[[nodiscard]] nonempty<fcppt::type_traits::remove_cv_ref_t<T>> make_nonempty(T &&_value)
{
  return nonempty<fcppt::type_traits::remove_cv_ref_t<T>>{std::forward<T>(_value)};
}

template <typename Ch>
class string_nav
{
public:
  FCPPT_NONMOVABLE(string_nav);

  string_nav() = default;

  virtual ~string_nav() = default;

  [[nodiscard]] virtual Ch cur() const = 0;

  [[nodiscard]] virtual fcppt::optional::object<fcppt::unique_ptr<string_nav<Ch>>> next() && = 0;

  [[nodiscard]] virtual fcppt::optional::object<fcppt::unique_ptr<string_nav<Ch>>> prev() && = 0;
};

template <typename Ch>
class simple_string_nav : public string_nav<Ch>
{
public:
  using pos_type = typename std::vector<Ch>::size_type;

  FCPPT_NONMOVABLE(simple_string_nav);

  simple_string_nav(std::vector<Ch> &&_impl, pos_type _pos) : impl_{_impl}, pos_{_pos} {}

  ~simple_string_nav() override = default;

  [[nodiscard]] Ch cur() const override { return this->impl_[this->pos_]; }

  [[nodiscard]] fcppt::optional::object<fcppt::unique_ptr<string_nav<Ch>>> next() && override
  {
    return fcppt::optional::make_if(this->pos_ < this->impl_.size() - 1U, [this] {
      return fcppt::unique_ptr_to_base<string_nav<Ch>>(
          fcppt::make_unique_ptr<simple_string_nav>(std::move(this->impl_), this->pos_ + 1U));
    });
  }

  [[nodiscard]] fcppt::optional::object<fcppt::unique_ptr<string_nav<Ch>>> prev() && override
  {
    return fcppt::optional::make_if(this->pos_ > 0U, [this] {
      return fcppt::unique_ptr_to_base<string_nav<Ch>>(
          fcppt::make_unique_ptr<simple_string_nav>(std::move(this->impl_), this->pos_ - 1U));
    });
  }
private:
  std::vector<Ch> impl_;
  pos_type pos_;
};

template <typename Ch>
[[nodiscard]] fcppt::optional::object<fcppt::unique_ptr<string_nav<Ch>>>
string_nav_first(std::vector<Ch> &&_string)
{
  return fcppt::optional::make_if(!_string.empty(), [&_string] {
    return fcppt::unique_ptr_to_base<string_nav<Ch>>(
        fcppt::make_unique_ptr<simple_string_nav<Ch>>(std::move(_string), 0U));
  });
}

template <typename Ch, typename N>
using spine_alph = fcppt::variant::object<std::tuple<Ch, N>, std::tuple<Ch, N, N>>;

template <typename Ch, typename N>
using vert_nav = nonempty<fcppt::unique_ptr<string_nav<spine_alph<Ch, N>>>>;

template <typename Ch, typename N>
[[nodiscard]] fcppt::optional::object<vert_nav<Ch, N>> root(std::vector<spine_alph<Ch, N>> &&_spine)
{
  return fcppt::optional::map(
      string_nav_first(std::move(_spine)),
      [](fcppt::unique_ptr<string_nav<spine_alph<Ch, N>>> &&_nav) {
        return make_nonempty(std::move(_nav));
      });
}

template <typename Ch, typename N>
[[nodiscard]] fcppt::optional::object<vert_nav<Ch, N>> up(vert_nav<Ch, N> &&_nav)
{
  return fcppt::optional::maybe(
      _nav.back()->prev(),
      [&_nav] { return std::move(_nav).pop_back(); },
      [&_nav](fcppt::unique_ptr<string_nav<spine_alph<Ch, N>>> &&_new_back) {
        _nav.back() = _new_back;
        return fcppt::optional::make(std::move(_nav));
      });
}

/*
  using N = char;
  using sa = spine_alph<Z, N>;

  std::vector<sa> spine{sa{std::make_tuple('a', 'L', 'R')}, sa{std::make_tuple('b', 'C')}};

  fcppt::optional::object<vert_nav<Z, N>> nav{root(std::move(spine))};
*/


template <typename Ch>
struct string_alg
{
  template <typename R>
  using type = fcppt::variant::object<fcppt::unit, Ch, std::tuple<R, R>>;
};

template <template <typename> class C>
struct fix1
{
  using rec = C<fix1<C>>;
  explicit fix1(rec &&_val) : val_{std::move(_val)} {}

  fcppt::recursive<rec> val_;
};

template <typename Ch>
struct forest_alg_f
{
  template <typename R, typename Rx>
  using type = fcppt::variant::object<fcppt::unit, std::tuple<R, R>, std::tuple<Ch, R>, std::tuple<Rx, R>>;
};

template <typename Ch>
struct forest_alg_fx
{
  template <typename R, typename Rx>
  using type = fcppt::variant::object<std::tuple<Ch, R, R>, std::tuple<Rx, Rx>>;
};

template <template <typename, typename> class C1, template <typename, typename> class C2>
struct fix2
{
  using rec = C1<fix2<C2, C1>, fix2<C1, C2>>;
  explicit fix2(rec &&_val) : val_{std::move(_val)} {}

  fcppt::recursive<rec> val_;
};

template<typename L, typename Index>
using splice = metal::splice<L, fcppt::metal::to_number<Index>, metal::list<>>;

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
      metal::bind<metal::lambda<splice>, metal::always<constructors>, metal::_1>,
      positions>;
  using arguments = metal::transform<metal::lambda<apply_fix>, rotations>;
  using type = metal::apply<metal::lambda<C1>,arguments>;
};

template <template <typename...> class... Cs>
struct fix
{
  using rec = typename make_fix<Cs...>::type;

  explicit fix(rec &&_val) : val_{std::move(_val)} {}

  fcppt::recursive<rec> val_;
};


int main()
{
  using fslp_fix = fix<forest_alg_f<char>::type,forest_alg_fx<char>::type>;
  using fslp_fix_arg = fslp_fix::rec;
  fslp_fix test{fslp_fix_arg{fcppt::unit{}}};
//  test++;
/*
  using Z = char;
  using string_alg_Z = string_alg<Z>;
  using string_alg_fix = fix1<string_alg_Z::type>;
  using string_alg_fix_arg = string_alg_Z::type<string_alg_fix>;

  string_alg_fix test{string_alg_fix_arg{fcppt::unit{}}};

  string_alg_fix test2{string_alg_fix_arg{std::make_tuple(fcppt::copy(test),fcppt::copy(test))}};*/
}
