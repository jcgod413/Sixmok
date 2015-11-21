#include "sixmok.h"

Sixmok::Sixmok()
{
	init();
}

void Sixmok::init()
{
	isPlay = false;
	nowTurn = playerA;
	number = 1;

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

void Sixmok::play()
{
	isPlay = true;

	while( isPlay )	{
		// 판 그리기
		printBoard();	
		// 사용자로부터 돌의 입력 받기
		input();
		// 다음 차례로 변경
		nextTurn();
	}
}

void Sixmok::printBoard()
{
	string msg[2] = {"PlayerA", "PlayerB"};

	system("clear");
	for(int i=0; i<BOARD_SIZE; i++)	{
		for(int j=0; j<BOARD_SIZE; j++)	{
			switch( move[i][j])	{
				case empty:		cout << board[i][j];	break;
				case playerA:	cout << "○";			break;
				case playerB:	cout << "●";			break;
			}		
		}
			
		cout << " " << i;
		if( i < 10 )	{
			cout << "\t\t" << msg[i/5] << "의 " << (i % 5) + 2 << "개 연속 개수 " << consecutiveMove[i];
		}
		cout << endl;
	}
	cout << "0123456789111111111" << endl;
	cout << "          012345678" << endl << endl;

	if( consecutiveMove[4] == 1 )
	{
		cout << msg[0] << "승리!" << endl;
		stop();
	}
	else if( consecutiveMove[9] == 1 )
	{
		cout << msg[1] << "승리!" << endl;
		stop();
	}
}

void Sixmok::nextTurn()
{
	nowTurn = static_cast<Player>((static_cast<int>(nowTurn) % 2) + 1);
	number++;
}

void Sixmok::reset()
{
	init();
	memset(move, 0, BOARD_SIZE*BOARD_SIZE);
}

void Sixmok::stop()
{
	isPlay = false;
}

void Sixmok::input()
{
	int x, y;
	string msg[2] = {"의 첫 번째 수의 위치를 입력해주세요 (x, y) : ",
					 "의 두 번째 수의 위치를 입력해주세요 (x, y) : "};

	for(int i=0; i<2; i++)	{
		// 첫 번째 turn에 대해 예외처리.
		if( number == 1 && i == 1 )	
			break;	

		cout << "플레이어" << static_cast<char>('A'+nowTurn-1) << msg[i];
		cin >> x >> y;

		if( move[y][x] == playerA
			|| move[y][x] == playerB )	{
			cout << "이미 돌이 놓여져있는 자리입니다." << endl;
			i--;
			continue;
		}
		else if( x >= 1 && x < BOARD_SIZE-1 
				 && y >= 1 && y < BOARD_SIZE-1 )	{
			move[y][x] = nowTurn;	
		}
		else	{
			cout << "판의 범위를 넘어섰거나 잘못 입력하셨습니다. 허용 범위는 (1~17)입니다." << endl;
			i--;
			continue;
		}
		
		findConnection();

		printBoard();
	}
}

void Sixmok::findConnection()
{
	memset(consecutiveMove, 0, sizeof(consecutiveMove));

	for(int i=1; i<BOARD_SIZE-1; i++)	{
		for(int j=1; j<BOARD_SIZE-1; j++)	{
			for(int k=2; k<=4; k++)	{
				if( move[i][j] != empty )	{
					int oppositeDir = (k + 4) % 8;
					
					if( move[i][j] == move[i+direction[k][0]][j+direction[k][1]] 
						&& move[i][j] != move[i+direction[oppositeDir][0]][j+direction[oppositeDir][1]] )
					{
						int cnt = recursiveCount(j, i, 1, k);
						int turn = move[i][j];
						int pos = ((turn-1)*5) + (cnt-2);

						consecutiveMove[pos]++;
					}
				}
			}
		}
	}
}

int Sixmok::recursiveCount(int x, int y, int cnt, int dir)
{
	if( move[y][x] == move[y+direction[dir][0]][x+direction[dir][1]] )	{
		return recursiveCount(x+direction[dir][1], y+direction[dir][0], cnt+1, dir);
	}
	else {
		return cnt;
	}
}