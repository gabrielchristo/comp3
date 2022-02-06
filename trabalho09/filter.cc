#include <type_traits>
#include <vector>
#include <initializer_list>
#include <map>
#include <algorithm>

using namespace std;

template<typename C, typename T>
auto operator|(C &list, T F)
{
	return filter(list, F);
}

template<typename C, typename T>
auto operator|(vector<C> list, T F)
{
	return filter(list, F);
}

template<typename C1, typename C2, typename T>
auto operator|(map<C1,C2> dict, T F)
{
	return filter(dict, F);
}

template<typename C>
auto operator|(vector<C> &list, decltype(&string::length) F)
{
    vector<unsigned long int> ret;
    for(const auto &item: list) ret.push_back(item.length());
    return ret;
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
	// any other cases
	else
	{
		vector<decltype(F(first))> ret;
		for(const auto& item : list) ret.push_back(F(item));
		return ret;
	}
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

void Teste5()
{
	map<string,string> v = { { "a", "1" }, { "b", "2" }, { "c", "3" }, { "d", "4" }, { "e", "5" } };
	v | []( auto x ){ return pair{ x.first, stod( x.second ) }; } | []( auto p ) { cout << p.second + 1.1 << " "; };
}

void Teste6()
{
	map<string,string> v = { { "a", "1" }, { "b", "2" }, { "c", "3" }, { "d", "4" }, { "e", "5" }, { "f", "6" } };
	auto par = []( auto x ){ return stoi( x.second ) % 2 == 0; };
	auto upper_first = []( auto x ){ string st = x.first; transform(st.begin(), st.end(), st.begin(), ::toupper); return st; };
	v | par | upper_first | []( auto st ) { cout << st + "! "; };
}

void Teste7()
{
	map<string,string> v = { { "a", "1" }, { "b", "2" }, { "c", "3" }, { "d", "4" }, { "e", "5" }, { "F", "6" } };
	auto par = []( auto x ){ return stoi( x.second ) % 2 == 0; };
	auto first = []( pair<string,string> p ) { return p.first; };
	auto upper = []( string st ){ transform(st.begin(), st.end(), st.begin(), ::toupper); return st; };
	vector<string> result = v | par | first | upper;
	result | []( auto st ) { cout << st + "! "; };
}

void Teste8()
{
	vector<string> v1 = { "janeiro", "fevereiro", "março", "abril", "maio" };
	v1 | &string::length | [] ( int x ) { cout << x << " "; };
}

int main()
{
	Teste1();
	Teste2();
	Teste3();
	Teste4();
	Teste5();
	Teste6();
	Teste7();
	Teste8();

	return 0;
}
