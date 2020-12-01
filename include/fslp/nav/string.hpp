#ifndef FSLP_NAV_STRING_HPP_INCLUDED
#define FSLP_NAV_STRING_HPP_INCLUDED

#include <fcppt/nonmovable.hpp>
#include <fcppt/unique_ptr_fwd.hpp>
#include <fcppt/optional/object_fwd.hpp>

namespace fslp::nav
{
template <typename Ch>
class string
{
public:
  FCPPT_NONMOVABLE(string);

  string() = default;

  virtual ~string() = default;

  [[nodiscard]] virtual Ch cur() const = 0;

  [[nodiscard]] virtual fcppt::optional::object<fcppt::unique_ptr<fslp::nav::string<Ch>>>
  next() const = 0;

  [[nodiscard]] virtual fcppt::optional::object<fcppt::unique_ptr<fslp::nav::string<Ch>>>
  prev() const = 0;

  [[nodiscard]] virtual fcppt::unique_ptr<fslp::nav::string<Ch>> clone() const = 0;
};
}

#endif
