#ifndef FSLP_DETAIL_MAKE_SLP_HPP_INCLUDED
#define FSLP_DETAIL_MAKE_SLP_HPP_INCLUDED

#include <fcppt/function_impl.hpp>
#include <fcppt/mpl/lambda.hpp>
#include <fcppt/mpl/list/apply.hpp>
#include <fcppt/mpl/list/as_tuple.hpp>
#include <fcppt/mpl/list/map_multi.hpp>
#include <fcppt/mpl/list/object.hpp>
#include <fslp/detail/rotations.hpp>

namespace fslp::detail
{

template<typename Ns, template<typename...> class... Cs>
struct make_slp
{
  template<typename N, typename C, typename A>
  using make_type = fcppt::function< fcppt::mpl::list::apply<C, A>(N) >;

  using func_types = fcppt::mpl::list::map_multi<
      fcppt::mpl::lambda<make_type>,
      Ns,
      fcppt::mpl::list::object<fcppt::mpl::lambda<Cs>...>,
      fslp::detail::rotations<Ns>>;

  using type = fcppt::mpl::list::as_tuple<func_types>;
};

}

#endif
