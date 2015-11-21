#include <iostream>
using namespace std;

#define BOARD_SIZE 19

class Sixmok
{
public:
	Sixmok();
	void initBoard();
	void printBoard();

private:
	string board[BOARD_SIZE][BOARD_SIZE];
};
