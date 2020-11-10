#ifndef FSLP_MAP_RESULT_HPP_INCLUDED
#define FSLP_MAP_RESULT_HPP_INCLUDED

#include <fslp/base_fwd.hpp>
#include <fcppt/container/tuple/map_result.hpp>
#include <fcppt/metal/unique.hpp>
#include <fcppt/variant/from_list_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
#include <tuple>
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
using map_result_t = typename fslp::detail::map_result<F,T>::type;

template<typename F, typename T>
struct map_result<F, fslp::base<T>>
{
  using type = fslp::base<T>;
};

template <typename F, typename... Ts>
struct map_result<F, std::tuple<Ts...>>
{
  struct map_inner
  {
    template <typename T>
    fslp::detail::map_result_t<F, T> operator()(T);
  };
  using type = fcppt::container::tuple::map_result<std::tuple<Ts...>,map_inner>;
};

template <typename F, typename... Ts>
struct map_result<F, fcppt::variant::object<Ts...>>
{
  using inner_types = ::metal::list<fslp::detail::map_result_t<F,Ts>...>;
  using type = fcppt::variant::from_list<fcppt::metal::unique<inner_types>>;
};

template <typename F, typename T>
struct map_result<F, std::vector<T>>
{
  using type = std::vector<fslp::detail::map_result_t<F,T>>;
};

}

template <typename F, typename T>
using map_result = fslp::detail::map_result_t<F,T>;
}

#endif
