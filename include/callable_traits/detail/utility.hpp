/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_DETAIL_UTILITY_HPP
#define CALLABLE_TRAITS_DETAIL_UTILITY_HPP

#include <callable_traits/detail/sfinae_errors.hpp>
#include <callable_traits/config.hpp>
#include <type_traits>
#include <tuple>
#include <utility>
#include <cstdint>

namespace callable_traits {

    struct invalid_type { invalid_type() = delete; };

    namespace detail {

        // used to convey "this type doesn't matter" in code
        struct dummy {};

        // used as return type in failed SFINAE tests
        struct substitution_failure : std::false_type{};

        template<bool Value>
        using bool_type = std::integral_constant<bool, Value>;

        // shorthand for std::tuple_element
        template<std::size_t I, typename Tup>
        using at = typename std::tuple_element<I, Tup>::type;

        // a faster version of std::decay_t
        template<typename T>
        using shallow_decay = typename std::remove_cv<
            typename std::remove_reference<T>::type
        >::type;

        namespace util_detail {

            template<typename T>
            struct is_reference_wrapper_t {
                using type = std::false_type;
            };

            template<typename T>
            struct is_reference_wrapper_t<std::reference_wrapper<T>> {
                using type = std::true_type;
            };
        }

        template<typename T>
        using is_reference_wrapper =
            typename util_detail::is_reference_wrapper_t<shallow_decay<T>>::type;

        template<typename T, typename Class>
        using add_member_pointer = T Class::*;

        namespace util_detail {
            template<typename T, bool Value>
            struct type_value {
                static constexpr const bool value = Value;

                struct _ {
                    using type = T;
                };
            };
        }

        template<typename T, typename ErrorType>
        using fail_if_invalid = sfinae_try<T,
            fail_if<std::is_same<T, invalid_type>::value, ErrorType>>;

        template<typename T, typename Fallback>
        using fallback_if_invalid = typename std::conditional<
            std::is_same<T, invalid_type>::value,
            Fallback,
            T
        >::type;
    }
}

#endif
