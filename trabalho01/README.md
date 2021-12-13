# Trabalho 1
## Classe PilhaInt

Implemente uma classe PilhaInt.

Nesse exercício você deverá implementar uma classe PilhaInt, de forma semelhante à que vimos na aula.

Você deve  criar um construtor sem nenhum parâmetro, um método empilha que recebe um parâmetro do tipo int, um método desempilha que retorna um int, um método print que recebe um ostream& como parâmetro e um operador de atribuição. Não use o construtor default e nem o operador de atribuição default. 

A classe ostream é usada para representar a saída. cout é um subtipo de ostream. 

```
void print_msg( ostream& o, const char* msg ) {
  o << msg << endl;
}
```

Assim, a função print_msg quando chamada como abaixo

```
print_msg( cout, "Erro!!" );
```

Irá imprimir a mensagem na saída padrão:

```
Erro!!
```

Envie um único arquivo pilha.cc (ou copie e cole no editor) contendo apenas a definição da classe. Não é permitido nenhum "#include", nem o uso de nenhum biblioteca além da iostream (que será incluída pelo meu programa principal). Não coloque nesse arquivo a função main, ou dará erro de compilação.

Exemplo de pilha.cc:

```
class PilhaInt {
  public:
// Seus métodos contendo o seu código
private:
// Atributos da sua classe
};
```

Você deve criar um "operador <<" para a PilhaInt, e que terá a função de empilhar.
