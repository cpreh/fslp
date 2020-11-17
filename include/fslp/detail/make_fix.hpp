#ifndef FSLP_DETAIL_MAKE_FIX_HPP_INCLUDED
#define FSLP_DETAIL_MAKE_FIX_HPP_INCLUDED

#include <fslp/fix_fwd.hpp>
#include <fslp/detail/rotations.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
#include <fcppt/config/external_end.hpp>

namespace fslp
{
namespace detail
{
template <template <typename...> class C1, template <typename...> class... Cs>
struct make_fix
{
  template <typename>
  struct apply_fix_impl;

  template <template <typename...> class... Ts>
  struct apply_fix_impl<::metal::list<::metal::lambda<Ts>...>>
  {
    using type = fix<Ts...>;
  };

  template <typename L>
  using apply_fix = typename apply_fix_impl<L>::type;

  using constructors = metal::list<metal::lambda<C1>, metal::lambda<Cs>...>;
  using arguments = metal::transform<metal::lambda<apply_fix>, fslp::detail::rotations<constructors>>;
  using type = metal::apply<metal::lambda<C1>, arguments>;
};

}
}

#endif
