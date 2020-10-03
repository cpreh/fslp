

#if 0
template <typename Ch>
struct forest_alg_def
{
  auto eval(forest_alg_f_t<Ch, forest_t<Ch>, forest_x_t<Ch>> const &exp)
  {
    return fcppt::variant::match(
        exp,
        [](fcppt::unit) { return forest_t<Ch>{}; },
        [](std::tuple<forest_t<Ch>, forest_t<Ch>> const &r) {
          return fcppt::container::join(std::get<0>(r), std::get<1>(r));
        },
        [](std::tuple<forest_x_t<Ch>, forest_t<Ch>> const &r) {
          return apply(std::get<0>(r), std::get<1>(r));
        },
        [](std::tuple<Ch, forest_t<Ch>> const &r) {
          return forest_t<Ch>{tree_t<Ch>{std::get<0>(r)}};
        });
  }
};
#endif

int main()
{

}
