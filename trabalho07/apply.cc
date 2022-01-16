#include <vector>

using namespace std;

// type C is container
// type T is function
template<typename C, typename T>
auto apply(const C& list, T F)
{
	// vector with same type that function F return
	vector<decltype(F(*begin(list)))> v;
	
	// vector with F result for each item
	for(const auto& item : list)
		v.push_back(F(item));

	return v;
}

// overload for initializer list
template<typename C, typename T>
auto apply(initializer_list<C> list, T F)
{
	return apply<decltype(list), T>(list, F);
}