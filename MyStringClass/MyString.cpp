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
	mStr[length] = NULL;
}
MyString::MyString(int length, char ch)
{
	mStr = new char[length + 1];
	for (int i = 0; i < length; i++)
	{
		mStr[i] = ch;
	}
	mStr[length] = NULL;
}
MyString::MyString(const MyString& str)
	: mStr{ nullptr }, mLength{ 0 }
{
	mStr = new char[str.mLength + 1];
	for (int i = 0; i < str.mLength; i++)
	{
		mStr[i] = str.mStr[i];
	}
	mStr[str.mLength] = NULL;
	mLength = str.mLength;
}
MyString::~MyString()
{
	delete mStr;
}
//int MyString::FindFirstOccur(const char str[])
//{
//	for (int i = 0; i < mLength; i++)
//	{
//		
//	}
//	return;
//}
//int MyString::FindFromIndex(const char str[], int index)
//{
//	return;
//}
char& MyString::operator[](const unsigned int index)
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
	mStr[str.mLength] = NULL;
	mLength = str.mLength;
	return *this;
}
MyString& MyString::operator+=(const MyString& str)
{
	int tempLength = mLength + str.mLength;
	char* pTempStr = new char[tempLength + 1];
	for (int i = 0; i < mLength; i++)
	{
		*(pTempStr + i) = mStr[i];
	}
	int i = 0;
	for (int j = mLength; j < tempLength; j++)
	{
		pTempStr[j] = str.mStr[i];
		i++;
	}
	pTempStr[tempLength] = NULL;
	delete mStr;
	mStr = pTempStr;
	pTempStr = nullptr;
	mLength = tempLength;
	return *this;
}
ostream& operator<<(ostream& os, MyString& str)
{
	if (str.mLength > 0)
	{
		for (int i = 0; str.mStr[i] != NULL; i++)
		{
			os << str.mStr[i];
		}
	}
	return os;
}