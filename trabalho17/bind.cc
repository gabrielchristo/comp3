#include <tuple>
#include <type_traits>
#include <functional>
#include <iostream>
#include <utility>

#define compareWithPlaceHolder(t) std::is_same_v<PlaceHolder,decltype(t)>

class PlaceHolder {};

PlaceHolder __;

// implementação do stackoverflow para reverter uma tupla
template<typename T, typename TT = typename std::remove_reference<T>::type, size_t... I>
auto reverse_impl(T&& t, std::index_sequence<I...>) -> std::tuple<typename std::tuple_element<sizeof...(I) - 1 - I, TT>::type...> {
    return std::make_tuple(std::get<sizeof...(I) - 1 - I>(std::forward<T>(t))...);
}

template<typename T, typename TT = typename std::remove_reference<T>::type>
auto reverse(T&& t) -> decltype(reverse_impl(std::forward<T>(t), std::make_index_sequence<std::tuple_size<TT>::value>())) {
    return reverse_impl(std::forward<T>(t), std::make_index_sequence<std::tuple_size<TT>::value>());
}

// usando a ideia dita em sala para separar em head e tail...
template <typename ...T>
inline constexpr auto head(std::tuple<T...> t) {
    if constexpr (sizeof...(T) > 0) {
        return std::get<0>(t);
    } else {}
}

// implementação de tail feita em sala
template <typename T, size_t... indices>
inline constexpr auto tail_impl(T tp, std::index_sequence<indices...>) {
    return std::tuple{ std::get<indices+1>(tp)... };
}

template <typename ...T>
inline constexpr auto tail(std::tuple<T...> tp) {
    return tail_impl(tp, std::make_index_sequence<sizeof...(T)-1>());
}

// função para substituir os PlaceHolders do final
template <typename ...T>
inline constexpr auto replacePlaceHolderAtEnd(std::tuple<T...> tp) {
    auto reversed = reverse(tp);
    if constexpr (compareWithPlaceHolder(head(reversed))) {
        return replacePlaceHolderAtEnd(reverse(tail(reversed)));
    } else {
        return tp;
    }
}

// função para substituir os PlaceHolders no meio,
// substituindo-os pelos valores em t2
template<typename ...T1, typename ...T2>
auto replacePlaceHolder(std::tuple<T1...> t1, std::tuple<T2...> t2) {
    if constexpr (sizeof...(T1) == 0 && sizeof...(T2) != 0) {
        return t2;
    } else if constexpr(sizeof...(T1) != 0 && sizeof...(T2) == 0) {
        return t1;
    } else if constexpr (compareWithPlaceHolder(head(t1))) {
        // assumindo que t2 nao possui placeholder
        return std::tuple_cat(std::tuple{head(t2)}, replacePlaceHolder(tail(t1),tail(t2)));
    } else {
        return std::tuple_cat(std::tuple{head(t1)}, replacePlaceHolder(tail(t1), t2));
    }
}

template <typename F, typename ...Args1>
class Bind;

template <typename F, typename ...Args1>
auto bind( F f, Args1... args1 ) {
    return Bind{ f, replacePlaceHolderAtEnd(std::tuple{args1...}) };
}

template <typename F, typename ...T>
auto bind(F f, std::tuple<T...> args1) {
    return Bind{f, replacePlaceHolderAtEnd(args1)};
}

template <typename F, typename ...T>
inline constexpr auto apply(F f, std::tuple<T...> args) {
    if constexpr (std::is_invocable_v<F,T...>) {
        return std::apply(f, args);
    } else {
        return ::bind(f, args);
    }
}

template <typename F, typename ...Args1>
class Bind {
    public:
        Bind( F f, std::tuple<Args1...> args1 ): f(f), args1(args1) {}

        template <typename ...Args2>
        auto operator()( Args2... args2 ) {
            auto args = replacePlaceHolder(args1, std::tuple{args2...});
            return apply(f, args);
        }

    private:
        F f;
        std::tuple<Args1...> args1;
};

//

int main()
{
	return 0;
}
