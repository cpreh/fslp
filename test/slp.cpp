#include <fslp/forest.hpp>
#include <fslp/forest_t.hpp>
#include <fslp/tree.hpp>
#include <fslp/tree_t.hpp>
#include <fslp/slp.hpp>
#include <fcppt/function_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <tuple>
#include <type_traits>
#include <fcppt/config/external_end.hpp>

enum class N1 { A };
enum class N2 { A };

using test_slp = fslp::slp<fslp::forest<char>::type, fslp::tree<char>::type>::type<N1, N2>;

static_assert(std::is_same_v<
              test_slp,
              std::tuple<
                  fcppt::function<fslp::forest_t<char, N1, N2>(N1)>,
                  fcppt::function<fslp::tree_t<char, N2, N1>(N2)>>>);
