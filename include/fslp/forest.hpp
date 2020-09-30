#ifndef FSLP_FOREST_HPP_INCLUDED
#define FSLP_FOREST_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace fslp
{

template <typename Ch>
struct forest
{
  template<typename F, typename T>
  using type = std::vector<T>;
};

}

#endif
