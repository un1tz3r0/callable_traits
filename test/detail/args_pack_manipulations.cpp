#include <tuple>
#include <utility>
#include <type_traits>
#include <callable_traits/config.hpp>
#include <callable_traits/detail/sfinae_errors.hpp>

#ifndef CT_ASSERT
#define CT_ASSERT(...) static_assert(__VA_ARGS__, #__VA_ARGS__)
#endif //CT_ASSERT

namespace callable_traits {

    namespace detail {

        template<typename... Ts>
        struct pack {

#define CALLABLE_TRAITS_BEGIN_PACK_MANIP void(
#define CALLABLE_TRAITS_ARGS_PACK Ts
#define CALLABLE_TRAITS_END_PACK_MANIP , ... )
#include <callable_traits/detail/unguarded/args_pack_manipulations.hpp>

        };
    }
}


using namespace callable_traits::detail;
template<int I>
struct N {};

int main() {

    {
        using p = pack<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test = typename p::template insert_args<0, int, char>;
        using expect = void(int, char, N<0>, N<1>, N<2>, N<3>, N<4>, ...);
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using p = pack<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test = typename p::template insert_args<1, int, char>;
        using expect = void(N<0>, int, char, N<1>, N<2>, N<3>, N<4>, ...);
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using p = pack<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test = typename p::template insert_args<2, int, char>;
        using expect = void(N<0>, N<1>, int, char, N<2>, N<3>, N<4>, ...);
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using p = pack<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test = typename p::template insert_args<3, int, char>;
        using expect = void(N<0>, N<1>, N<2>, int, char, N<3>, N<4>, ...);
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using p = pack<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test = typename p::template insert_args<4, int, char>;
        using expect = void(N<0>, N<1>, N<2>, N<3>, int, char,  N<4>, ...);
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using p = pack<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test = typename p::template insert_args<5, int, char>;
        using expect = void(N<0>, N<1>, N<2>, N<3>, N<4>, int, char, ...);
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using p = pack<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test = typename p::template remove_args<0>;
        using expect = void(N<1>, N<2>, N<3>, N<4>, ...);
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using p = pack<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test = typename p::template remove_args<1>;
        using expect = void(N<0>, N<2>, N<3>, N<4>, ...);
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using p = pack<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test = typename p::template remove_args<2>;
        using expect = void(N<0>, N<1>, N<3>, N<4>, ...);
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using p = pack<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test = typename p::template remove_args<3>;
        using expect = void(N<0>, N<1>, N<2>, N<4>, ...);
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using p = pack<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test = typename p::template remove_args<4>;
        using expect = void(N<0>, N<1>, N<2>, N<3>, ...);
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using p = pack<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test = typename p::template remove_args<0, 5>;
        using expect = void(...);
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using p = pack<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test = typename p::template remove_args<0, 3>;
        using expect = void(N<3>, N<4>, ...);
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using p = pack<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test = typename p::template remove_args<3, 2>;
        using expect = void(N<0>, N<1>, N<2>, ...);
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using p = pack<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test = typename p::template remove_args<4, 1>;
        using expect = void(N<0>, N<1>, N<2>, N<3>, ...);
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using p = pack<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test = typename p::template replace_args<0, int, char>;
        using expect = void(int, char, N<2>, N<3>, N<4>, ...);
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using p = pack<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test = typename p::template replace_args<1, int, char>;
        using expect = void(N<0>, int, char, N<3>, N<4>, ...);
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using p = pack<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test = typename p::template replace_args<2, int, char>;
        using expect = void(N<0>, N<1>, int, char, N<4>, ...);
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using p = pack<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test = typename p::template replace_args<3, int, char>;
        using expect = void(N<0>, N<1>, N<2>, int, char, ...);
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using p = pack<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test = typename p::template replace_args<4, int, char, short, void*>;
        using expect = void(N<0>, N<1>, N<2>, N<3>, int, char, short, void*, ...);
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using p = pack<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test = typename p::template pop_front<2>;
        using expect = void(N<2>, N<3>, N<4>, ...);
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using p = pack<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test = typename p::template pop_back<2>;
        using expect = void(N<0>, N<1>, N<2>, ...);
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using p = pack<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test = typename p::template pop_back<5>;
        using expect = void(...);
        CT_ASSERT(std::is_same<test, expect>::value);
    }

    {
        using p = pack<N<0>, N<1>, N<2>, N<3>, N<4>>;
        using test = typename p::template pop_back<0>;
        using expect = void(N<0>, N<1>, N<2>, N<3>, N<4>, ...);
        CT_ASSERT(std::is_same<test, expect>::value);
    }
}

