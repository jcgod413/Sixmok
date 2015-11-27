#include <iostream>
using namespace std;

#define BOARD_SIZE 19

enum Player {
	empty = 0,
	playerA = 1,
	playerB = 2
};

enum Direction	{
	Top,
	Right_Top,
	Right,
	Right_Down,
	Down,
	Left_Down,
	Left,
	Left_Top
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
	void playerInput();
	void computerInput();
	void nextTurn();
	void findConnection();
	void calculateWeight();
	void moveStone(int x, int y);
	void findPosition(int &x, int &y);
	int recursiveCount(int x, int y, int cnt, int dir);

private:
	// 판의 그림을 담고있는 배열
	string board[BOARD_SIZE][BOARD_SIZE];
	// 돌의 위치를 나타내는 배열
	int move[BOARD_SIZE][BOARD_SIZE];
	// 판에서 유망함을 나타내는 배열
	int promising[BOARD_SIZE][BOARD_SIZE];
	// 판에서 상대편의 돌의 유망함을 나타내는 배열
	int danger[BOARD_SIZE][BOARD_SIZE];
	// 현재 게임이 실행중인지를 나타내는 변수
	bool isPlay;
	// 현재 차례의 Player
	Player nowTurn;
	// 현재 수의 번호를 나타내는 변수
	int number;
	// 8방향의 값을 나타내는 배열
	int direction[8][2] = { {-1, 0}, {-1, 1}, {0, 1},  {1, 1},
					  {1, 0},  {1, -1}, {0, -1}, {-1, -1} };
	// 연속적인 돌의 조합을 담는 배열
	int consecutiveMove[10];
};
