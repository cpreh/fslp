#ifndef FSLP_IS_FIX_HPP_INCLUDED
#define FSLP_IS_FIX_HPP_INCLUDED

#include <fslp/fix_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace fslp
{

template <typename>
struct is_fix
:
std::false_type
{};

template <template <typename...> class... Cs>
struct is_fix<fslp::fix<Cs...>>
:
std::true_type
{};

}

#endif
