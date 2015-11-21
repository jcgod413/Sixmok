#include "sixmok.h"

Sixmok::Sixmok()
{
	initBoard();
	printBoard();
}

void Sixmok::initBoard()
{
	// 모서리
    board[0][0] = "┌", 
    board[0][BOARD_SIZE-1] = "┐", 
    board[BOARD_SIZE-1][0] = "└", 
    board[BOARD_SIZE-1][BOARD_SIZE-1] = "┘";
 
 	// 몸통
    for(int i=1; i<BOARD_SIZE-1; i++)
    {
        board[0][i] = "┬";
        board[i][0] = "├";
        board[i][BOARD_SIZE-1] = "┤";
        board[BOARD_SIZE-1][i] = "┴";
        
        for(int j=1; j<18; j++)
        {
            board[i][j] = "┼";
        }
    }
}

void Sixmok::printBoard()
{
	system("clear");
	for(int i=0; i<BOARD_SIZE; i++)	{
		for(int j=0; j<BOARD_SIZE; j++)	{
			switch( move[i][j])	{
				case EMPTY:		cout << board[i][j];	break;
				case playerA:	cout << "○";			break;
				case playerB:	cout << "●";			break;
			}		
		}
			
		cout << " " << i << endl;
	}
	cout << "0123456789111111111" << endl;
	cout << "          012345678" << endl << endl;
}

void Sixmok::reset()
{
	initBoard();
	memset(move, 0, BOARD_SIZE*BOARD_SIZE);
}

int Sixmok::input(Player player, int x, int y)
{
	if( move[y][x] == playerA
		|| move[y][x] == playerB )	{
		// 이미 돌이 존재. 에러메시지 1 return
		return 1;	
	}
	else if( x < 1 || x > BOARD_SIZE-1 
			|| y < 1 || y > BOARD_SIZE-1 )	{
		// 허용 범위가 넘어섬. 에러메시지 2 return
		return 2;
	}
	
	board[y][x] = player;
	return 0;	// 정상 수행
}