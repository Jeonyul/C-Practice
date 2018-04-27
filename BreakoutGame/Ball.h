#pragma once

class Ball
{
public:
	Ball();
	void SetX(const int x) { mX = x; }
	void SetY(const int y) { mY = y; }
	void SetDirUp(bool b) { mbDirUp = b; }
	void SetDirDown(bool b) { mbDirDown = b; }
	void SetDirRight(bool b) { mbDirRight = b; }
	void SetDirLeft(bool b) { mbDirLeft = b; }

	int GetX() const { return mX; }
	int GetY() const { return mY; }
	char GetShape() const { return SHAPE; }
	bool GetDirUp() { return mbDirUp; }
	bool GetDirDown() { return mbDirDown; }
	bool GetDirRight() { return mbDirRight; }
	bool GetDirLeft() { return mbDirLeft; }
	void Move();

private:
	const char SHAPE = 'o';
	int mX;
	int mY;
	bool mbIsLive;
	bool mbDirUp;
	bool mbDirDown;
	bool mbDirRight;
	bool mbDirLeft;
};
Ball::Ball()
	:mX{ 78 }, mY{ 1 }, mbIsLive{ true },
	mbDirUp{ false }, mbDirDown{ true }, mbDirRight{ false }, mbDirLeft{ true }
{
}
void Ball::Move()
{
	if (mbDirUp)
	{
		mY--;
	}
	if (mbDirDown)
	{
		mY++;
	}
	if (mbDirRight)
	{
		mX++;
	}
	if (mbDirLeft)
	{
		mX--;
	}
}