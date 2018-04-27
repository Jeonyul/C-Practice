#pragma once
#include <Windows.h>
#include "Console.h"

const short SHIFTED = (short)0x8000;
enum class eDirection { Up, Down, Right, Left };

class SnakePart
{
public:
	SnakePart();
	void SetX(const int x) { mX = x; }
	void SetY(const int y) { mY = y; }
	void SetPastX(const int taleX) { mTaleX = taleX; }
	void SetPastY(const int taleY) { mTaleY = taleY; }
	void SetIsLive(bool b) { mbIsLive = b; }

	int GetX() const { return mX; }
	int GetY() const { return mY; }
	int GetPastX() const { return mTaleX; }
	int GetPastY() const { return mTaleY; }
	bool GetIsLive() const { return mbIsLive; }
private:
	const char SHAPE = '*';
	int mX;
	int mY;
	int mTaleX;
	int mTaleY;
	bool mbIsLive;
};
SnakePart::SnakePart()
	:mX{ 0 }, mY{ 0 }, mTaleX{ 0 }, mTaleY{ 0 }, mbIsLive{ false }
{
}

class Snake
{
public:
	Snake();
	char GetShapeHead() const { return SHAPE_HEAD; }
	char GetShapeTale() const { return SHAPE_TALE; }
	int GetLength() const { return mLength; }
	void Move();
	void IncrementTale();
	void CutTales();
	SnakePart& operator[](const int position) { return mBody[position]; }
private:
	const char SHAPE_HEAD = '@';
	const char SHAPE_TALE = '*';
	static const int MAX_TALE = 500;
	SnakePart mBody[MAX_TALE];
	eDirection mDirection;
	int mLength;
};
Snake::Snake()
	:mDirection{ eDirection::Left }, mLength{ 2 }
{	
	mBody[0].SetX(WIDTH / 2);
	mBody[0].SetY(HEIGHT / 2);
	mBody[0].SetPastX(mBody[0].GetX());
	mBody[0].SetPastY(mBody[0].GetY());
	mBody[0].SetIsLive(true);
	for (int i = 1; i <= mLength; i++)
	{
		mBody[i].SetX(mBody[i - 1].GetPastX() + 1);
		mBody[i].SetY(mBody[i - 1].GetPastY());
		mBody[i].SetPastX(mBody[i].GetX());
		mBody[i].SetPastY(mBody[i].GetY());
		mBody[i].SetIsLive(true);
	}
}
void Snake::Move()
{
	if (mDirection != eDirection::Down && GetKeyState(VK_UP) & SHIFTED)
	{
		mDirection = eDirection::Up;
	}
	else if (mDirection != eDirection::Up && GetKeyState(VK_DOWN) & SHIFTED)
	{
		mDirection = eDirection::Down;
	}
	else if (mDirection != eDirection::Left && GetKeyState(VK_RIGHT) & SHIFTED)
	{
		mDirection = eDirection::Right;
	}
	else if (mDirection != eDirection::Right && GetKeyState(VK_LEFT) & SHIFTED)
	{
		mDirection = eDirection::Left;
	}
	switch (mDirection)
	{
	case eDirection::Up:
		mBody[0].SetPastX(mBody[0].GetX());
		mBody[0].SetPastY(mBody[0].GetY());
		mBody[0].SetY(mBody[0].GetY() - 1);
		break;
	case eDirection::Down:
		mBody[0].SetPastX(mBody[0].GetX());
		mBody[0].SetPastY(mBody[0].GetY());
		mBody[0].SetY(mBody[0].GetY() + 1);
		break;
	case eDirection::Right:
		mBody[0].SetPastX(mBody[0].GetX());
		mBody[0].SetPastY(mBody[0].GetY());
		mBody[0].SetX(mBody[0].GetX() + 1);
		break;
	case eDirection::Left:
		mBody[0].SetPastX(mBody[0].GetX());
		mBody[0].SetPastY(mBody[0].GetY());
		mBody[0].SetX(mBody[0].GetX() - 1);
		break;
	default:
		break;
	}
	for (int i = 1; i <= mLength; i++)
	{
		mBody[i].SetPastX(mBody[i].GetX());
		mBody[i].SetPastY(mBody[i].GetY());
		mBody[i].SetX(mBody[i - 1].GetPastX());
		mBody[i].SetY(mBody[i - 1].GetPastY());
	}
}
void Snake::IncrementTale()
{
	if (mLength < MAX_TALE)
	{
		mBody[mLength + 1].SetIsLive(true);
		mBody[mLength + 1].SetX(mBody[mLength].GetX());
		mBody[mLength + 1].SetY(mBody[mLength].GetY());
		mLength++;
	}
}
void Snake::CutTales()
{

}
