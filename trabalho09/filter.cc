#include <type_traits>
#include <vector>
#include <initializer_list>

using namespace std;

template<typename C, typename T>
//auto operator|(const C &list, T F)
auto operator|(vector<C> list, T F)
{
	auto first = *begin(list);
	auto returnType = F(first);

	vector<decltype(first)> retElement;
	vector<decltype(returnType)> retType;

	// boolean case
	if constexpr (is_same<decltype(returnType), bool>::value)
	{
		for(const auto& item : list)
			if(F(item)) retElement.push_back(item);
		return retElement;
	}

	// void return case
	else if constexpr (is_same<decltype(returnType), void>::value)
	{
		for(const auto& item : list)
			F(item);
	}

	// any other case
	else
	{
        for(const auto &item: list)
            retType.push_back(F(item));
        return retType;
	}
	
}

//

#include <iostream>

int main()
{
	vector<int> v1 = { 2, 9, 8, 8, 7, 4 };
	auto result = v1 | []( int x ) { return x % 2 == 0; };
	for( auto x : result ) cout << x << " ";
}