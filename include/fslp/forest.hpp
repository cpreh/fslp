#ifndef FSLP_FOREST_HPP_INCLUDED
#define FSLP_FOREST_HPP_INCLUDED

#include <fslp/tree.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace fslp
{

template <typename Ch>
struct forest
{
  using type = std::vector<fslp::tree<Ch>>;
};

}

#endif
