#ifndef FSLP_DETAIL_ROTATIONS_HPP_INCLUDED
#define FSLP_DETAIL_ROTATIONS_HPP_INCLUDED

#include <fcppt/mpl/arg.hpp>
#include <fcppt/mpl/bind.hpp>
#include <fcppt/mpl/constant.hpp>
#include <fcppt/mpl/lambda.hpp>
#include <fcppt/mpl/list/append.hpp>
#include <fcppt/mpl/list/drop.hpp>
#include <fcppt/mpl/list/indices.hpp>
#include <fcppt/mpl/list/map.hpp>
#include <fcppt/mpl/list/take.hpp>

namespace fslp::detail
{

template<typename List>
struct rotations_impl
{
  template <typename L, typename Index>
  using rotate_at =
      fcppt::mpl::list::append<fcppt::mpl::list::drop<L, Index>, fcppt::mpl::list::take<L, Index>>;

  using positions = fcppt::mpl::list::indices<List>;
  using type = fcppt::mpl::list::map<
      positions,
      fcppt::mpl::
          bind<fcppt::mpl::lambda<rotate_at>, fcppt::mpl::constant<List>, fcppt::mpl::arg<1>>>;
};

template<typename List>
using rotations = typename fslp::detail::rotations_impl<List>::type;

}

#endif
