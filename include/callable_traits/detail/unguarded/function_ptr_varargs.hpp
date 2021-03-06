/*
Copyright (c) 2016 Modified Work Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

HEADER GUARDS INTENTIONALLY OMITTED
DO NOT INCLUDE THIS HEADER DIRECTLY
*/

#define CALLABLE_TRAITS_INCLUDE_TRANSACTION_SAFE
#define CALLABLE_TRAITS_IS_TRANSACTION_SAFE std::false_type
#include <callable_traits/detail/unguarded/function_ptr_varargs_2.hpp>

#undef CALLABLE_TRAITS_INCLUDE_TRANSACTION_SAFE
#undef CALLABLE_TRAITS_IS_TRANSACTION_SAFE

#ifdef CALLABLE_TRAITS_ENABLE_TRANSACTION_SAFE
#define CALLABLE_TRAITS_IS_TRANSACTION_SAFE std::true_type
#define CALLABLE_TRAITS_INCLUDE_TRANSACTION_SAFE transaction_safe
#include <callable_traits/detail/unguarded/function_ptr_varargs_2.hpp>
#endif

#undef CALLABLE_TRAITS_INCLUDE_TRANSACTION_SAFE
#undef CALLABLE_TRAITS_IS_TRANSACTION_SAFE
