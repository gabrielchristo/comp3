# Trabalho 18
## Lazy Streams

Tome como base a tarefa Filter (pode partir da solução dada no laboratório) para que os vetores não sejam instanciados. Para isso, você deve retornar um Iterator a cada operador "|". Esse iterator (que tem os métodos begin, end e "++") vai fornecer um elemento de cada vez para o próximo "pipe".

Rode com o mesmo exemplo:

```cpp
int main( int argc, char* argv[] ) {
  int tab[10] =  { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
  vector<int> v;
  
  tab |	 [ &v ]( int x ) { v.push_back( x ); };
  v | []( int x ) { return x % 2 == 0; } 
    | []( int x ) { return x*x / 10.0; } 
    | [] ( double x ) { cout << x << endl; };
   
  cout << endl;
  return 0;
}
```

Crie também um gerador de intervalos, com a possibilidade de ter intervalos abertos (infinitos). Ex:

```cpp
Intervalo( 9, 99 )  | []( auto x ) { cout << x << " "; };  // Imprime de 9 a 98.
```

Crie uma classe que retorne o N-primeiros elementos do stream. O nome deve ser NPrimeiros.

```cpp
Intervalo( 0 ) | testa_se_e_primo | NPrimeiros( 10 ) | []( auto x ) { cout << x << " "; };
```

testa_se_e_primo é uma função que testa se um número é primo (um predicado). NPrimeiros passa para o pipe seguinte os NPrimeiros elementos que passaram no predicado testa_se_e_primo. 

Para começar a execução de um LazyStream é necessário colocar um Consumidor. Um Consumidor é uma função ou functor que retorna void.  

Assim o programa abaixo também deve ser válido:

```cpp
auto lazySt = Intervalo( 0 ) | testa_se_e_primo | NPrimeiros( 10 );
lazySt | []( auto x ) { cout << x << " "; };
```

Apenas na segunda linha que os números devem ser gerados.
