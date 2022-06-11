#ifndef FSLP_NONEMPTY_CATCH_HPP_INCLUDED
#define FSLP_NONEMPTY_CATCH_HPP_INCLUDED

#include <fslp/nonempty.hpp>
#include <fcppt/catch/convert.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch_tostring.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace Catch
{
template<typename T>
struct StringMaker<fslp::nonempty<T>>
{
  static std::string convert(fslp::nonempty<T> const &v)
  {
    return "(" + fcppt::catch_::convert(v.front()) + "," + fcppt::catch_::convert(v.back()) + ")";
  }
};
}

#endif
