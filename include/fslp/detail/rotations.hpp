#ifndef FSLP_DETAIL_ROTATIONS_HPP_INCLUDED
#define FSLP_DETAIL_ROTATIONS_HPP_INCLUDED

#include <fcppt/metal/interval.hpp>
#include <fcppt/metal/to_number.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
#include <fcppt/config/external_end.hpp>

namespace fslp
{
namespace detail
{

template<typename List>
struct rotations_impl
{
  template <typename L, typename Index>
  using rotate_at = metal::join<
      metal::drop<L, fcppt::metal::to_number<Index>>,
      metal::take<L, fcppt::metal::to_number<Index>>>;

  using positions = fcppt::metal::interval<std::size_t, 0U, metal::size<List>::value>;
  using type = metal::transform<metal::bind<metal::lambda<rotate_at>,metal::always<List>,metal::_1>,positions>;
};

template<typename List>
using rotations = typename fslp::detail::rotations_impl<List>::type;

}
}

#endif
