/*
Copyright Barrett Adair 2016
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http ://boost.org/LICENSE_1_0.txt)
*/

#include <type_traits>
#include <functional>
#include <utility>
#include <callable_traits/is_rvalue_reference_member.hpp>

#ifndef CT_ASSERT
#define CT_ASSERT(...) static_assert(__VA_ARGS__, #__VA_ARGS__)
#endif //CT_ASSERT

#ifdef CALLABLE_TRAITS_DISABLE_REFERENCE_QUALIFIERS
int main(){ return 0; }
#else

struct foo {};

namespace ct = callable_traits;

template<typename T>
void assert_rvalue_qualified() {
    
    CT_ASSERT(ct::is_rvalue_reference_member<T>());
}


template<typename T>
void assert_not_rvalue_qualified() {
    
    CT_ASSERT(!ct::is_rvalue_reference_member<T>());
}

int main() {

    {
        using f   = void(foo::*)();
        using l   = void(foo::*)() &;
        using r   = void(foo::*)() && ;
        using c   = void(foo::*)() const;
        using cl  = void(foo::*)() const &;
        using cr  = void(foo::*)() const &&;
        using v   = void(foo::*)() volatile;
        using vl  = void(foo::*)() volatile &;
        using vr  = void(foo::*)() volatile &&;
        using cv  = void(foo::*)() const volatile;
        using cvl = void(foo::*)() const volatile &;
        using cvr = void(foo::*)() const volatile &&;

        assert_not_rvalue_qualified<f>();
        assert_not_rvalue_qualified<l>();
        assert_rvalue_qualified<r>();
        assert_not_rvalue_qualified<c>();
        assert_not_rvalue_qualified<cl>();
        assert_rvalue_qualified<cr>();
        assert_not_rvalue_qualified<v>();
        assert_not_rvalue_qualified<vl>();
        assert_rvalue_qualified<vr>();
        assert_not_rvalue_qualified<cv>();
        assert_not_rvalue_qualified<cvl>();
        assert_rvalue_qualified<cvr>();
    }

    {
        struct f   { int operator()() { return 0; } };
        struct l   { int operator()() & { return 0; } };
        struct r   { int operator()() && { return 0; } };
        struct c   { int operator()() const { return 0; } };
        struct cl  { int operator()() const & { return 0; } };
        struct cr  { int operator()() const && { return 0; } };
        struct v   { int operator()() volatile { return 0; } };
        struct vl  { int operator()() volatile & { return 0; } };
        struct vr  { int operator()() volatile && { return 0; } };
        struct cv  { int operator()() const volatile { return 0; } };
        struct cvl { int operator()() const volatile & { return 0; } };
        struct cvr { int operator()() const volatile && { return 0; } };

        assert_not_rvalue_qualified<f>();
        assert_not_rvalue_qualified<l>();
        assert_rvalue_qualified<r>();
        assert_not_rvalue_qualified<c>();
        assert_not_rvalue_qualified<cl>();
        assert_rvalue_qualified<cr>();
        assert_not_rvalue_qualified<v>();
        assert_not_rvalue_qualified<vl>();
        assert_rvalue_qualified<vr>();
        assert_not_rvalue_qualified<cv>();
        assert_not_rvalue_qualified<cvl>();
        assert_rvalue_qualified<cvr>();
    }

    {
        using f   = void();
        using l   = void() &;
        using r   = void() && ;
        using c   = void() const;
        using cl  = void() const &;
        using cr  = void() const &&;
        using v   = void() volatile;
        using vl  = void() volatile &;
        using vr  = void() volatile &&;
        using cv  = void() const volatile;
        using cvl = void() const volatile &;
        using cvr = void() const volatile &&;

        CT_ASSERT(!ct::is_rvalue_reference_member<f>());
        CT_ASSERT(!ct::is_rvalue_reference_member<l>());
        CT_ASSERT(ct::is_rvalue_reference_member<r>());
        CT_ASSERT(!ct::is_rvalue_reference_member<c>());
        CT_ASSERT(!ct::is_rvalue_reference_member<cl>());
        CT_ASSERT(ct::is_rvalue_reference_member<cr>());
        CT_ASSERT(!ct::is_rvalue_reference_member<v>());
        CT_ASSERT(!ct::is_rvalue_reference_member<vl>());
        CT_ASSERT(ct::is_rvalue_reference_member<vr>());
        CT_ASSERT(!ct::is_rvalue_reference_member<cv>());
        CT_ASSERT(!ct::is_rvalue_reference_member<cvl>());
        CT_ASSERT(ct::is_rvalue_reference_member<cvr>());
    }

    using f_ptr = void(*)();
    assert_not_rvalue_qualified<f_ptr>();
    assert_not_rvalue_qualified<f_ptr foo::*>();
    assert_not_rvalue_qualified<int foo::*>();
    assert_not_rvalue_qualified<void(&)()>();
}

#endif //#ifdef CALLABLE_TRAITS_DISABLE_REFERENCE_QUALIFIERS
