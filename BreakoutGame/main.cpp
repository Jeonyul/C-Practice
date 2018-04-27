#include <iostream>
#include <Windows.h>
#include "Ball.h"
#include "Bar.h"
#include "Brick.h"
#include "Console.h"

void SetInitialBricks();
void CheckBrickCrash();
void CheckCrash();
void Draw();

char screen[HEIGHT][WIDTH];
const int MAX_BRICKS = 185;
BrickNormal bricks[MAX_BRICKS];
Ball ball;
Bar bar;
int score = 0;

int main()
{
	Initial();
	SetInitialBricks();
	while (true)
	{
		bar.Move();
		ball.Move();
		CheckCrash();
		Draw();
		Sleep(90);
	}

	return 0;
}

// fucntions
void SetInitialBricks()
{
	int initialX = 3;
	int initialY = 2;
	int x = initialX;
	int y = initialY;
	for (int i = 0; i < MAX_BRICKS; i++)
	{
		if (i % 37 == 0)
		{
			x = initialX;
			y++;
		}
		bricks[i].SetX(x);
		bricks[i].SetY(y);
		x += 2;
	}
}
void SetMapOnScreen()
{

	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH - 2 + 1; x++)
		{
			if (x == 0 || x == WIDTH - 2)
			{
				screen[y][x] = '|';
			}
			if (y == 0)
			{
				screen[y][x] = '-';
			}
			if (y == HEIGHT - 1)
			{
				screen[y][x] = '^';
			}
		}
	}
	screen[0][0] = '+';
	screen[0][WIDTH - 2] = '+';
}
void SetBricksOnScreen()
{
	for (int i = 0; i < MAX_BRICKS; i++)
	{
		if (bricks[i].GetIsLive() == true)
		{
			int x = bricks[i].GetX();
			int y = bricks[i].GetY();
			for (int j = 0; j < bricks[i].GetSize(); j++)
			{
				screen[y][x] = bricks[i][j];
				x++;
			}
		}
	}
}
void Draw()
{
	// Clear screen
	for (int i = 0; i < HEIGHT; i++)
	{
		memset(screen[i], ' ', WIDTH - 2);
		screen[i][WIDTH - 1] = NULL;
	}

	SetMapOnScreen();
	SetBricksOnScreen();

	// Set ball on screen
	screen[ball.GetY()][ball.GetX()] = ball.GetShape();
	// Set Bar on screen
	for (int i = 0; i < bar.GetSize(); i++)
	{
		screen[bar.GetY()][bar.GetX() + i] = bar.GetShape();
	}
	// Draw screen
	for (int i = 0; i < HEIGHT; i++)
	{
		MoveCursor(0, i);
		printf("%s", screen[i]);
	}
	MoveCursor(0, HEIGHT);
	printf("[ SCORE ] : %d", score);
}

void CheckCrash()
{
	// ball - bar
	if (ball.GetY() == bar.GetY() - 1)
	{
		if ((ball.GetX() >= bar.GetX()) && (ball.GetX() <= bar.GetX() + bar.GetSize() - 1))
		{
			ball.SetDirUp(true);
			ball.SetDirDown(false);
		}
	}
	// bar-frame
	if (bar.GetX() <= 0)
	{
		bar.SetX(1);
	}
	if (bar.GetX() >= WIDTH - 2 - (bar.GetSize() - 1))
	{
		bar.SetX(WIDTH - 3 - (bar.GetSize() - 1));

	}
	// ball - frame
	if (ball.GetX() < 2)
	{
		ball.SetDirLeft(false);
		ball.SetDirRight(true);
	}
	if (ball.GetX() > WIDTH - 2 - 2)
	{
		ball.SetDirRight(false);
		ball.SetDirLeft(true);
	}
	if (ball.GetY() < 2)
	{
		ball.SetDirUp(false);
		ball.SetDirDown(true);
	}
	if (ball.GetY() > HEIGHT - 3)
	{
		ball.SetDirDown(false);
		ball.SetDirUp(true);
	}

	// ball-bricks
	CheckBrickCrash();
}

