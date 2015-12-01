#include <iostream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "MySocket.h"

using namespace std;

#define BOARD_SIZE 17
#define CRITICAL 99999

enum Player {
	empty = 0,
	playerA = 1,
	playerB = 2
};
enum gameMode	{
	Server=1,
	Client=2
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
enum Participant	{
	People=1,
	Computer=2
};

typedef struct{
	int x,y;
	int win;//0:game running, 1:sever win ,2:client win
	int turn;//1:sever turn ,2:client turn
}GAME_DATA;

class Sixmok
{
public:
	Sixmok(int, int);
	void play();
	void stop();
	void init();
	void printBoard();
	void reset();
	void playerInput();
	void playerInput2();
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
	// 연속적인 돌의 조합을 담는 배열
	int consecutiveMove[12];
	int gameMode;
	int participant;
	GAME_DATA gameData;
};
