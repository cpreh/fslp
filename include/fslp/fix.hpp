#ifndef FSLP_FIX_HPP_INCLUDED
#define FSLP_FIX_HPP_INCLUDED

#include <fslp/fix_fwd.hpp>
#include <fslp/detail/make_fix.hpp>
#include <fcppt/recursive.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace fslp
{

template <template <typename...> class... Cs>
class fix
{
public:
  using rec = typename fslp::detail::make_fix<Cs...>::type;

  template <typename U>
  explicit fix(U &&_val)
    requires(std::is_same_v<std::remove_cvref_t<U>, rec>)
      : v{std::forward<U>(_val)}
  {
  }

  [[nodiscard]] rec const &unfix() const { return v.get(); }
private:
  fcppt::recursive<rec> v;
};

template <template <typename...> class... Cs>
[[nodiscard]] inline bool operator==(fslp::fix<Cs...> const &l, fslp::fix<Cs...> const &r)
{
  return l.unfix() == r.unfix();
}
}

#endif
