#include <iostream>

int main()
{
	return 0;
}

//

using namespace std;

class PilhaInt
{

public:

	PilhaInt(int capacity = 10) : mCurrentIndex(0), mCapacity(capacity)
	{
		mStack = (int*) malloc(sizeof(int) * mCapacity);

		for(int i = 0; i < capacity; i++)
			mStack[i] = 0;
	}

	PilhaInt(const PilhaInt& stack)
	{
		mStack = (int*) malloc(sizeof(int) * stack.mCapacity);

		for(mCurrentIndex = 0; mCurrentIndex < stack.mCapacity; mCurrentIndex++)
			mStack[mCurrentIndex] = stack.mStack[mCurrentIndex];
	}

	~PilhaInt()
	{
		free(mStack);
	}

	void empilha(int value)
	{
		if(mCurrentIndex >= capacidade())
			redimensiona(2 * capacidade());
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

	int capacidade()
	{
		return mCapacity;
	}

	void redimensiona(int newCapacity)
	{
		if(newCapacity < capacidade())
		{
			for(int i = capacidade(); i > newCapacity; i--)
				desempilha();
			mCurrentIndex = newCapacity;
		}

		else {
			mStack = (int*) realloc(mStack, newCapacity * sizeof(int));

			for(int i = capacidade(); i > newCapacity; i--)
				mStack[i] = 0;
		}

		mCapacity = newCapacity;
	}

	const PilhaInt& operator=(const PilhaInt& stack)
	{
		redimensiona(stack.mCapacity);

		for(mCurrentIndex = 0; mCurrentIndex < capacidade(); mCurrentIndex++)
			mStack[mCurrentIndex] = stack.mStack[mCurrentIndex];

		return *this;
	}

	PilhaInt& operator<<(int value)
	{
		empilha(value);
		return *this;
	}

private:

	int *mStack;

	int mCurrentIndex;

	int mCapacity;

};