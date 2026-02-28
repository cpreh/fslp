#ifndef FSLP_MAP_RESULT_HPP_INCLUDED
#define FSLP_MAP_RESULT_HPP_INCLUDED

#include <fslp/base_fwd.hpp>
#include <fslp/nonempty_fwd.hpp>
#include <fcppt/mpl/list/object.hpp>
#include <fcppt/mpl/list/unique.hpp>
#include <fcppt/tuple/map_result.hpp>
#include <fcppt/tuple/object_fwd.hpp>
#include <fcppt/variant/from_list_fwd.hpp>
#include <fcppt/variant/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace fslp
{
namespace detail
{
template<typename F, typename T>
struct map_result
{
  using type = std::invoke_result_t<F,T>;
};

template<typename F, typename T>
using map_result_t = fslp::detail::map_result<F,T>::type;

template<typename F, typename T>
struct map_result<F, fslp::base<T>>
{
  using type = fslp::base<T>;
};

template <typename F, typename... Ts>
struct map_result<F, fcppt::tuple::object<Ts...>>
{
  struct map_inner
  {
    template <typename T>
    fslp::detail::map_result_t<F, T> operator()(T);
  };
  using type = fcppt::tuple::map_result<fcppt::tuple::object<Ts...>,map_inner>;
};

template <typename F, typename... Ts>
struct map_result<F, fcppt::variant::object<Ts...>>
{
  using inner_types = fcppt::mpl::list::object<fslp::detail::map_result_t<F,Ts>...>;
  using type = fcppt::variant::from_list<fcppt::mpl::list::unique<inner_types>>;
};

template <typename F, typename T>
struct map_result<F, std::vector<T>>
{
  using type = std::vector<fslp::detail::map_result_t<F,T>>;
};

template <typename F, typename T>
struct map_result<F, fslp::nonempty<T>>
{
  using type = fslp::nonempty<fslp::detail::map_result_t<F,T>>;
};

}

template <typename F, typename T>
using map_result = fslp::detail::map_result_t<F,T>;
}

#endif
