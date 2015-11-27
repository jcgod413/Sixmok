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
		// 사용자로부터 돌 입력 받기
		playerInput();
		// 인공지능으로부터 돌 입력 받기
		computerInput();
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
	cout << "게임이 종료됩니다." << endl;
	exit(1);
}

void Sixmok::playerInput()
{
	int x, y;
	string msg[2] = {"의 첫 번째 수의 위치를 입력해주세요 (x, y) : ",
					 "의 두 번째 수의 위치를 입력해주세요 (x, y) : "};

	for(int i=0; i<2; i++)	{
		// 첫 번째 수에 대해 예외처리.  
		if( number == 1 && i == 1 )	
			break;	
		// 비정상적인 입력 예외처리 필요 
		cout << "플레이어" << static_cast<char>('A'+nowTurn-1) << msg[i];
		cin >> x >> y;
		
		if( x > 0 && x < BOARD_SIZE-1 && y > 0 && y < BOARD_SIZE-1 )	{
			if( move[y][x] == playerA
				|| move[y][x] == playerB )	{
				cout << "이미 돌이 놓여져있는 자리입니다." << endl;
				i--;
				continue;
			}
	
			moveStone(x, y);
		}
		else	{
			cout << "판의 범위를 넘어섰거나 잘못 입력하셨습니다. 허용 범위는 (1~17)입니다." << endl;
			cin.clear();
			fflush(stdin);
			cout << x << " " << y << endl;
			i--;
			continue;
		}
		
		// 연속된 돌 갱신
		findConnection();
		// 판 갱신
		printBoard();
	}
	
	nextTurn();
}

void Sixmok::computerInput()
{
	int x, y;

	for(int i=0; i<2; i++)	{
		// 연속된 돌 가중치 계산
		calculateWeight();
		// 계산된 가중치로 놓을 돌의 위치 찾기
		findPosition(x, y);
		// 돌 놓기
		moveStone(x, y);
		// 연속된 돌 갱신
		findConnection();
		// 판 갱신
		printBoard();
	}

	nextTurn();
}

void Sixmok::moveStone(int x, int y)
{
	move[y][x] = nowTurn;
}

void Sixmok::findPosition(int &x, int &y)
{
	int max = -1;

	for(int i=1; i<BOARD_SIZE-1; i++)	{
		for(int j=1; j<BOARD_SIZE-1; j++)	{
			if( max < promising[i][j] )	{
				max = promising[i][j];
				x = j;
				y = i;
			}
			if( max < danger[i][j] )	{
				max = danger[i][j];
				x = j;
				y = i;
			}
		}
	}
	cout << "max : " << max << endl;
	cout << x << ", " << y << endl;
	cout << "promising[y][x] = " << promising[y][x] << endl;
	cout << "danger[y][x] = " << danger[y][x] << endl;
}

void Sixmok::calculateWeight()
{	
	memset(danger, 0, sizeof(danger));
	memset(promising, 0, sizeof(promising));

	for(int i=1; i<BOARD_SIZE-1; i++)	{
		for(int j=1; j<BOARD_SIZE-1; j++)	{
			if( move[i][j] == empty )	{
				for(int k=0; k<8; k++)	{
					if( move[i+direction[k][0]][j+direction[k][1]] != empty )
					{
						int newX, newY;
						int cnt = recursiveCount(j+direction[k][1], i+direction[k][0], 1, k);

						if( move[i+direction[k][0]][j+direction[k][1]] == nowTurn )	{
							int newCnt = 0;
							for(int l=1; l<=6; l++)	{
								newX = j + (direction[k][1] * l);
								newY = i + (direction[k][0] * l);

								if( move[i][j] == move[newY][newX] )
									newCnt++;
								else if( move[i][j] != move[newY][newX] &&
										 move[newY][newX] != empty )
									break;
							}

							if( newCnt >=4 )	{
								cnt = CRITICAL * 2;
								
								for(int l=0; l<=7; l++)	{
									newX = j + (direction[k][1] * l);
									newY = i + (direction[k][0] * l);

									if( move[newY][newX] == empty )
										promising[newY][newX] = cnt;									
								}
							}
							else
								promising[i][j] += cnt;
						}
						else	{
							int newCnt = 0;
							for(int l=1; l<=6; l++)	{
								newX = j + (direction[k][1] * l);
								newY = i + (direction[k][0] * l);
								
								if( move[i][j] == move[newY][newX] )
									newCnt++;
								else if( move[i][j] != move[newY][newX] &&
										 move[newY][newX] != empty )
									break;
							}
					
							if( newCnt >= 4 )	{
								cnt = CRITICAL;

								for(int l=0; l<=7; l++)	{
									newX = j + (direction[k][1] * l);
									newY = i + (direction[k][0] * l);

									if( move[newY][newX] == empty )
										danger[newY][newX] = cnt;
								}
							}
							else
								danger[i][j] += cnt; 
						}
					}
				}
			}
		}
	}
}

void Sixmok::findConnection() 
{
	memset(consecutiveMove, 0, sizeof(consecutiveMove)); 

	for(int i=1; i<BOARD_SIZE-1; i++)	{ 
		for(int j=1; j<BOARD_SIZE-1; j++)	{ 
			for(int k=2; k<=5; k++)	{ 
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
