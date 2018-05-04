#pragma once
template<typename T>
class MyVector
{
public:
	MyVector();
	~MyVector() { delete[] mArr; }
	int GetCapacity() const { return mCapacity; }
	int GetSize() const { return mSize; }
	void Pushback(const T& d);
	//void Popback();
	T& operator[](const unsigned int index) { return mArr[index]; }
private:
	T* mArr;
	int mCapacity;
	int mSize;
};
template<typename T>
MyVector<T>::MyVector()
	: mArr{ nullptr }, mCapacity{ 0 }, mSize{ 0 }
{
}

template<typename T>
void MyVector<T>::Pushback(const T& d)
{
	if (mSize + 1 > mCapacity)
	{
		mCapacity++;
		T* temp = new T[mCapacity];
		for (int i = 0; i < mSize; i++)
		{
			temp[i] = mArr[i];
		}
		temp[mSize] = d;
		mSize++;
		delete[] mArr;
		mArr = temp;
	}
	else
	{
		mArr[mSize] = d;
		mSize++;
	}
}