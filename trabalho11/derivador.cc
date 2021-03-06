#include <cmath>
#include <type_traits>

using namespace std;

#define x X()

enum class Operation
{
	MULT = 0,
	ADD,
	SUB,
	DIV,
	POW,
	EXP,
	LOG,
	SIN,
	COS
};

// variable class
class X
{
public:
	double operator()(double value){ return value; }
	double e(double value){ return value; }
	double dx(double value){ return 1; }
};

// constant class
class Constant
{
public:
	Constant(double value): mValue(value){}
  	double operator()(double value){ return mValue; }
	double e(double value){ return value; }
	double dx(double value){ return 0; }
private:
	double mValue;
};

// binary operations class
template<typename T1, typename T2>
class Binary
{
public:

	Binary(Operation op, T1 t1, T2 t2) : mT1(t1), mT2(t2), mOp(op){}

	auto dx(double value)
	{
		switch(mOp)
		{
			case Operation::POW:{ return mT2(value) * mT1.dx(value) * pow(mT1(value), mT2(value) - 1); }
			case Operation::MULT:{ return mT1(value)*mT2.dx(value) + mT1.dx(value)*mT2(value); }
			case Operation::DIV:{ return (mT1.dx(value)*mT2(value) - mT1(value)*mT2.dx(value)) / (mT2(value) * mT2(value)); }
			case Operation::ADD:{ return mT1.dx(value) + mT2.dx(value); }
			case Operation::SUB:{ return mT1.dx(value) - mT2.dx(value); }
			default: return 1337.0;
		}
	}

	auto operator()(double value){ return this->Calc(value); }

	auto e(double value){ return this->Calc(value); }

	auto Calc(double value)
	{
		switch(mOp)
		{
			case Operation::POW:{ return pow(mT1(value), mT2(value)); }
			case Operation::MULT:{ return mT1(value) * mT2(value); }
			case Operation::DIV:{ return mT1(value) / mT2(value); }
			case Operation::ADD:{ return mT1(value) + mT2(value); }
			case Operation::SUB:{ return mT1(value) - mT2(value); }
			default: return 1337.0;
		}
	}

private:

	T1 mT1;
	T2 mT2;
	Operation mOp;
};

// unary operations class
template<typename T1>
class Unary
{
public:

	Unary(Operation op, T1 t1) : mT1(t1), mOp(op){}

	auto dx(double value)
	{
		switch(mOp)
		{
			case Operation::SIN:{ return cos(mT1(value)) * mT1.dx(value); }
			case Operation::COS:{ return sin(mT1(value)) * -1.0 * mT1.dx(value); }
			case Operation::EXP:{ return exp(mT1(value)) * mT1.dx(value); }
			case Operation::LOG:{ return 1 / mT1(value); }
			default: return 1337.0;
		}
	}

	auto operator()(double value){ return this->Calc(value); }

	auto e(double value){ return this->Calc(value); }

	auto Calc(double value)
	{
		switch(mOp)
		{
			case Operation::SIN:{ return sin(mT1(value)); }
			case Operation::COS:{ return cos(mT1(value)); }
			case Operation::EXP:{ return exp(mT1(value)); }
			case Operation::LOG:{ return log(mT1(value)); }
			default: return 1337.0;
		}
	}

private:

	T1 mT1;
	Operation mOp;
};

// mult operator

template<typename F1, typename F2>
auto operator*(F1 value1, F2 value2){ return Binary<F1, F2>(Operation::MULT, value1, value2); }

template<typename F2>
auto operator*(double value1, F2 value2){ return Binary<Constant, F2>(Operation::MULT, Constant(value1), value2); }

template<typename F2>
auto operator*(int value1, F2 value2){ return Binary<Constant, F2>(Operation::MULT, Constant(value1), value2); }

template<typename F2>
auto operator*(X value1, F2 value2) { return Binary<X, F2>(Operation::MULT, value1, value2); }

// div operator

template<typename F1, typename F2>
auto operator/(F1 value1, F2 value2){ return Binary<F1, F2>(Operation::DIV, value1, value2); }

template<typename F2>
auto operator/(double value1, F2 value2){ return Binary<Constant, F2>(Operation::DIV, Constant(value1), value2); }

template<typename F2>
auto operator/(int value1, F2 value2){ return Binary<Constant, F2>(Operation::DIV, Constant(value1), value2); }

template<typename F2>
auto operator/(X value1, F2 value2) { return Binary<X, F2>(Operation::DIV, value1, value2); }

// add operator

template<typename F1, typename F2>
auto operator+(F1 value1, F2 value2){ return Binary<F1, F2>(Operation::ADD, value1, value2); }

