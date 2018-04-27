#include "MyString.h"

MyString::MyString()
	: mStr{ nullptr }, mLength{ 0 }
{
}
MyString::MyString(const char str[])
	: mStr{ nullptr }, mLength{ 0 }
{
	int length{ 0 };
	int i{ 0 };
	while (str[i] != NULL)
	{
		length++;
		i++;
	}
	mLength = length;
	mStr = new char[length + 1];
	for (int i = 0; i < length; i++)
	{
		mStr[i] = str[i];
	}
	mStr[length + 1] = NULL;
}
MyString::MyString(const MyString& str)
	: mStr{ nullptr }, mLength{ 0 }
{
	mStr = new char[str.mLength + 1];
	for (int i = 0; i < str.mLength; i++)
	{
		mStr[i] = str.mStr[i];
	}
	mStr[str.mLength + 1] = NULL;
	mLength = str.mLength;
}
char& MyString::operator[](const int index)
{
	return *(mStr + index);
}
MyString& MyString::operator=(const MyString& str)
{
	delete mStr; // TODO: when trying assignment to self
	mStr = new char[str.mLength + 1];
	for (int i = 0; i < str.mLength; i++)
	{
		mStr[i] = str.mStr[i];
	}
	mStr[str.mLength + 1] = NULL;
	mLength = str.mLength;
	return *this;
}
ostream& operator<<(ostream& os, MyString& str)
{
	for (int i = 0; str.mStr[i] != NULL; i++)
	{
		os << str.mStr[i];
	}
	return os;
}