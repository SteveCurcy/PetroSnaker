#pragma once

#include <time.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>

#define SPACE	1
#define FOOD	2
#define SNAKE	3
#define WALL	4

#define UP		72
#define DOWN	80
#define LEFT	75
#define RIGHT	77

void GotoXY(int x, int y);

struct Node {
	int x, y;
	Node* nex, * pre;
	Node(int X, int Y) { x = X; y = Y; nex = pre = NULL; }
};

template <int row, int col>
class Map {
	char maze[row][col];
	void PrintWall(int x, int y);
public:
	Map();
	void CreateFood();
	void PrintSnakeBody(int x, int y);
	void FreeCell(int x, int y);
	char GetTag(int x, int y) {
		return maze[x][y];
	}
	~Map() { GotoXY(0, col + 2); };
};

class Snake {
	Node* SnakeHead, * SnakeTail;
	Map<30, 30> mp;
	char direction;
	bool life;
	int timer, timer_mod;
public:
	Snake();
	~Snake();
	void Move();
	bool IsAlive() {
		return life;
	}
	void TurnAround(char Tag) {
		if (Tag == UP && direction != DOWN)	direction = UP;
		else if (Tag == DOWN && direction != UP)	direction = DOWN;
		else if (Tag == LEFT && direction != RIGHT)	direction = LEFT;
		else if (Tag == RIGHT && direction != LEFT)	direction = RIGHT;
	}
	void Tick();
	void ResetTimer() {
		timer = 0;
	}
};

template <int row, int col>
Map<row, col>::Map() {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (i == 0 || i == row - 1 || j == 0 || j == col - 1) {
				this->maze[i][j] = WALL;
				PrintWall(i, j);
			}
			else
				this->maze[i][j] = SPACE;
		}
	}
}

template <int row, int col>
void Map<row, col>::FreeCell(int x, int y) {
	GotoXY(y << 1, x);
	maze[x][y] = SPACE;
	printf("  ");
}

template <int row, int col>
void Map<row, col>::PrintSnakeBody(int x, int y) {
	/* ×ø±ê×ª»» */
	GotoXY(y << 1, x);
	maze[x][y] = SNAKE;
	printf("¡ö");
}

template <int row, int col>
void Map<row, col>::PrintWall(int x, int y) {
	GotoXY(y << 1, x);
	printf("%c ", 1);
}

template <int row, int col>
void Map<row, col>::CreateFood() {
	srand((unsigned)time(NULL));
	int x = rand() % row;
	int y = rand() % col;

	while (maze[x][y] != SPACE) {
		x = rand() % row;
		y = rand() % col;
	}

	maze[x][y] = FOOD;
	GotoXY(y << 1, x);
	printf("¡Ñ");
}