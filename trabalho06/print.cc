#include <initializer_list>
#include <iostream>

using namespace std;

class AbstractPair
{
public:
	virtual void imprime(ostream& stream) = 0;
};

template <typename A, typename B>
class PairImpl : public AbstractPair
{
public:

	PairImpl(A a, B b) : a(a), b(b) {}

	void imprime(ostream& stream)
	{
		stream << a << " = " << b << endl;
	}

private:
	A a;
	B b;
};

class Pair {
public:

  	template <typename A, typename B>
  	Pair( A a, B b ) {
		p = new PairImpl<A,B>(a, b);
  	}

	void imprime(ostream& stream)
	{
		p->imprime(stream);
	}

private:
  	AbstractPair *p;
};

void print( ostream& o, initializer_list<Pair> lista )
{
	for(auto item : lista)
		item.imprime(o);
}

//

int main() {
 
    Pair p( "1", 2 );
  
    print( cout, { { "jan", 1 }, { 2, "fev" }, { string( "pi" ), 3.14 } } );

  return 0;  
}