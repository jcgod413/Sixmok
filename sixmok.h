#include <iostream>
using namespace std;

#define BOARD_SIZE 19

enum Player {
	empty = 0,
	playerA = 1,
	playerB = 2
};

enum Dir_Vertical	{
	top = -1,
	remain = 0,
	down = 1
};
enum Dir_Horizontal	{
	left = -1,
	right = 1
};

class Sixmok
{
public:
	Sixmok();
	void play();
	void stop();
	void init();
	void printBoard();
	void reset();
	void input();
	void nextTurn();

private:
	// 판의 그림을 담고있는 배열
	string board[BOARD_SIZE][BOARD_SIZE];
	// 돌의 위치를 나타내는 배열
	int move[BOARD_SIZE][BOARD_SIZE];
	// 현재 게임이 실행중인지를 나타내는 변수
	bool isPlay;
	// 현재 차례의 Player
	Player nowTurn;
	// 현재 수를 나타내는 변수
	int count;
};
