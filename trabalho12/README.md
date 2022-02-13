# Trabalho 12
## Expressões lambda simplificadas

Tente fazer expressões lambda que permitam o programa abaixo compilar (e executar corretamente):

```cpp
X x; // Declarar em algum lugar global.
int tab[10] =  { 1, 2, 3, 2, 3, 4, 6, 0, 1, 8 };
vector<int> v;
tab | cout << x*x << '\n';
tab | [ &v ]( int x ) { v.push_back( x ); };
v | x % 2 == 0 | cout << x*x + 1 << '\n';
v | x % 2 == 1 | x*x | cout << x << '\n';
```

Ideias:

```cpp
class X {
  template <typename K>
  auto operator() ( K valor ) {
    return valor;
  }
}; 


template <typename Op1, typename Op2> 
class Soma {
public:
  auto operator() ( auto valor ) {
    return a( valor ) + b( valor );
  } 

private:
  Op1 a;
  Op2 b;
};

template <typename T> 
class Cte {
public:
  Cte( const T& valor ): valor( valor ) {}

  template<typename K>
  T operator() ( K ignorar ) {
    return valor;
  } 

private:
  T valor;
};

template <typename Op1, typename Op2>
Op1 operator + ( Op1 a, Op2 b ) {
  return Soma< Op1, Op2 >( a, b );
}
```

x + x + x ==> deve retornar uma classe do tipo Soma< Soma< X, X >, X>;

```cpp
auto s = x + x + x;
s( 8 ); // Soma 8 + 8 + 8.
```

Podemos utilizar também a abordagem de Composição de expressões lambda, evitando assim declara uma grande quantidade de classes:

```cpp
auto operator + ( auto a, auto b ) {
  return [a,b]( auto x ){ return a(x) + b(x); }; 
}
```

O operador "+" irá retornar uma expressão lambda que faz a soma. No entanto, ele está assumindo que os dois parâmetros a e b são functores. Ou seja, funcionará para "x + x", mas não para "x + 8". O caso do "8" deve ser tratado de forma diferente, pois não é um functor. Uma abordagem é convertê-lo para um functor "constante":

```cpp
auto cte( auto valor ) { return [valor]( auto x ) { return valor; } ; }
```
