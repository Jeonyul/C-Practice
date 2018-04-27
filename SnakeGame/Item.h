#pragma once
#include "Console.h"
class Item
{
public:
	Item();
	char GetShape() const { return SHAPE; }
	int GetX() const { return mX; }
	int GetY() const { return mY; }
	bool GetIsShown() const { return mbIsShown; }

	void SetX(int x) { mX = x; }
	void SetY(int y) { mY = y; }
	void SetIsShown(bool b) { mbIsShown = b; }
private:
	const char SHAPE = '&';
	int mX;
	int mY;
	bool mbIsShown;
};
Item::Item()
	:mX{ 0 }, mY{ 0 }, mbIsShown{ false }
{
}