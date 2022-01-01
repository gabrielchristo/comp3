#include <iostream>
#include <initializer_list>

//

#include <vector>

using namespace std;

template<int N, typename T>
class Vetor
{

public:

	// classe intermediaria para produto vetorial
	class MeioDoProdutoVetorial
	{
	friend class Vetor;
	public:
		MeioDoProdutoVetorial(const Vetor& vector) : mList(vector.mInitList) {};
	private:
		vector<T> mList;
	};

	// construtor
	Vetor(){};

	// atribuicao
	Vetor& operator=(initializer_list<T> init_list)
	{
		mInitList = init_list;
		return *this;
	}

	// multiplicacao com vetor (produto escalar)
	T operator*(const Vetor& vector)
	{
		T value(0);
		for(auto i = 0; i < N; i++)
			value += mInitList[i] * vector.mInitList[i];
		return value;
	}

	// multiplicacao com escalar
	Vetor& operator*(T value)
	{
		for(auto i = 0; i < N; i++)
			mInitList[i] *= value;
		return *this;
	}

	// retorno do vetor b para produto vetorial na forma intermediaria
	MeioDoProdutoVetorial operator*()
	{
		return MeioDoProdutoVetorial(*this);
	}

	// produto vetorial
	Vetor operator*(const MeioDoProdutoVetorial& vector)
	{
		Vetor<3, T> result;
		switch(N)
		{
			case 2:
				result.mInitList.push_back(mInitList[0]*vector.mList[1] - mInitList[1]*vector.mList[0]);
				result.mInitList[0] = 0;
				result.mInitList[1] = 0;
				break;
			case 3:
				result.mInitList[0] = mInitList[1] * vector.mList[2] - mInitList[2] * vector.mList[1];
				result.mInitList[1] = mInitList[2] * vector.mList[0] - mInitList[0] * vector.mList[2];
				result.mInitList[2] = mInitList[0] * vector.mList[1] - mInitList[1] * vector.mList[0];
				break;
		}
		return result;
	}

	// divisao com escalar
	Vetor& operator/(T value)
	{
		for(auto i = 0; i < N; i++)
			mInitList /= value;
		return *this;
	}

	// adicao com vetor
	Vetor& operator+(const Vetor& vector)
	{
		for(auto i = 0; i < N; i++)
			mInitList[i] += vector.mInitList[i];
		return *this; 
	}

	// subtracao de vetor
	Vetor& operator-(const Vetor& vector)
	{
		for(auto i = 0; i < N; i++)
			mInitList[i] -= vector.mInitList[i];
		return *this;
	}

	// print
	void print(ostream& stream) const
	{
		for(auto item : mInitList)
			stream << item << " ";
	}

private:

	// vetor com conteudo do initializer_list
	vector<T> mInitList;

};

// overload do stream de saida
template<int N, typename T>
ostream& operator<<(ostream& stream, const Vetor<N,T>& vector)
{
	vector.print(stream);
	return stream;
}

// multiplicacao do tipo T com vetor
template<int N, typename T>
auto operator*(T value, Vetor<N,T>& vector)
{
	return vector * value;
}
