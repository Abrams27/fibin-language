#include <iostream>
#include <stdlib.h>
#include <assert.h>

//Fib
template <int N>
struct Fib {
    static_assert(N >= 0);
    static constexpr auto value = Fib<N-1>::value + Fib<N-2>::value;
};

template <>
struct Fib<0> {
    static constexpr auto value = 0;
};

template <>
struct Fib<1> {
    static constexpr auto value = 1;
};

//Lit
template <typename T>
struct is_fib : std::false_type {};

template <int N>
struct is_fib<Fib<N>> : std::true_type {};

template <typename T>
inline constexpr bool is_fib_v = is_fib<T>::value;

template <typename T>
struct Lit { //trzeba jeszcze zrobić dla True i False
    static_assert(is_fib_v<T>);
};

//Var
template <typename T>
struct Var {

};


int main() {

    std::cout<<Fib<8>::value<<std::endl;
    Lit<Fib<7>>();

    return 0;
}
