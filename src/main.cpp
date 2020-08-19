#include <fcppt/nomovable.hpp>
#include <fcppt/unique_ptr.hpp>
#include <fcppt/optional/object.hpp>

template <typename Ch>
struct string_nav
{
  FCPPT_NONMOVABLE(string_nav);

  string_nav() = default;

  ~virtual string_nav() = default;

  [[nodiscard]] virtual Ch cur() const = 0;

  [[nodiscard]] fcppt::optional::object<fcppt::unique_ptr<string_nav<Ch>>> next() const = 0;

  [[nodiscard]] fcppt::optional::object<fcppt::unique_ptr<string_nav<Ch>>> prev() const = 0;
};

int main() {}
