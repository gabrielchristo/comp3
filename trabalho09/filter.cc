#include <type_traits>
#include <vector>
#include <initializer_list>

using namespace std;

template<typename C, typename T>
//auto operator|(const C &list, T F)
auto operator|(vector<C> list, T F)
{
	auto first = *begin(list);
	vector<decltype(first)> ret;

	// boolean case
	if constexpr (is_same<decltype(F(first)), bool>::value)
	{
		for(const auto& item : list)
			if(F(item)) ret.push_back(item);
		return ret;
	}

	// void return case
	else if constexpr (is_same<decltype(F(first)), void>::value)
	{
		for(const auto& item : list)
			F(item);
	}

	// any other case
	//else
	//{
	//	vector<decltype(F(first))> retType;
    //    for(const auto &item: list)
    //        retType.push_back(F(item));
    //    return retType;
	//}
	
}

//

#include <iostream>

int main()
{
	// Teste 1
	//vector<int> v1 = { 2, 9, 8, 8, 7, 4 };
	//auto result = v1 | []( int x ) { return x % 2 == 0; };
	//for( auto x : result ) cout << x << " ";

	// Teste 2
	vector<int> v1 = { 2, 9, 8, 8, 7, 4 };
	v1 | []( int x ) { return x % 2 == 0; } | [] ( int x ) { cout << x << " "; };
}