# Trabalho 19
## Otimizador de Expressões para Matrizes

Um otimizador de expressões para Matrizes é um conjunto de classes e operadores que, dada uma expressão de matrizes envolvendo "+" e "*" (por exemplo, A*B + C) escolhe a ordem de execução com menor número de operações de soma e multiplicação (e que por isso deve ter a execução mais rápida). Por exemplo, (A*B)*C pode ser bem mais lento do que A*(B*C), embora o resultado seja idêntico (basta que A seja uma matriz-coluna, B uma matriz-linha e C uma matriz quadrada).

Nessa tarefa você deve construir um tipo template Matriz<L,C> para double e os respectivos operadores de multiplicação e adição de matrizes, bem como uma operação para aplicar uma função à uma matriz.

Exemplo de declarações válidas:

```cpp
int main() {
  Matriz<10,20> a;
  Matriz<20,3> b;
  auto c = a*b;
  
// aplicar uma função à uma matriz:
  
  auto f = Apply( []( double x ){ return rand(); } );
  
  c = f(c);
  /* Vai calcular c[i][j] = g( c[i][j] ); */
  auto d = f(a) * b;
  
  for( int i = 0; i < d.nLin(); i++ )
    for( int j = 0; j < d.nCol(); j++ )
      cout << d[i][j] << endl;
  
  return 0;  
}
```

Arquivo inicial:

```cpp
template <int L, int C>
class Matriz {
};

template <int L, int LC, int C>
Otimizador< ?? > operator * ( const Matriz<L,LC>& a, const Matriz<LC,C>& b ) {
}

template <typename F>
class Apply {
public:
  Apply( F f ): f(f) {}
  
  template <int L, int C>
  Matriz<L,C> operator()( const Matriz<L,C>& m ) const {
  }
  
private:
  F f;
};
```
