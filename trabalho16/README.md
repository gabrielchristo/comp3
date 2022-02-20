# Trabalho 16
## Expressões Lambda Complicadas

Usando as Expressões Lambda Simplificadas da tarefa anterior, faça com que o código abaixo rode também:

```cpp
vector m< vector<int> >;
m | x[0] != 0 | ( x | cout << x << '\n' );
```

Nesse caso m é um vetor de vetores, e então o primeiro x é um vetor. Logo, podemos escrever um pipe para ele.

E será necessário redefinir o operador "[]" para Expressões Lambda.

Modelo:

```cpp
#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include <string.h>

using namespace std;

#include "lambda.cc"

vector<int> operator + ( const vector<int>& v, int n ) {
    vector<int> result{ v };
    result.push_back( n );
    return result;
}

int main() {
    decltype(::x) x(::x);
    
/* TESTCASE-PLACE-HOLDER */
  
  return 0;
}
```