template<typename F2>
auto operator+(double value1, F2 value2){ return Binary<Constant, F2>(Operation::ADD, Constant(value1), value2); }

template<typename F1>
auto operator+(F1 value1, double value2){ return Binary<F1, Constant>(Operation::ADD, value1, Constant(value2)); }

template<typename F2>
auto operator+(int value1, F2 value2){ return Binary<Constant, F2>(Operation::ADD, Constant(value1), value2); }

template<typename F1>
auto operator+(F1 value1, int value2){ return Binary<F1, Constant>(Operation::ADD, value1, Constant(value2)); }

// sub operator

template<typename F1, typename F2>
auto operator-(F1 value1, F2 value2){ return Binary<F1, F2>(Operation::SUB, value1, value2); }

template<typename F2>
auto operator-(double value1, F2 value2){ return Binary<Constant, F2>(Operation::SUB, Constant(value1), value2); }

template<typename F1>
auto operator-(F1 value1, double value2){ return Binary<F1, Constant>(Operation::SUB, value1, Constant(value2)); }

template<typename F2>
auto operator-(int value1, F2 value2){ return Binary<Constant, F2>(Operation::SUB, Constant(value1), value2); }

template<typename F1>
auto operator-(F1 value1, int value2){ return Binary<F1, Constant>(Operation::SUB, value1, Constant(value2)); }

// cos operator

template<typename F1>
auto cos(F1 value1){ return Unary<F1>(Operation::COS, value1); }

// sin operator

template<typename F1>
auto sin(F1 value1){ return Unary<F1>(Operation::SIN, value1); }

// exp operator

template<typename F1>
auto exp(F1 value1){ return Unary<F1>(Operation::EXP, value1); }

// log operator

template<typename F1>
auto log(F1 value1){ return Unary<F1>(Operation::LOG, value1); }

// pow operator

template <typename F1, typename F2>
auto operator->*(F1 value1, F2 value2)
{
	static_assert(is_same<int, F2>::value, "Operador de potencia????o definido apenas para inteiros");
	return Binary<F1, Constant>(Operation::POW, value1, Constant(value2));
}

//

#include <iostream>

void Teste1()
{
	auto f = 3.0 * x * x;
  	double v = 7;
  	cout << "f(" << v << ")=" << f.e( v ) << ", f'(" << v << ")=" << f.dx( v ) << endl;
}

void Teste2()
{
	double v = 1.1;
	auto f = x*x*( x + 8.0 ) + x;
	cout << "f(" << v << ")=" << f.e( v ) << ", f'(" << v << ")=" << f.dx( v ) << endl;
}

void Teste3()
{
	double v = 0.5;
	auto f = sin( x * x * cos( 3.14 * x + 1.0 ) );
	cout << "f(" << v << ")=" << f.e( v ) << ", f'(" << v << ")=" << f.dx( v ) << endl;
}

void Teste4()
{
	double v = 3.14;
	auto f = sin( x * x - cos( 3.14 * x + 1.0 ) );
	cout << "f(" << v << ")=" << f.e( v ) << ", f'(" << v << ")=" << f.dx( v ) << endl;
}

void Teste5()
{
	double v = 3.14159;
	auto f =  sin(x)/cos(x);
	cout << "f(" << v << ")=" << f.e( v ) << ", f'(" << v << ")=" << f.dx( v ) << endl;
}

void Teste6()
{
	double v = -7.3;
	auto f = x->*3 + x->*2;
	cout << "f(" << v << ")=" << f.e( v ) << ", f'(" << v << ")=" << f.dx( v ) << endl;
}

void Teste7()
{
	double v = -0.5;
	auto f = 1.0 / (sin(x)->*2 + cos(x)->*2)->*4;
	cout << "f(" << v << ")=" << f.e( v ) << ", f'(" << v << ")=" << f.dx( v ) << endl;
}

void Teste8()
{
	double v = 0.1;
	auto f = 1 / (1 + exp( -2*( x - 1 )->*4 ) );
	cout << "f(" << v << ")=" << f.e( v ) << ", f'(" << v << ")=" << f.dx( v ) << endl;
}

void Teste9()
{
	double v = 3;
	auto f = exp( x * log( x ) );
	cout << "f(" << v << ")=" << f.e( v ) << ", f'(" << v << ")=" << f.dx( v ) << endl;
}

void Teste10()
{
	//double v = 3;
	//auto f =  2 * x->*1.1;
	//checado manualmente, deve gerar um erro estatico ao compilar
}

int main()
{
  	Teste1();
	Teste2();
	Teste3();
	Teste4();
	Teste5();
	Teste6();
	Teste7();
	Teste8();
	Teste9();
	Teste10();

	return 0;
}
