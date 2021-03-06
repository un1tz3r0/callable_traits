/*

@copyright Barrett Adair 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef CALLABLE_TRAITS_ADD_MEMBER_VOLATILE_HPP
#define CALLABLE_TRAITS_ADD_MEMBER_VOLATILE_HPP

#include <callable_traits/detail/core.hpp>

//[ add_member_volatile_hpp
/*`
[section:ref_add_member_volatile add_member_volatile]
[heading Header]
``#include<callable_traits/add_member_volatile.hpp>``
[heading Definition]
*/

namespace callable_traits {

    template<typename T>
    using add_member_volatile_t = //implementation-defined
//<-
        detail::fail_if_invalid<
            typename detail::traits<T>::add_member_volatile,
            member_qualifiers_are_illegal_for_this_type>;
//->

    template<typename T>
    struct add_member_volatile {
        using type = add_member_volatile_t<T>;
    };
}

/*`
[heading Constraints]
* `T` must be a function type or a member function pointer type

[heading Behavior]
* A substitution failure occurs if the constraints are violated.
* Adds a member volatile qualifier to `T`, if not already present.

[heading Input/Output Examples]
[table
    [[`T`]                              [`add_member_volatile_t<T>`]]
    [[`int()`]                          [`int() volatile`]]
    [[`int(foo::*)()`]                  [`int(foo::*)() volatile`]]
    [[`int(foo::*)() &`]                [`int(foo::*)() volatile &`]]
    [[`int(foo::*)() &&`]               [`int(foo::*)() volatile &&`]]
    [[`int(foo::*)() const`]            [`int(foo::*)() const volatile`]]
    [[`int(foo::*)() transaction_safe`] [`int(foo::*)() volatile transaction_safe`]]
    [[`int`]                            [(substitution failure)]]
    [[`int (&)()`]                      [(substitution failure)]]
    [[`int (*)()`]                      [(substitution failure)]]
    [[`int foo::*`]                     [(substitution failure)]]
    [[`int (foo::* const)()`]           [(substitution failure)]]
]

[heading Example Program]
[import ../example/add_member_volatile.cpp]
[add_member_volatile]
[endsect][/section:ref_add_member_volatile]
*/
//]

#endif
