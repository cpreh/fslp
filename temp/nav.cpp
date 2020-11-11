template <typename T>
class nonempty
{
public:
  explicit nonempty(T &&_v) : c_{fcppt::container::make<std::vector<T>>(std::move(_v))} {}

  [[nodiscard]] T const &back() const { return this->c_.back(); }
  [[nodiscard]] T &back() { return this->c_.back(); }

  [[nodiscard]] fcppt::optional::object<nonempty> pop_back() &&
  {
    return fcppt::optional::make_if(!this->c_.empty(), [this] {
      this->c_.pop_back();
      return std::move(*this);
    });
  }

private:
  std::vector<T> c_;
};

template <typename T>
[[nodiscard]] nonempty<fcppt::type_traits::remove_cv_ref_t<T>> make_nonempty(T &&_value)
{
  return nonempty<fcppt::type_traits::remove_cv_ref_t<T>>{std::forward<T>(_value)};
}

template <typename Ch>
class string_nav
{
public:
  FCPPT_NONMOVABLE(string_nav);

  string_nav() = default;

  virtual ~string_nav() = default;

  [[nodiscard]] virtual Ch cur() const = 0;

  [[nodiscard]] virtual fcppt::optional::object<fcppt::unique_ptr<string_nav<Ch>>> next() && = 0;

  [[nodiscard]] virtual fcppt::optional::object<fcppt::unique_ptr<string_nav<Ch>>> prev() && = 0;
};

template <typename Ch>
class simple_string_nav : public string_nav<Ch>
{
public:
  using pos_type = typename std::vector<Ch>::size_type;

  FCPPT_NONMOVABLE(simple_string_nav);

  simple_string_nav(std::vector<Ch> &&_impl, pos_type _pos) : impl_{_impl}, pos_{_pos} {}

  ~simple_string_nav() override = default;

  [[nodiscard]] Ch cur() const override { return this->impl_[this->pos_]; }

  [[nodiscard]] fcppt::optional::object<fcppt::unique_ptr<string_nav<Ch>>> next() && override
  {
    return fcppt::optional::make_if(this->pos_ < this->impl_.size() - 1U, [this] {
      return fcppt::unique_ptr_to_base<string_nav<Ch>>(
          fcppt::make_unique_ptr<simple_string_nav>(std::move(this->impl_), this->pos_ + 1U));
    });
  }

  [[nodiscard]] fcppt::optional::object<fcppt::unique_ptr<string_nav<Ch>>> prev() && override
  {
    return fcppt::optional::make_if(this->pos_ > 0U, [this] {
      return fcppt::unique_ptr_to_base<string_nav<Ch>>(
          fcppt::make_unique_ptr<simple_string_nav>(std::move(this->impl_), this->pos_ - 1U));
    });
  }
private:
  std::vector<Ch> impl_;
  pos_type pos_;
};

template <typename Ch>
[[nodiscard]] fcppt::optional::object<fcppt::unique_ptr<string_nav<Ch>>>
string_nav_first(std::vector<Ch> &&_string)
{
  return fcppt::optional::make_if(!_string.empty(), [&_string] {
    return fcppt::unique_ptr_to_base<string_nav<Ch>>(
        fcppt::make_unique_ptr<simple_string_nav<Ch>>(std::move(_string), 0U));
  });
}

template <typename Ch, typename N>
using spine_alph = fcppt::variant::object<std::tuple<Ch, N>, std::tuple<Ch, N, N>>;

template <typename Ch, typename N>
using vert_nav = nonempty<fcppt::unique_ptr<string_nav<spine_alph<Ch, N>>>>;

template <typename Ch, typename N>
[[nodiscard]] fcppt::optional::object<vert_nav<Ch, N>> root(std::vector<spine_alph<Ch, N>> &&_spine)
{
  return fcppt::optional::map(
      string_nav_first(std::move(_spine)),
      [](fcppt::unique_ptr<string_nav<spine_alph<Ch, N>>> &&_nav) {
        return make_nonempty(std::move(_nav));
      });
}

template <typename Ch, typename N>
[[nodiscard]] fcppt::optional::object<vert_nav<Ch, N>> up(vert_nav<Ch, N> &&_nav)
{
  return fcppt::optional::maybe(
      _nav.back()->prev(),
      [&_nav] { return std::move(_nav).pop_back(); },
      [&_nav](fcppt::unique_ptr<string_nav<spine_alph<Ch, N>>> &&_new_back) {
        _nav.back() = _new_back;
        return fcppt::optional::make(std::move(_nav));
      });
}

/*
  using N = char;
  using sa = spine_alph<Z, N>;

  std::vector<sa> spine{sa{std::make_tuple('a', 'L', 'R')}, sa{std::make_tuple('b', 'C')}};

  fcppt::optional::object<vert_nav<Z, N>> nav{root(std::move(spine))};
*/



