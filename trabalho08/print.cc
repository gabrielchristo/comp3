#include <initializer_list>
#include <iostream>
#include <memory>

using namespace std;

class AbstractPair
{
public:
	virtual void imprime(ostream& stream) = 0;
	virtual ~AbstractPair() {};
};

template <typename A, typename B>
class PairImpl : public AbstractPair
{
public:
	PairImpl(const A& a, const B& b) : mA(a), mB(b) {}

	PairImpl(const PairImpl& pair) : mA(pair.a), mB(pair.b) {}

	void imprime(ostream& stream)
	{
		stream << mA << " = " << mB << endl;
	}

private:
	A mA;
	B mB;
};

class Pair {
public:

  	template <typename A, typename B>
  	Pair( A a, B b ) {
		auto pair = new PairImpl<A,B>(a, b);
		p = shared_ptr<AbstractPair>(pair);
  	}

	void imprime(ostream& stream)
	{
		p->imprime(stream);
	}

private:
  	shared_ptr<AbstractPair> p;
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