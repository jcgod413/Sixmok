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
	// ���� �׸��� ����ִ� �迭
	string board[BOARD_SIZE][BOARD_SIZE];
	// ���� ��ġ�� ��Ÿ���� �迭
	int move[BOARD_SIZE][BOARD_SIZE];
	// �ǿ��� �������� ��Ÿ���� �迭
	int promising[BOARD_SIZE][BOARD_SIZE];
	// �ǿ��� ������� ���� �������� ��Ÿ���� �迭
	int danger[BOARD_SIZE][BOARD_SIZE];
	// ���� ������ ������������ ��Ÿ���� ����
	bool isPlay;
	// ���� ������ Player
	Player nowTurn;
	// ���� ���� ��ȣ�� ��Ÿ���� ����
	int number;
	// �������� ���� ������ ��� �迭
	int consecutiveMove[12];
	int gameMode;
	int participant;
	GAME_DATA gameData;
};
