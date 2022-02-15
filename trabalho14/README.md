# Trabalho 14
## Objeto com tipo variável - Arrays

Iremos evoluir a tarefa Objeto com tipo variável para lidar com arrays. Você poderá usar o seu código como base, ou alterar uma das soluções apresentadas no Moodle pelo professor. As seguintes alterações devem ser implementadas:

1. Métodos de conversão

Definir os métodos isNumber(), asBool(), asString() etc. Serão métodos para teste e conversão de tipos. O comportamento esperado é o mesmo dos operadores em Javascript. Note que serão métodos da classe Var.

Exemplos:

```cpp
Var b;
for( b = 0; (b < 10).asBool(); b = b + 1 )
  cout << b <<  endl;
```
  
2. Arrays

A declaração de arrays será através da chamada da função newArray(). Um array é na verdade uma subclasse de Object, logo ele pode ter também propriedades indexadas por strings. Não há erros de limites de arrays para cima, apenas para índices negativos - nesse caso, o índice deve ser convertido em uma string e ser usado como nome de propriedade (ex: a[-1] se torna a["-1"]). Valores lidos que estão fora do limite do array são undefined. Se houver uma atribuição eles irão causar o redimensionamento do array. Arrays não diminuem de tamanho. 

```cpp
Var a, b;
a = newArray();
a["sqr"] = []( int n ){ return n*n; };
  
for( b = 0; (b < 10).asBool(); b = b + 1 )
  a[b] = a["sqr"]( b );
```

3. Métodos para Arrays:

Os seguintes métodos devem ser implementados para arrays:

- array.indexOf( elemento ): retorna a posição do elemento no array, ou -1 se o elemento não está no array.

- array.forEach( function ): executa uma função para cada elemento do array. Deve retornar undefined.

- array.filter( function ): retorna um array contendo os elementos para os quais a função foi verdadeira.

- array.map( function ): retorna um array contendo a função aplicada a cada um dos elementos do array.

Exemplos:

```cpp
  Var pares = []( int n ){ return n%2 == 0; };
  
  a.filter( pares ).forEach( []( Var n ){ cout << n << " "; } );
  cout << endl;
  
  a.filter( pares ).map( [](auto x){ return x / 2 + 0.1; } ).forEach( []( Var n ){ cout << n << " "; } );  
  cout << endl;
  
  auto indexOf = []( const Var& array, Var valor ) {
    int n = 0;
    int pos = -1;
    
    array.forEach( [&n,&pos,valor](auto x) { 
      if( pos == -1 ) { 
	if( (x == valor).asBool() ) 
	  pos = n; 
	n++; 
      } 
    } ); 

    return pos;
  };
  
  cout << (indexOf( a, 36 ) == a.indexOf( 36 ) ) << endl;
  cout << indexOf( a.filter( pares ), "A" ) << endl;
  
  a[11] = 'A';
  cout << a.indexOf( "A" ) << endl;
```
