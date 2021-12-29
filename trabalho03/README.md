# Trabalho 3
## Criar uma classe Vetor Geometrico

Implementar uma classe template Vetor<n,T> onde T deve ser numérico. As operações básicas de vetores geométricos devem estar implementadas.

Um Vetor em duas dimensões seria Vetor<2,double>.

Criar os operadores de multiplicação, adição e subtração de vetores. Lembrando que existe produto escalar e produto vetorial. Criar também multiplicação e divisão por escalar.

Bole uma forma do código abaixo compilar:

```
Vetor<2,double> v;
v = { 4.5, 6.1 };
```

O produto escalar será feito através de '*', e o produto vetorial, através de '**'.

Esse operador '**' não existe em C++, mas ele pode ser simulado através de 

```
v = a ** b;
```

Para isso você deve redefinir o operador '*' unário (ponteiro) para retornar uma classe intermediária (por exemplo, MeioDoProdutoVetorial) que contém o vetor b. Além disso, você deve redefinir o operador '*' entre um Vetor e a classe MeioDoProdutoVetorial para realizar o produto vetorial.

Por último, crie o operador '<<' para imprimir. 

Não colocar a main() no arquivo - o teste vai ter uma classe main.

Programa utilizado para testar:

```
#include <iostream>
#include "Vetor.cc"
using namespace std;
int main( int argc, char* argv[]) {
  Vetor< 3, double> a, b;
  int caso;
  double x, y, z;
  
  cin >> caso >> x >> y >> z;
  a = { x, y, z };
  b = { 1, 2, 3 };
  switch( caso ) {
      case 1: cout << a << endl; break;
      case 2: cout << a + b << endl; break;
      case 3: {
          Vetor< 3, double> c;
          c = a ** b; 
          cout << c << endl;
          break; 
      }
      case 4: cout << a * b << endl; break;
      case 5: cout << a * 3.0 << endl; break;
      case 6: cout << 2.1 * a << endl; break;
      case 7: cout << a + b + a * 2.0 << endl; break;
  }
  
  return 0;
}
```

