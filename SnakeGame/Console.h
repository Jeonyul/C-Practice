#pragma once
constexpr int WIDTH = 55; // index: 0~54, playable map index: 1~52
constexpr int HEIGHT = 21; // index: 0~20, playable map index: 1~19

void Initial();

void MoveCursor(int x, int y);

//void ClearScreen();