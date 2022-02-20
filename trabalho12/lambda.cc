#include <iostream>
#include <math.h>
#include <type_traits>
#include <cstdint>
#include <sstream>
#include <vector>
#include <string>
#include <iterator>
#include <functional>
#include <typeinfo>
#include <cxxabi.h>

using namespace std;

class Var {
    public:
        template <typename K>
        K operator()( K v ) {
         return v;
        }
};

Var x;

template<typename T>
class Cte {
public:
    Cte( const T& c ): c(c) {}

    template<typename K>
    T operator()( K v ) {
        return c;
    }
  
private:
  T c;
};

template <typename F1>
class Sin {
public:
    Sin( F1 f1): f1(f1){}
    
    template<typename K>
    K operator() ( K v ) {
        return sin(f1(v));
    }
  
private:
  F1 f1;
};

template <typename F1>
Sin<F1> sin(F1 f1){
    if constexpr ((is_same_v<int,F1> || is_same_v<double,F1>)){
        return Sin<Cte<F1>>(f1);
    } 
    return Sin<F1>(f1);  
}

template <typename F1>
class Cos {
public:
    Cos( F1 f1): f1(f1){}
    
    template<typename K>
    K operator() ( K v ) {
        return cos(f1(v));
    }

private:
  F1 f1;
};

template <typename F1>
Cos<F1> cos(F1 f1){
    if constexpr ((is_same_v<int,F1> || is_same_v<double,F1>)){
        return Cos<Cte<F1>>(f1);
    } 
    return Cos<F1>(f1);  
}

template <typename F1>
class Exp {
public:
    Exp( F1 f1): f1(f1){}
    
    
    template<typename K>
    K operator() ( K v ) {
        return exp(f1(v));
    }
  
private:
  F1 f1;
};

template <typename F1>
Exp<F1> exp(F1 f1){
    if constexpr ((is_same_v<int,F1> || is_same_v<double,F1>)){
        return Exp<Cte<F1>>(f1);
    } 
    return Exp<F1>(f1);  
}

template <typename F1>
class Log {
public:
    Log( F1 f1): f1(f1){}
    
    template<typename K>
    K operator() ( K v ) {
        return log(f1(v));
    }
  
private:
  F1 f1;
};

template <typename F1>
auto log(F1 f1){
    if constexpr ((is_same_v<int,F1> || is_same_v<double,F1>)){
        return Log<Cte<F1>>(f1);
    }
    return Log<F1>(f1);  
}

template <typename F1, typename F2>
class Soma {
public:
    Soma( F1 f1, F2 f2 ): f1(f1), f2(f2) {}
    
    template<typename K>
    K operator() ( K v ) {
        return f1(v) + f2(v);
    }

private:
  F1 f1;
  F2 f2;
};

template <typename F1, typename F2> 
auto operator + ( F1 f1, F2 f2 ) {
    if constexpr ((is_same_v<int,F1> || is_same_v<double,F1>) && (is_same_v<int,F2> || is_same_v<double,F2>)){
        return Soma<Cte<F1>,Cte<F2>>( f1, f2 );
    }else if constexpr ((is_same_v<int,F1> || is_same_v<double,F1>) && (is_same_v<int,F2> || !is_same_v<double,F2>)){
        return Soma<Cte<F1>,F2>( f1, f2 );
    }else if constexpr (!(is_same_v<int,F1> || is_same_v<double,F1>) && (is_same_v<int,F2> || is_same_v<double,F2>)){
        return Soma<F1,Cte<F2>>( f1, f2 );
    }else{
        return Soma<F1,F2>( f1, f2 );
    }
}


template <typename F1, typename F2>
class Subtracao {
public:
    Subtracao( F1 f1, F2 f2 ): f1(f1), f2(f2) {}
    
    template<typename K>
    K operator() ( K v ) {
        return f1(v) - f2(v);
    }

  
private:
  F1 f1;
  F2 f2;
};

template <typename F1, typename F2>
auto operator - ( F1 f1, F2 f2 ) {
    if constexpr ((is_same_v<int,F1> || is_same_v<double,F1>) && (is_same_v<int,F2> || is_same_v<double,F2>)){
        return Subtracao<Cte<F1>,Cte<F2>>( f1, f2 );
    }else if constexpr ((is_same_v<int,F1> || is_same_v<double,F1>) && (is_same_v<int,F2> || !is_same_v<double,F2>)){
        return Subtracao<Cte<F1>,F2>( f1, f2 );
    }else if constexpr (!(is_same_v<int,F1> || is_same_v<double,F1>) && (is_same_v<int,F2> || is_same_v<double,F2>)){
        return Subtracao<F1,Cte<F2>>( f1, f2 );
    }else{
        return Subtracao<F1,F2>( f1, f2 );
    }
}

