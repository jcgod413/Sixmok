#include <iostream>
using namespace std;

#define BOARD_SIZE 19

enum Player {
	EMPTY = 0,
	playerA = 1,
	playerB = 2
};

class Sixmok
{
public:
	Sixmok();
	void initBoard();
	void printBoard();
	void reset();

private:
	// 판의 그림을 담고있는 배열
	string board[BOARD_SIZE][BOARD_SIZE];
	// 돌의 위치를 나타내는 배열
	int move[BOARD_SIZE][BOARD_SIZE];
};
