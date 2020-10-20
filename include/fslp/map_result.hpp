#ifndef FSLP_MAP_RESULT_HPP_INCLUDED
#define FSLP_MAP_RESULT_HPP_INCLUDED

#include <fcppt/unit.hpp>
#include <fcppt/container/tuple/map_result.hpp>
#include <fcppt/variant/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <tuple>
#include <type_traits>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace fslp
{
namespace detail
{
template<typename F, typename T>
struct map_result;

template <typename F>
struct map_result<F, fcppt::unit>
{
  using type = fcppt::unit;
};

template <typename F, typename... Ts>
struct map_result<F, std::tuple<Ts...>>
{
  using type = fcppt::container::tuple::map_result<std::tuple<Ts...>,F>;
};

template <typename F, typename... Ts>
struct map_result<F, fcppt::variant::object<Ts...>>
{
  using type = fcppt::variant::object<std::invoke_result_t<F,Ts>...>;
};

template <typename F, typename T>
struct map_result<F, std::vector<T>>
{
  using type = std::vector<std::invoke_result_t<F,T>>;
};

}

template <typename F, typename T>
using map_result = typename fslp::detail::map_result<F,T>::type;
}

#endif
