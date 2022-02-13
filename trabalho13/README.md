# Trabalho 13
## Classe bind e função bind

Nesse trabalho você deve criar uma classe template Bind que recebe um functor/função e armazena esse functor, juntamente com possíveis parâmetros. Cada vez que uma função é ligada (binded) a um parâmetro, ela perde em n-aridade (ou seja, diminui o seu número de parâmetros). Ex: se uma função de dois parâmetros é ligada a um parâmetro, ela se torna uma nova função de apenas um parâmetro (o outro deve ser armazenado).

```cpp
int mdc( int a, int b ) { return b == 0 ? a : mdc( b, a%b ); }
auto f = bind( mdc, 12 ); 
// f é uma função de um parâmetro que calcula o mdc entre 12 e o parâmetro passado.  
cout << f( 9 ) << endl; // deve imprimir 3, que é o mdc entre 12 e 9.
```

Outros exemplos de uso:

```cpp
void func4( int a, string b, int c, double d ) {
  // Faz algum processamento
}


int main() {
  auto f3 = bind( func4, 5 );

  cout << f3( "b", 7, 2.1 ) << endl;
 
  auto f2 = bind( f3, "b" );
  auto f2_a = f3( "b" );
  auto f2_b = f3( "b" );
  auto f1 = f3( "b", 8 );

  cout << f1( 1.1 ) << endl; 
  cout << f2( 2, 1.1 ) << endl; 
  cout << f2_a( 2, 1.1 ) << endl; 
  cout << f2_b( 2, 1.1 ) << endl; 
}
```

Note que devemos declarar uma função auxiliar bind, embora poderia ser possível usar a sintaxe Bind{ func4, 1, "a" };  - só que não haverão testes neste sentido. 

Arquivo usado para compilar os testes:

```cpp
#include <iostream>
#include <algorithm>
#include <array>

#include "bind.cc"

using namespace std;

long mdc( long a, long b ) { return b == 0 ? a : mdc( b, a%b ); }

struct MMC {
  auto operator()( long a, long b ) { return a*b/mdc(a,b); }    
};

struct BarraPesada {
  template <typename A, typename B>
  auto operator()( A a, B b ) {
      return a + b;
  } 
};

string ordena( string a, string b, string c, string d, string e, string f, string g, string h, string i, string j, string k, string l ) {
  std::array<string, 12> tab = { a, b, c, d, e, f, g, h, i, j, k, l };
  string result;
  
  std::sort( tab.begin(), tab.end() );
  for( auto itr = tab.begin(); itr != tab.end(); ++itr )
    result += *itr + " ";
  
  return result;    
}

int main() {
    
using ::bind;
  
/* Aqui entram os comandos nos casos de teste */
  
  return 0;
}
```