void CheckBrickCrash()
{
	bool IsDone = false;
	// Check sides
	for (int i = 0; i < MAX_BRICKS; i++)
	{
		if (bricks[i].GetIsLive() == true)
		{
			// top side
			if ((bricks[i].GetX() == ball.GetX() || bricks[i].GetX() + 1 == ball.GetX()) && bricks[i].GetY() - 1 == ball.GetY())
			{
				if (ball.GetDirDown() == true)
				{
					ball.SetDirDown(false);
					ball.SetDirUp(true);

					bricks[i].SetIsLive(false);
					bricks[i].SetX(0);
					bricks[i].SetY(0);

					IsDone = true;
					score += 100;
				}
			}
			// bottom side
			else if ((bricks[i].GetX() == ball.GetX() || bricks[i].GetX() + 1 == ball.GetX()) && bricks[i].GetY() + 1 == ball.GetY())
			{
				if (ball.GetDirUp() == true)
				{
					ball.SetDirUp(false);
					ball.SetDirDown(true);

					bricks[i].SetIsLive(false);
					bricks[i].SetX(0);
					bricks[i].SetY(0);

					IsDone = true;
					score += 100;
				}
			}
			// left side
			else if (bricks[i].GetX() - 1 == ball.GetX() && bricks[i].GetY() == ball.GetY())
			{
				if (ball.GetDirRight() == true)
				{
					ball.SetDirRight(false);
					ball.SetDirLeft(true);

					bricks[i].SetIsLive(false);
					bricks[i].SetX(0);
					bricks[i].SetY(0);

					IsDone = true;
					score += 100;
				}
			}
			// right side
			else if (bricks[i].GetX() + 2 == ball.GetX() && bricks[i].GetY() == ball.GetY())
			{
				if (ball.GetDirLeft() == true)
				{
					ball.SetDirLeft(false);
					ball.SetDirRight(true);

					bricks[i].SetIsLive(false);
					bricks[i].SetX(0);
					bricks[i].SetY(0);

					IsDone = true;
					score += 100;
				}
			}
		}
	}

	// Check corners
	if (IsDone == false)
	{
		for (int i = 0; i < MAX_BRICKS; i++)
		{
			if (bricks[i].GetIsLive() == true)
			{
				// top-left corner
				if (bricks[i].GetX() - 1 == ball.GetX() && bricks[i].GetY() - 1 == ball.GetY())
				{
					if (ball.GetDirDown() == true && ball.GetDirRight() == true)
					{
						ball.SetDirDown(false);
						ball.SetDirRight(false);
						ball.SetDirUp(true);
						ball.SetDirLeft(true);

						bricks[i].SetIsLive(false);
						bricks[i].SetX(0);
						bricks[i].SetY(0);

						score += 100;
					}
				}
				// top-right corner
				if (bricks[i].GetX() + 2 == ball.GetX() && bricks[i].GetY() - 1 == ball.GetY())
				{
					if (ball.GetDirDown() == true && ball.GetDirLeft() == true)
					{
						ball.SetDirDown(false);
						ball.SetDirLeft(false);
						ball.SetDirUp(true);
						ball.SetDirRight(true);

						bricks[i].SetIsLive(false);
						bricks[i].SetX(0);
						bricks[i].SetY(0);

						score += 100;
					}
				}
				// right-bottom corner
				if (bricks[i].GetX() + 2 == ball.GetX() && bricks[i].GetY() + 1 == ball.GetY())
				{
					if (ball.GetDirUp() == true && ball.GetDirLeft() == true)
					{
						ball.SetDirUp(false);
						ball.SetDirLeft(false);
						ball.SetDirDown(true);
						ball.SetDirRight(true);

						bricks[i].SetIsLive(false);
						bricks[i].SetX(0);
						bricks[i].SetY(0);

						score += 100;
					}
				}
				// bottom-left corner
				if (bricks[i].GetX() - 1 == ball.GetX() && bricks[i].GetY() + 1 == ball.GetY())
				{
					if (ball.GetDirUp() == true && ball.GetDirRight() == true)
					{
						ball.SetDirUp(false);
						ball.SetDirRight(false);
						ball.SetDirDown(true);
						ball.SetDirLeft(true);

						bricks[i].SetIsLive(false);
						bricks[i].SetX(0);
						bricks[i].SetY(0);

						score += 100;
					}
				}
			}
		}
	}
}