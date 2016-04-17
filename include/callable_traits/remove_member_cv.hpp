/*!
@file

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_remove_member_cv_HPP
#define CALLABLE_TRAITS_remove_member_cv_HPP

#include <callable_traits/detail/required_definitions.hpp>


namespace callable_traits {

    namespace detail {

        template<bool Sfinae>
        struct remove_member_cv_error {

            static_assert(Sfinae,
                "callable_traits::remove_member_cv<T> "
                "is not a meaningful operation for this T.");
        };
    }

    namespace permissive {

        template<typename T>
        using remove_member_cv = detail::fallback_if_invalid<
            typename detail::traits<T>::remove_member_cv,
            T>;
    }

    namespace verbose {

        template<typename T>
        using remove_member_cv = detail::fail_if_invalid<
            typename detail::traits<T>::remove_member_cv,
            detail::remove_member_cv_error<false>>;
    }

    template<typename T>
    using remove_member_cv = detail::fail_if_invalid<
            typename detail::traits<T>::remove_member_cv,
            detail::remove_member_cv_error<true>>;
}

#endif