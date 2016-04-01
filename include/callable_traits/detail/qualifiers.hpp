/*!
@file
Defines `flags`

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_DETAIL_QUALIFIERS_HPP
#define CALLABLE_TRAITS_DETAIL_QUALIFIERS_HPP

#include <type_traits>
#include <cstdint>

namespace callable_traits {

    namespace detail {

        //bit flags used to signify cv/ref qualifiers
        using flags = std::uint32_t;

        /*

            | && &  V  C |
        --------------------------------------------
        0   | 0  0  0  0 | default
        1   | 0  0  0  1 | const
        2   | 0  0  1  0 | volatile
        3   | 0  0  1  1 | const volatile
        --------------------------------------------
        4   | 0  1  0  0 | &
        5   | 0  1  0  1 | const &
        6   | 0  1  1  0 | volatile &
        7   | 0  1  1  1 | const volatile &
        --------------------------------------------
        8   | 1  0  0  0 | &&
        9   | 1  0  0  1 | const &&
        10  | 1  0  1  0 | volatile &&
        11  | 1  0  1  1 | const volatile &&

        */

        //! Flag representing the default qualifiers on a type 
        //! or member function overload.
        constexpr flags default_ = 0;

        //! Flag representing a const qualifier on a type or
        //! member function overload.
        constexpr flags const_ = 1;

        //! Flag representing a volatile qualifier on a type
        //! or member function overload.
        constexpr flags volatile_ = 2;

        //! Flag representing an lvalue reference type, or
        //! an lvalue-reference-qualified member function
        //! overload.
        constexpr flags lref_ = 4;

        //! Flag representing an lvalue reference type, or
        //! an rvalue-reference-qualified member function
        //! overload.
        constexpr flags rref_ = 8;

        constexpr flags cv_ = 3;

        template<flags Flags>
        using remove_const = std::integral_constant<flags, Flags & ~const_>;

        template<flags Flags>
        using is_const = std::integral_constant<bool,
            (Flags & const_) != 0
        >;

        template<flags Flags>
        using remove_volatile = std::integral_constant<flags, Flags & ~volatile_>;

        template<typename U, typename T = typename std::remove_reference<U>::type>
        using cv_of = std::integral_constant<flags,
            (std::is_const<T>::value ? const_ : default_)
            | (std::is_volatile<T>::value ? volatile_ : default_)
        >;

        template<typename T, typename ForceRef = std::false_type>
        using ref_of = std::integral_constant<flags,
            std::is_rvalue_reference<T>::value ? rref_
            : (std::is_lvalue_reference<T>::value ? lref_
                : (ForceRef::value ? lref_ : default_))
        >;

        template<typename T>
        struct flag_map {
            static_assert(sizeof(T) < 0,
                "Invalid argument passed to flag_map template.");

            static constexpr flags value = default_;
        };

        template<> struct flag_map<int> { static constexpr flags value = default_; };
        template<> struct flag_map<int &> { static constexpr flags value = lref_; };
        template<> struct flag_map<int &&> { static constexpr flags value = rref_; };
        template<> struct flag_map<int const> { static constexpr flags value = const_; };
        template<> struct flag_map<int const &> { static constexpr flags value = const_ | lref_; };
        template<> struct flag_map<int const &&> { static constexpr flags value = const_ | rref_; };
        template<> struct flag_map<int volatile> { static constexpr flags value = volatile_; };
        template<> struct flag_map<int volatile &> { static constexpr flags value = volatile_ | lref_; };
        template<> struct flag_map<int volatile &&> { static constexpr flags value = volatile_ | rref_; };
        template<> struct flag_map<int const volatile> { static constexpr flags value = const_ | volatile_; };
        template<> struct flag_map<int const volatile &> { static constexpr flags value = const_ | volatile_ | lref_; };
        template<> struct flag_map<int const volatile &&> { static constexpr flags value = const_ | volatile_ | rref_; };

        template<typename T>
        class qualifier_traits {

        protected:

            static constexpr flags cv_flags = cv_of<T>::value;
            static constexpr flags ref_flags = ref_of<T>::value;
            static constexpr flags q_flags = cv_flags | ref_flags;

        public:

            using is_reference_qualified = std::integral_constant<bool, 0 < ref_flags>;
            using is_lvalue_reference_qualified = std::integral_constant<bool, ref_flags == lref_>;
            using is_rvalue_reference_qualified = std::integral_constant<bool, ref_flags == rref_>;
            using is_const_qualified = std::integral_constant<bool, 0 < (cv_flags & const_)>;
            using is_volatile_qualified = std::integral_constant<bool, 0 < (cv_flags & volatile_)>;
            using is_cv_qualified = std::integral_constant<bool, cv_flags == (const_ | volatile_)>;
        };
    }
}
#endif