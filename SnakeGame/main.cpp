#include <ctime>
#include <iostream>
#include "Console.h"
#include "Item.h"
#include "Snake.h"

void SetItems();
void CheckCrash();
void Draw();

char screen[HEIGHT][WIDTH];
int score = 0;
int timer = 0;
int itemIndex = 0;
Snake snake;
constexpr int MAX_ITEM = 300;
Item items[MAX_ITEM];

int main()
{
	std::cout << "Press any key\n";
	getchar();
	srand(unsigned int(time(0)));
	Initial();
	while (true)
	{
		SetItems();
		snake.Move();
		CheckCrash();
		Draw();
		if (snake[0].GetIsLive() == false)
		{
			MoveCursor(WIDTH / 2 - 8, HEIGHT / 2);
			printf("### GAME OVER ###");
			Sleep(4000);
			break;
		}
		Sleep(100);
	}
	return 0;
}
void SetItems()
{
	if (itemIndex < MAX_ITEM && timer % 5 == 4)
	{
		items[itemIndex].SetX(rand() % (WIDTH - 4) + 1);
		items[itemIndex].SetY(rand() % (HEIGHT - 3) + 1);
		items[itemIndex].SetIsShown(true);
		itemIndex++;
	}
	timer++;
}
void CheckCrash()
{
	// head - wall
	if (snake[0].GetX() <= 0 || snake[0].GetX() >= WIDTH - 2 || snake[0].GetY() <= 0 || snake[0].GetY() >= HEIGHT - 1)
	{
		snake[0].SetIsLive(false);
	}
	// head - tails
	for (int i = 4; i <= snake.GetLength(); i++)
	{
		if (snake[0].GetX() == snake[i].GetX() && snake[0].GetY() == snake[i].GetY())
		{
			snake[0].SetIsLive(false);
		}
	}
	// head - items
	for (int i = 0; i < MAX_ITEM; i++)
	{
		if (snake[0].GetX() == items[i].GetX() && snake[0].GetY() == items[i].GetY())
		{
			snake.IncrementTale();
			snake.IncrementTale();
			snake.IncrementTale();
			snake.IncrementTale();
			snake.IncrementTale();
			snake.IncrementTale();
			snake.IncrementTale();
			snake.IncrementTale();
			snake.IncrementTale();
			snake.IncrementTale();
			items[i].SetIsShown(false);
			score += 100;
		}
	}
}
void Draw()
{
	// Clear the screen
	for (int i = 0; i < HEIGHT; i++)
	{
		memset(screen[i], ' ', WIDTH - 2);
		screen[i][WIDTH - 1] = NULL;
	}

	// Map on the screen
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH - 1; x++)
		{
			screen[y][x / 2 * 2] = '.';
		}
	}
	for (int i = 0; i < HEIGHT; i++)
	{
		screen[i][0] = '#';
		screen[i][WIDTH - 2] = '#';
	}
	for (int i = 0; i < WIDTH - 1; i++)
	{
		screen[0][i] = '#';
		screen[HEIGHT - 1][i] = '#';
	}

	// Snake on the screen
	screen[snake[0].GetY()][snake[0].GetX()] = snake.GetShapeHead();
	for (int i = 1; i <= snake.GetLength(); i++)
	{
		if (snake[i].GetIsLive())
		{
			screen[snake[i].GetY()][snake[i].GetX()] = snake.GetShapeTale();
		}
	}
	// Items on the screen
	for (int i = 0; i < MAX_ITEM; i++)
	{
		if (items[i].GetIsShown() == true)
		{
			screen[items[i].GetY()][items[i].GetX()] = items[i].GetShape();
		}

	}
	// Draw the screen
	for (int i = 0; i < HEIGHT; i++)
	{
		MoveCursor(0, i);
		printf("%s", screen[i]);
	}
	MoveCursor(0, HEIGHT);
	printf("SCORE: %d", score);
}