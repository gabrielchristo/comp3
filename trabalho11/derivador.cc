#include <iostream>
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

class X
{
public:
	double operator()(double value){ return value; }
	double e(double value){ return value; }
	double dx(double value){ return 1; }
};

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

template<typename T1, typename T2>
class Result
{
public:

	Result(T1 t1, T2 t2, Operation op) : mT1(t1), mT2(t2), mOp(op){}

	auto operator()(double value)
	{
		return this->Calc(value);
 	}

	auto e(double value)
	{
		return this->Calc(value);
	}

	auto dx(double value)
	{
		switch(mOp)
		{
			case Operation::MULT: return mT1(value)*mT2.dx(value) + mT1.dx(value)*mT2(value);
			default: return 1337.0;
		}
	}


	auto Calc(double value)
	{
		switch(mOp)
		{
			case Operation::MULT:
			{
				return mT1(value) * mT2(value);
				cout << "Multiply";
			}

			case Operation::DIV:
			{
				return mT1(value)*mT2.dx(value) + mT1.dx(value)*mT2(value);
			}


			default: return 1337.0;
		}
	}


private:

	T1 mT1;
	T2 mT2;
	Operation mOp;
};

template<typename F1, typename F2>
auto operator*(F1 value1, F2 value2)
{
	return Result<F1, F2>(value1, value2, Operation::MULT);
}

template<typename F1>
auto operator*(double value1, F1 value2)
{
	return Result<Constant, F1>(value1, value2, Operation::MULT);
}
//
//template<typename F1>
//auto operator*(F1 value1, X value2)
//{
//	return Result<F1, X>(value1, value2, Result::Operation::MULTIPLY);
//}


//

int main()
{
  	auto f = 3.0 * x * x;
  	double v = 7;

  	cout << "f(" << v << ")=" << f.e( v ) << ", f'(" << v << ")=" << f.dx( v ) << endl;
}