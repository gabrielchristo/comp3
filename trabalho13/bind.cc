#include <functional>
#include <type_traits>

using namespace std;

template<typename F, typename ...Args, typename ...NewArgs>
auto bind(F functor, Args... args)
{
	if constexpr (is_invocable<decltype(functor), decltype(args)...>::value)
		return invoke(functor, args...);
	else
		return [functor, args...](auto... newArgs)
		{
			return bind(functor, args..., newArgs...);
		};
}
