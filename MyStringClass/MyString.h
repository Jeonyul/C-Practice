#pragma once
#include <iostream>
using std::ostream;
class MyString
{
	friend ostream& operator<<(ostream& os, MyString& str);
public:
	MyString();
	MyString(const char str[]);
	MyString(const MyString& str);
	int GetLength() { return mLength; }
	char& operator[](const int index);
	MyString& operator=(const MyString& str);
private:
	char* mStr;
	int mLength;
};
