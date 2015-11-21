#include <iostream>
using namespace std;

#define BOARD_SIZE 18

class Sixmok
{
public:
	Sixmok();
	void printBoard();

private:
	string board[BOARD_SIZE][BOARD_SIZE];
};

int main()
{

}

Sixmok::Sixmok()
{
	printBoard();
}

void Sixmok::printBoard()
{
	// 모서리
    table[0][0]="┌", table[0][18]="┐", table[18][0]="└", table[18][18]="┘";
 
    for(int i=1; i<18; i++)
    {
        table[0][i]="┬";
        table[i][0]="├";
        table[i][18]="┤";
        table[18][i]="┴";
        
        for(int j=1; j<18; j++)
        {
            table[i][j]="┼";
        }
    }
}
