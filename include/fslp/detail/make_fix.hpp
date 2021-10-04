#ifndef FSLP_DETAIL_MAKE_FIX_HPP_INCLUDED
#define FSLP_DETAIL_MAKE_FIX_HPP_INCLUDED

#include <fslp/fix_fwd.hpp>
#include <fslp/detail/rotations.hpp>
#include <fcppt/mpl/lambda.hpp>
#include <fcppt/mpl/list/apply.hpp>
#include <fcppt/mpl/list/map.hpp>
#include <fcppt/mpl/list/object.hpp>

namespace fslp::detail
{
template <template <typename...> class C1, template <typename...> class... Cs>
struct make_fix
{
  template <typename>
  struct apply_fix_impl;

  template <template <typename...> class... Ts>
  struct apply_fix_impl<fcppt::mpl::list::object<fcppt::mpl::lambda<Ts>...>>
  {
    using type = fix<Ts...>;
  };

  template <typename L>
  using apply_fix = typename apply_fix_impl<L>::type;

  using constructors = fcppt::mpl::list::object<fcppt::mpl::lambda<C1>, fcppt::mpl::lambda<Cs>...>;
  using arguments = fcppt::mpl::list::map<fslp::detail::rotations<constructors>, fcppt::mpl::lambda<apply_fix>>;
  using type = fcppt::mpl::list::apply<fcppt::mpl::lambda<C1>, arguments>;
};

}

#endif