template <typename F1, typename F2>
class Multiplica {
public:
    Multiplica( F1 f1, F2 f2 ): f1(f1), f2(f2) {}
    
    template<typename K>
    K operator() ( K v ) {
        return f1(v) * f2(v);
    }
  
private:
  F1 f1;
  F2 f2;
};

template <typename F1, typename F2> 
auto operator * ( F1 f1, F2 f2 ) {
    if constexpr ((is_same_v<int,F1> || is_same_v<double,F1>) && (is_same_v<int,F2> || is_same_v<double,F2>)){
        return Multiplica<Cte<F1>,Cte<F2>>( f1, f2 );
    }else if constexpr ((is_same_v<int,F1> || is_same_v<double,F1>) && (is_same_v<int,F2> || !is_same_v<double,F2>)){
        return Multiplica<Cte<F1>,F2>( f1, f2 );
    }else if constexpr (!(is_same_v<int,F1> || is_same_v<double,F1>) && (is_same_v<int,F2> || is_same_v<double,F2>)){
        return Multiplica<F1,Cte<F2>>( f1, f2 );
    }else{
        return Multiplica<F1,F2>( f1, f2 );
    }
}

template <typename F1, typename F2>
class Divide {
public:
    Divide( F1 f1, F2 f2 ): f1(f1), f2(f2) {}
    
    template<typename K>
    K operator() ( K v ) {
        return f1(v) / f2(v);
    }

  
private:
  F1 f1;
  F2 f2;
};

template <typename F1, typename F2> 
auto operator / ( F1 f1, F2 f2 ) {
    if constexpr ((is_same_v<int,F1> || is_same_v<double,F1>) && (is_same_v<int,F2> || is_same_v<double,F2>)){
        return Divide<Cte<F1>,Cte<F2>>( f1, f2 );
    }else if constexpr ((is_same_v<int,F1> || is_same_v<double,F1>) && (is_same_v<int,F2> || !is_same_v<double,F2>)){
        return Divide<Cte<F1>,F2>( f1, f2 );
    }else if constexpr (!(is_same_v<int,F1> || is_same_v<double,F1>) && (is_same_v<int,F2> || is_same_v<double,F2>)){
        return Divide<F1,Cte<F2>>( f1, f2 );
    }else{
        return Divide<F1,F2>( f1, f2 );
    }
}

template <typename F1, typename F2>
class Potencia {
public:
    Potencia( F1 f1, F2 f2 ): f1(f1), f2(f2) {}
    
    
    template<typename K>
    K operator() ( K v ) {
        auto res = f1(v);
        for(int i=0; i<(f2(v)-1); i++){
            res = f1(v) * res;
        }
        return res;
    }
  
private:
  F1 f1;
  F2 f2;
  int newExp = f2.e(0) - 1;
};


template <typename F1, typename F2> 
Potencia<F1,F2> operator ->* (F1 f1, F2 n) {
    static_assert(!is_same<double,F2>::value, "Operador de potenciação definido apenas para inteiros");
    return Potencia<F1,F2>(f1,n);
}

template<typename T, typename F>
auto operator | ( const T& iterable, F function ) {
    if constexpr ( is_same_v< bool, invoke_result_t< F, decltype( *begin(iterable) ) > > ) {
        vector< decay_t< decltype( *begin(iterable) ) > > result;

        for( auto element : iterable ) 
            if( invoke( function, element ) )
                result.push_back( element );
        
        return result;
    }
    else if constexpr ( is_same_v< void, invoke_result_t< F, decltype( *begin(iterable) ) > > ) {
        for( auto element : iterable ) 
            invoke( function, element );
    }
    else {
        std::vector< decay_t< invoke_result_t< F, decltype( *begin(iterable) ) > > > result;

        for( auto element : iterable ) 
            result.push_back( invoke( function, element ) );
        
        return result;
    }
}


template <typename F1, typename F2>
class Imprime {
public:
    string f3 = "";
    Imprime( F1 &f1, F2 f2): f1(f1), f2(f2){}
    

    template<typename K>
    void operator() ( K v ) {
       f1 << f2(v) << f3;
    }
  
private:
  F1 &f1;
  F2 f2;
};


template<typename F1>
F1 operator << (F1 f1, char f2){
    f1.f3 = f1.f3 + f2;
    return f1;
}

Imprime<ostream,Var> operator << (ostream &o, Var f1){
    return Imprime<ostream,Var> (o, f1);
}

