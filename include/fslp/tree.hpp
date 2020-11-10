#ifndef FSLP_TREE_HPP_INCLUDED
#define FSLP_TREE_HPP_INCLUDED

#include <fslp/base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <tuple>
#include <fcppt/config/external_end.hpp>

namespace fslp
{

template <typename Ch>
struct tree
{
  template<typename T, typename F>
  using type = std::tuple<fslp::base<Ch>, F>;
};

}

#endif
