#include <fslp/fix.hpp>
#include <fslp/unfold_result.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace
{
template<typename R>
using rec = std::vector<R>;
}

int main()
{
  using rec_i = rec<int>;
  auto const eval{[](rec_i const &) { return 0; }};

  using rec_fix = fslp::fix<rec>;
  static_assert(std::is_same_v<fslp::unfold_result<rec_fix,decltype(eval)>,int>);
}
