# Trabalho 7
## Função apply

Crie uma função apply que recebe um array (pode ser vector também, na verdade qualquer tipo iterável) e uma função F, e retorna um vector cujo tipo base é definido pelo valor de retorno de F.

Exemplo:

```
Entrada: vector<int> v{ 1, 2, 3, 4 }
F = int sqr( int a ) { return a*a; }
Saida: vector<int>, com os valores { 1, 4, 9, 16 } 
```

Se a função F for algo do tipo:

```
string romanos( int n ) { // blablaba }
```

a saída será:

```
vector<string> => { "I", "IV", "IX", "XVI" }
```

Exemplo de uso:

```
vector<int> v{ 1, 3, 5 };

vector<double> s = apply( v, sin );
```

Os testes são realizados com o seguinte programa, trocando o place-holder pela entrada do teste:

```
#include <vector>
#include <iostream>
#include <math.h>
#include <string>
#include <map>

#include "apply.cc"

using namespace std;

double seno( double n ) { return sin(n); }
int id( int n ) { return n; }
string roman( int n ) {
    map<int,string> rom = { { 1, "I" }, { 2, "II" }, { 3, "III" }, { 4, "IV" }, { 5, "V" }, { 6, "VI" }, { 7, "VII" }, { 8, "VIII" } } ; 

    return rom[n]; 
}

struct FunctorSimples { 
    string operator()( int n ) { return roman( n ) + "!"; }
};

struct FunctorTemplate { 
    template <typename T>
    T operator()( T n ) { return n+n; }
};

template <typename T>
ostream& operator << ( ostream& o, const vector<T>& v ) {
    o << "[ ";
    for( auto x : v )
        o << x << " ";
        
    return o << "]";
}

int main( int argc, char* argv[]) {     

/* TESTCASE-PLACE-HOLDER */

  return 0;
}
```


