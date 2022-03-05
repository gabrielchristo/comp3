#include <vector>
#include <iterator>
#include <type_traits>
#include <functional>
#include <iostream>

#define INT_MAX 100

int nPrimeiros = INT_MAX;

template<typename T, typename F>
auto operator | ( const T& iterable, F function ) {
    if constexpr ( std::is_same_v< bool, std::invoke_result_t< F, decltype( *std::begin(iterable) ) > > ) {
        std::vector< std::decay_t< decltype( *std::begin(iterable) ) > > result;

        for( auto element : iterable ) 
            if( std::invoke( function, element ) )
                result.push_back( element );
        
        return result;
    }
    else if constexpr ( std::is_same_v< void, std::invoke_result_t< F, decltype( *std::begin(iterable) ) > > ) {
        for( auto element : iterable ) 
            std::invoke( function, element );
    }
    else {
        std::vector< std::decay_t< std::invoke_result_t< F, decltype( *std::begin(iterable) ) > > > result;

        for( auto element : iterable ) {
            if(nPrimeiros-->0)
                result.push_back(std::invoke(function, element));
            else break;
        }

        nPrimeiros = INT_MAX;
        return result;
    }
}

template<int FROM, int TO = INT_MAX>
class Range {
public:
    class iterator {
        long num = FROM;
    public:
        iterator(long _num = 0) : num(_num) {}
        iterator& operator++() {num = TO >= FROM ? num + 1: num - 1; return *this;}
        iterator operator++(int) {iterator retval = *this; ++(*this); return retval;}
        bool operator==(iterator other) const {return num == other.num;}
        bool operator!=(iterator other) const {return !(*this == other);}
        long operator*() {return num;}
        // iterator traits
        using difference_type = long;
        using value_type = long;
        using pointer = const long*;
        using reference = const long&;
        using iterator_category = std::forward_iterator_tag;
    };
    iterator begin() const {return FROM;}
    iterator end() const {return TO >= FROM? TO+1 : TO-1;}
};

#define RangeFrom(from) Range<from>()
#define RangeFromTo(from, to) Range<from, to-1>()

#define GET_MACRO(_1,_2,NAME,...) NAME
#define Intervalo(...) GET_MACRO(__VA_ARGS__, RangeFromTo, RangeFrom)(__VA_ARGS__)

class NPrimeiros {
    public:
        NPrimeiros(int n) {
            nPrimeiros = n;
        }

        template <typename T>
        auto operator () (T t) {
            return t;
        }
};

//

struct Impares
{
  bool operator()( int n ) {
    return n % 2 == 0;
  }
};

int main()
{
	return 0;
}
