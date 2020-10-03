#include "Sanke.h"

void GotoXY(int x, int y)
{
	// 更新光标位置 
	COORD pos;
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hOutput, pos);
	// 隐藏光标 
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = FALSE;
	cursor.dwSize = sizeof(cursor);
	SetConsoleCursorInfo(hOutput, &cursor);
}

void Snake::Tick() {
	Sleep(100);
	timer++;
	if (timer == 5)
		Move(), timer = 0;
}

void Snake::Move() {
	int nx = SnakeHead->x, ny = SnakeHead->y;
	switch (direction)
	{
	case UP:
		nx--;	break;
	case DOWN:
		nx++;	break;
	case LEFT:
		ny--;	break;
	case RIGHT:
		ny++;	break;
	}
	if (mp.GetTag(nx, ny) == WALL || mp.GetTag(nx, ny) == SNAKE) {
		life = false;
		return;
	}
	Node* TempBody = new Node(nx, ny);
	TempBody->nex = SnakeHead;
	SnakeHead->pre = TempBody;
	SnakeHead = TempBody;
	if (mp.GetTag(nx, ny) == FOOD) {
		mp.PrintSnakeBody(nx, ny);
		mp.CreateFood();
		return;
	}
	mp.PrintSnakeBody(nx, ny);
	mp.FreeCell(SnakeTail->x, SnakeTail->y);
	SnakeTail = SnakeTail->pre;
	delete SnakeTail->nex;
}

Snake::Snake() {
	timer = 1;	timer_mod = 100000000;
	SnakeHead = new Node(15, 15);
	SnakeHead->nex = SnakeTail = new Node(15, 14);
	SnakeTail->pre = SnakeHead;
	mp.PrintSnakeBody(15, 15);
	mp.PrintSnakeBody(15, 14);
	life = true;
	direction = RIGHT;
	mp.CreateFood();
}

Snake::~Snake() {
	Node* temp;
	while (SnakeHead <= SnakeTail) {
		temp = SnakeHead->nex;
		delete SnakeHead;
		SnakeHead = temp;
	}
}