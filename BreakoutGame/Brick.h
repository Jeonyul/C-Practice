#pragma once

class Brick
{
public:
	Brick();
	int GetX() const { return mX; }
	int GetY() const { return mY; }
	bool GetIsLive() const {return mbIsLive;}
	void SetX(int x) { mX = x; }
	void SetY(int y) { mY = y; }
	void SetIsLive(bool b) { mbIsLive = b; }
private:
	int mX;
	int mY;
	bool mbIsLive;
};
Brick::Brick()
	:mX{ 0 }, mY{ 0 }, mbIsLive{ true }
{
}

class BrickNormal : public Brick
{
public:
	BrickNormal();
	int GetSize() const { return mSize; }
	char operator[](const int index) { return SHAPE[index]; }
private:
	static const int mSize = 2;
	const char SHAPE[mSize + 1];
};
BrickNormal::BrickNormal()
	: SHAPE{ "¢Ë" }
{
}
//class BrickHard : public Brick
//{
//	static const int mSize = 2;
//	const char SHAPE[mSize + 1] = "¢Ã";
//};
//class BrickItem : public Brick
//{
//private:
//	static const int mSize = 2;
//	const char SHAPE[mSize + 1] = "¡á";
//};