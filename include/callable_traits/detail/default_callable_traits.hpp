/*
Copyright Barrett Adair 2016

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_DETAIL_DEFAULT_CALLABLE_TRAITS_HPP
#define CALLABLE_TRAITS_DETAIL_DEFAULT_CALLABLE_TRAITS_HPP

#include <callable_traits/detail/utility.hpp>

namespace callable_traits {
    
    namespace detail {
            
        template<typename T = void>
        struct default_callable_traits {
            
            // value is used by all traits classes to participate 
            // in the <callable_traits/detail/traits.hpp> disjunction.
            static constexpr bool value = false;
            
            // used facilitate the disjunction in
            // <callable_traits/detail/traits.hpp>
            using traits = default_callable_traits;
            
            // represents the type under consideration
            using type = invalid_type;
            
            // std::true_type for PMFs and PMDs
            using is_member_pointer = std::false_type;
            
            // std::true_type for PMFs
            using is_member_function_pointer = std::false_type;
            
            // Internally, CallableTraits assumes that all classes
            // are function objects. Therefore, is_function_object
            // is always std::true_type for classes.
            using is_function_object = std::false_type;
            
            // std::true_type when it's a function object, AND
            // we can't take the address of operator() without casting
            using is_overloaded_function_object = std::false_type;

            // std::true_type for function references
            using is_function_reference = std::false_type;
            
            // std::true_type for function pointers
            using is_function_pointer = std::false_type;
            
            // std::true_type for plain function types only
            using is_function = std::false_type;
            
            // std::true_type for callables with C-style variadics
            using has_varargs = std::false_type;
            
            using return_type = invalid_type;
            
            // arg_types is a std::tuple of argument types for
            // callables that are not overloaded/templated function objects.
            // arg_types IS defined in terms of INVOKE, which means
            // a PMF's arg_types tuple will use a reference to its
            // parent class as the first argument, with qualifiers added to
            // match the PMF's own qualifiers.
            using arg_types = invalid_type;
            
            // used in pmf to offer a non-invoke std::tuple<Args...> to derived
            // the function_object type
            using non_invoke_arg_types = invalid_type;

            // An "approximation" of a callable type, in the form
            // of a plain function type. Defined in terms of INVOKE.
            // An identity alias for qualified/unqualified plain function
            // types.
            using function_type = invalid_type;
            
            // Used to smoothen the edges between PMFs and function objects
            using function_object_signature = invalid_type;

            // An identity alias for qualified/unqualified plain function
            // types. Equivalent to remove_member_pointer for PMFs. Same
            // as function_type for other callable types.
            using qualified_function_type = invalid_type;
            
            // Removes C-style variadics from a signature, if present.
            // Aliases invalid_type for function objects and PMDs.
            using remove_varargs = invalid_type;
            
            // Adds C-style variadics to a signature. Aliases
            // invalid_type for function objects and PMDs.
            using add_varargs = invalid_type;
            
            // std::true_type when the signature includes transaction_safe, when
            // the feature is available
            using is_transaction_safe = std::false_type;

            // adds transaction_safe to a signature if the feature is available
            using add_transaction_safe = invalid_type;

            // removes transaction_safe from a signature if present
            using remove_transaction_safe = invalid_type;

            // The class of a PMD or PMF. invalid_type for other types
            using class_type = invalid_type;
            
            // The qualified reference type of class_type. invalid_type
            // for non-member-pointers.
            using invoke_type = invalid_type;
            
            // Removes reference qualifiers from a signature.
            using remove_reference = invalid_type;
            
            // Adds an lvalue qualifier to a signature, in arbitrary
            // accordance with C++11 reference collapsing rules.
            using add_member_lvalue_reference = invalid_type;
            
            // Adds an rvalue qualifier to a signature, in arbitrary
            // accordance with C++11 reference collapsing rules.
            using add_member_rvalue_reference = invalid_type;
            
            // Adds a const qualifier to a signature.
            using add_member_const = invalid_type;
            
            // Adds a volatile qualifier to a signature.
            using add_member_volatile = invalid_type;
            
            // Adds both const and volatile qualifiers to a signature.
            using add_member_cv = invalid_type;
            
            // Removes a const qualifier from a signature, if present.
            using remove_member_const = invalid_type;
            
            // Removes a volatile qualifier from a signature, if present.
            using remove_member_volatile = invalid_type;
            
            // Removes both const and volatile qualifiers from a
            // signature, if any.
            using remove_member_cv = invalid_type;
            
            // Removes the member pointer from PMDs and PMFs. An identity
            // alias for other callable types.
            using remove_member_pointer = invalid_type;
            
            // Changes the parent class type for PMDs and PMFs. Turns
            // function pointers, function references, and
            // qualified/unqualified function types into PMFs. Turns
            // everything else into member data pointers.
            template<typename C,
                typename U = T,
                typename K = typename std::remove_reference<U>::type,
                typename L = typename std::conditional<
                    std::is_same<void, K>::value, invalid_type, K>::type,
                typename Class = typename std::conditional<
                    std::is_class<C>::value, C, invalid_type>::type>
            using apply_member_pointer = typename std::conditional<
                std::is_same<L, invalid_type>::value || std::is_same<Class, invalid_type>::value,
                invalid_type, L Class::*>::type;
            
            // Changes the return type of PMFs, function pointers, function
            // references, and qualified/unqualified function types. Changes
            // the data type of PMDs. invalid_type for function objects.
            template<typename>
            using apply_return = invalid_type;

            // Expands the argument types into a template
            template<template<class...> class Container>
            using expand_args = invalid_type;

            template<template<class...> class Container, typename... RightArgs>
            using expand_args_left = invalid_type;

            template<template<class...> class Container, typename... LeftArgs>
            using expand_args_right = invalid_type;

            using clear_args = invalid_type;
            
            template<typename... NewArgs>
            using push_front = invalid_type;

            template<typename... NewArgs>
            using push_back = invalid_type;
            
            template<std::size_t ElementCount>
            using pop_front = invalid_type;

            template<std::size_t ElementCount>
            using pop_back = invalid_type;
            
            template<std::size_t Index, typename... NewArgs>
            using insert_args = invalid_type;

            template<std::size_t Index, std::size_t Count>
            using remove_args = invalid_type;

            template<std::size_t Index, typename... NewArgs>
            using replace_args = invalid_type;
        };
    }
}

#endif // CALLABLE_TRAITS_DETAIL_DEFAULT_CALLABLE_TRAITS_HPP

