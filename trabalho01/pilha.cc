#include <iostream>

int main()
{
	return 0;
}

//

using namespace std;

#define MAX_PILHA 1024

class PilhaInt
{

public:

	PilhaInt() : mCurrentIndex(0)
	{
		for(int i = 0; i < MAX_PILHA; i++)
			mStack[i] = 0;
	}

	void empilha(int value)
	{
		if(mCurrentIndex < MAX_PILHA)
			mStack[mCurrentIndex++] = value;
	}

	int desempilha()
	{
		//if(mCurrentIndex > 0)
			return mStack[--mCurrentIndex];
		
	}

	void print(ostream& stream)
	{
		stream << "[";
		for(int i = 0; i < mCurrentIndex; i++)
		{
			stream << " " << mStack[i];
			if(i < mCurrentIndex - 1) stream << ",";
		}
		stream << " ]";
	}

	const PilhaInt& operator=(const PilhaInt& stack)
	{
		mCurrentIndex = stack.mCurrentIndex;

		for(int i = 0; i < mCurrentIndex; i++)
			mStack[i] = stack.mStack[i];

		return *this;
	}

	PilhaInt& operator<<(int value)
	{
		empilha(value);
		return *this;
	}

private:

	int mStack[MAX_PILHA];

	int mCurrentIndex;

};