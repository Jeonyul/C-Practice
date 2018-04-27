#pragma once
#include <Windows.h>

class Bar
{
public:
	Bar();
	char GetShape() const { return SHAPE; }
	int GetX() const { return mX; }
	int GetY() const { return mY; }
	int GetSize() const { return mSize; }

	void SetX(int x) { mX = x; }
	void Move();

private:
	const char SHAPE = '=';
	int mX;
	int mY;
	int mSize;
};

Bar::Bar()
	: mX{ 38 }, mY{ 20 }, mSize{ 7 }
{
}

const short SHIFTED = (short)0x8000;
void Bar::Move()
{
	if (GetKeyState(VK_RIGHT) & SHIFTED)
	{
		mX += 2;
	}
	if (GetKeyState(VK_LEFT) & SHIFTED)
	{
		mX -= 2;
	}
}