template<typename T1, typename T2>
Imprime<ostream,Soma<T1,T2>> operator << (ostream &o, Soma<T1,T2> f1){
    return Imprime<ostream,Soma<T1,T2>> (o, f1);
}

template<typename T1, typename T2>
Imprime<ostream,Subtracao<T1,T2>> operator << (ostream &o, Subtracao<T1,T2> f1){
    return Imprime<ostream,Subtracao<T1,T2>> (o, f1);
}

template<typename T1, typename T2>
Imprime<ostream,Multiplica<T1,T2>> operator << (ostream &o, Multiplica<T1,T2> f1){
    return Imprime<ostream,Multiplica<T1,T2>> (o, f1);
}

template<typename T1, typename T2>
Imprime<ostream,Divide<T1,T2>> operator << (ostream &o, Divide<T1,T2> f1){
    return Imprime<ostream,Divide<T1,T2>> (o, f1);
}

template<typename T1, typename T2>
Imprime<ostream,Sin<T1>> operator << (ostream &o, Sin<T1> f1){
    return Imprime<ostream,Sin<T1>> (o, f1);
}

template<typename T1, typename T2>
Imprime<ostream,Cos<T1>> operator << (ostream &o, Cos<T1> f1){
    return Imprime<ostream,Cos<T1>> (o, f1);
}

template<typename T1, typename T2>
Imprime<ostream,Log<T1>> operator << (ostream &o, Log<T1> f1){
    return Imprime<ostream,Log<T1>> (o, f1);
}

template<typename T1, typename T2>
Imprime<ostream,Exp<T1>> operator << (ostream &o, Exp<T1> f1){
    return Imprime<ostream,Exp<T1>> (o, f1);
}


template <typename F1, typename F2>
class Modulo {
public:
    Modulo( F1 f1, F2 f2): f1(f1), f2(f2){}
    

    template<typename K>
    K operator() ( K v ) {
        if constexpr((is_same_v<int,F1> || is_same_v<double,F1>) && (is_same_v<int,F2> || is_same_v<double,F2>)){
            return f1 % f2;
        }else if  constexpr(!(is_same_v<int,F1> || is_same_v<double,F1>) && (is_same_v<int,F2> || is_same_v<double,F2>)){
            return f1(v) % f2;
        }else if  constexpr((is_same_v<int,F1> || is_same_v<double,F1>) && !(is_same_v<int,F2> || is_same_v<double,F2>)){
            return f1 % f2(v);
        }else{
            return f1(v) % f2(v);
        }
    }
  
private:
  F1 f1;
  F2 f2;
};


template<typename F1, typename F2>
Modulo<F1, F2> operator % (F1 f1, F2 f2){
    return Modulo<F1,F2>(f1, f2);
}


template <typename F1, typename F2>
class Booleano {
public:
    Booleano( F1 f1, F2 f2): f1(f1), f2(f2){}
    

    template<typename K>
    bool operator() ( K v ) {
        if constexpr((is_same_v<int,F1> || is_same_v<double,F1>) && (is_same_v<int,F2> || is_same_v<double,F2>)){
            return (f1 == f2) ? true : false;
        }else if  constexpr(!(is_same_v<int,F1> || is_same_v<double,F1>) && (is_same_v<int,F2> || is_same_v<double,F2>)){
            return (f1(v) == f2) ? true : false;
        }else if  constexpr((is_same_v<int,F1> || is_same_v<double,F1>) && !(is_same_v<int,F2> || is_same_v<double,F2>)){
            return (f1 == f2(v)) ? true : false;
        }else{
            return (f1(v) == f2(v)) ? true : false;
        }
    }
  
private:
  F1 f1;
  F2 f2;
};

template<typename F1, typename F2>
Booleano<F1, F2> operator == (F1 f1, F2 f2){
    return Booleano<F1,F2>(f1, f2);
}

//

int main()
{
	vector<int> v1 = { 1, 2, 3, 4, 1, 1, 0, 8 };
    v1 | (x % 2 == 0) | cout << x*x + 1 << ' ';


	//int v1[] = { 1, 2, 3, 4, 1, 1, 0, 8 };
	//v1 | (x % 2 == 0) | cout << x*x + 1 << ' ';

	//int v1[] = { 1, 2, 3, 4, 1, 1, 0, 8 };
	//v1 | (x % 2 == 1) | x*x | cout << x << ' ';

	//string v1[] = { "a", "b2", "cc3", "saci" };
	//v1 | []( string n ) { return n.length() % 2 == 0; } | (x+x) | cout << x << ' ';

}