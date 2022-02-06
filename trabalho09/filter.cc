#include <type_traits>
#include <vector>
#include <initializer_list>

using namespace std;

template<typename C, typename T>
auto operator|(C &list, T F)
{
	return filter(list, F);
}

template<typename C, typename T>
auto filter(C &list, T F)
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
		for(const auto& item : list) F(item);
	}
}

template<typename C, typename T>
auto operator|(vector<C> list, T F)
{
	//auto first = *begin(list);
	//vector<decltype(first)> ret;
	//// boolean case
	//if constexpr (is_same<decltype(F(first)), bool>::value)
	//{
	//	for(const auto& item : list)
	//		if(F(item)) ret.push_back(item);
	//	return ret;
	//}
	//// void return case
	//else if constexpr (is_same<decltype(F(first)), void>::value)
	//{
	//	for(const auto& item : list) F(item);
	//}

	return filter(list, F);
}

//

#include <iostream>

void Teste1()
{
	vector<int> v1 = { 2, 9, 8, 8, 7, 4 };
	auto result = v1 | []( int x ) { return x % 2 == 0; };
	for( auto x : result ) cout << x << " ";
}

void Teste2()
{
	vector<int> v1 = { 2, 9, 8, 8, 7, 4 };
	v1 | []( int x ) { return x % 2 == 0; } | [] ( int x ) { cout << x << " "; };
}

void Teste3()
{
	int v1[] = { 2, 9, 8, 8, 7, 4 };
	auto result = v1 | []( int x ) { return x % 2 == 0; };
	for( auto x : result ) cout << x << " ";
}

void Teste4()
{
	int v1[] = { 2, 9, 8, 8, 7, 4 };
	v1 | []( int x ) { return x % 2 == 0; } | [] ( int x ) { cout << x << " "; };
}

int main()
{
	Teste1();
	Teste2();
	Teste3();
	Teste4();

	return 0;
}
