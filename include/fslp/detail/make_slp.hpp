#ifndef FSLP_DETAIL_MAKE_SLP_HPP_INCLUDED
#define FSLP_DETAIL_MAKE_SLP_HPP_INCLUDED

#include <fcppt/function_impl.hpp>
#include <fcppt/metal/as_tuple.hpp>
#include <fslp/detail/rotations.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
#include <fcppt/config/external_end.hpp>

namespace fslp
{
namespace detail
{

template<typename Ns, template<typename...> class... Cs>
struct make_slp
{
  template<typename N, typename C, typename A>
  using make_type = fcppt::function< metal::apply<C, A>(N) >;

  using func_types = metal::transform<
      metal::lambda<make_type>,
      Ns,
      metal::list<metal::lambda<Cs>...>,
      fslp::detail::rotations<Ns>>;

  using type = fcppt::metal::as_tuple<func_types>;
};

}
}

#endif
