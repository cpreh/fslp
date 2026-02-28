#ifndef FSLP_NAV_SIMPLE_STRING_HPP_INCLUDED
#define FSLP_NAV_SIMPLE_STRING_HPP_INCLUDED

#include <fslp/nav/string.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/optional/make_if.hpp>
#include <fcppt/optional/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace fslp::nav
{
template <typename Ch>
class simple_string : public fslp::nav::string<Ch>
{
public:
  using pos_type = std::vector<Ch>::size_type;

  FCPPT_NONMOVABLE(simple_string);

  simple_string(std::vector<Ch> _impl, pos_type const _pos) : impl_{std::move(_impl)}, pos_{_pos}
  {
  }

  ~simple_string() override = default;

  // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-avoid-unchecked-container-access)
  [[nodiscard]] Ch cur() const override { return this->impl_[this->pos_]; }

  [[nodiscard]] fcppt::optional::object<fcppt::unique_ptr<fslp::nav::string<Ch>>> next() const override
  {
    return fcppt::optional::make_if(this->pos_ < this->impl_.size() - 1U, [this] {
      return fcppt::unique_ptr_to_base<fslp::nav::string<Ch>>(
          fcppt::make_unique_ptr<fslp::nav::simple_string<Ch>>(this->impl_, this->pos_ + 1U));
    });
  }

  [[nodiscard]] fcppt::optional::object<fcppt::unique_ptr<fslp::nav::string<Ch>>> prev() const override
  {
    return fcppt::optional::make_if(this->pos_ > 0U, [this] {
      return fcppt::unique_ptr_to_base<fslp::nav::string<Ch>>(
          fcppt::make_unique_ptr<fslp::nav::simple_string<Ch>>(this->impl_, this->pos_ - 1U));
    });
  }

  [[nodiscard]] fcppt::unique_ptr<fslp::nav::string<Ch>> clone() const override
  {
    return fcppt::unique_ptr_to_base<fslp::nav::string<Ch>>(
        fcppt::make_unique_ptr<fslp::nav::simple_string<Ch>>(
            std::vector<Ch>{this->impl_}, this->pos_));
  }
private:
  std::vector<Ch> impl_;
  pos_type pos_;
};
}

#endif
