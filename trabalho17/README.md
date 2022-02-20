# Trabalho 17
## Bind posicional

Altere a função bind da tarefa anterior de modo a permitir que os parâmetros sejam passados de forma posicional, tornando possível dar bind em um parâmetro do meio:

```cpp
auto f = bind( foo, __, __, 34 ); // guardou 34 para o terceiro parâmetro de foo
auto g = f( __, 56 ); // colocou 56 como segundo parâmetro de f, ou seja, equivale a bind( foo, __, 56, 34 )
cout << g( 9 ) << endl; // chamou foo( 9, 56, 34 )
```

Crie uma classe PlaceHolder e declare uma variável global "PlaceHolder __;" A princípio essa classe é vazia, mas se você achar conveniente pode declarar membros ou métodos.

Note que é necessário tratar quando se marca lugar para os parâmetros do fim:

```cpp
auto f = bind( foo, 89, __, __ );  // É o mesmo que bind( foo, 89 )
```

Ou seja, "__" como último parâmetros devem ser ignorados.

OBS: uma sugestão para a solução é usar tuple, e ir substituind PlaceHolder dentro da tupla pelos parâmetros fornecidos.
