/*<-
Copyright (c) 2016 Barrett Adair

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
->*/

#include <callable_traits/config.hpp>

#ifndef CALLABLE_TRAITS_ENABLE_TRANSACTION_SAFE
int main(){}
#else

//[ is_transaction_safe
#include <callable_traits/is_transaction_safe.hpp>

namespace ct = callable_traits;

struct foo;

static_assert(ct::is_transaction_safe<int() transaction_safe>::value, "");
static_assert(ct::is_transaction_safe<int(*)() transaction_safe>::value, "");
static_assert(ct::is_transaction_safe<int(&)() transaction_safe>::value, "");
static_assert(ct::is_transaction_safe<int(foo::*)() const transaction_safe>::value, "");

static_assert(!ct::is_transaction_safe<int()>::value, "");
static_assert(!ct::is_transaction_safe<int(*)()>::value, "");
static_assert(!ct::is_transaction_safe<int(&)()>::value, "");
static_assert(!ct::is_transaction_safe<int(foo::*)() const>::value, "");

int main() {}
//]
#endif
