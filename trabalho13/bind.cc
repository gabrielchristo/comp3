#include <functional>
#include <type_traits>

using namespace std;

template<typename F, typename ...Args>
class Bind
{
public:

	Bind(F functor, Args... args) : mFunctor(functor){}

	template<typename ...NewArgs>
	auto operator()(Args... args, NewArgs... newArgs)
	{
		return bind(mFunctor, args..., newArgs...);
	}

private:
	F mFunctor;
};


template<typename F, typename ...Args, typename ...NewArgs>
auto bind(F functor, Args... args)
{
	if constexpr (is_invocable<decltype(functor), decltype(args)...>::value)
		return invoke(functor, args...);
	else
		return [functor, args...](auto... newArgs)
		{
			//return invoke(functor, args..., newArgs...);
			return bind(functor, args..., newArgs...);
		};
}
