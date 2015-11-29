#include "sixmok.h"

// 8방향의 값을 나타내는 배열
int direction[8][2] = { {-1, 0}, {-1, 1}, {0, 1},  {1, 1},
						{1, 0},  {1, -1}, {0, -1}, {-1, -1} };

MySocket player(sizeof(GAME_DATA));

Sixmok::Sixmok(int mode, int p) : gameMode(mode),
			participant(p)
{
	init();
}

void Sixmok::init()
{
	isPlay = false;
	nowTurn = playerA;
	number = 1;

	srand(time(NULL));

	memset(move, 0, sizeof(move));
	memset(consecutiveMove, 0, sizeof(consecutiveMove));

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

	if( gameMode == Server )	{
		player.ServerSetting();
		player.ServerRun();
	}
	else    {
		player.ClientSetting();
		player.ClientRun();
	}
}

void Sixmok::play()
{
	isPlay = true;

	while( isPlay )	{
		// 판 그리기
		printBoard();

		if( gameMode == Client )	{
			// 사용자로부터 돌 입력 받기
			if( participant == People )	{
				playerInput();
				playerInput2();
				// 사람이 입력
			}
			else
			{
				playerInput();
				// 인공지능으로부터 돌 입력 받기
				computerInput();
			}
		}
		else if( gameMode == Server )	{		
			if( participant == People )	{
				// 사람이 입력
				playerInput2();
				playerInput();
			}
			else
			{				
				// 인공지능으로부터 돌 입력 받기
				computerInput();
				// 사용자로부터 돌 입력 받기
				playerInput();
			}
		}
	}
}

void Sixmok::printBoard()
{
	string msg[2] = {"Server", "Client"};
	board[5][5] = 1;
	system("cls");
	board[5][5] = "┼";
	for(int i=0; i<BOARD_SIZE; i++)	{
		for(int j=0; j<BOARD_SIZE; j++)	{
			switch( move[i][j])	{
				case 0:	cout << board[i][j];	break;
				case 1:	cout << "○";			break;
				case 2:	cout << "●";			break;
			}		
		}
			
		cout << " " << i;
		if( i < 10 )	{
			cout << "\t" << msg[i/5] << "의 연속" << (i % 5) + 2 << "개 개수 " << consecutiveMove[i];
		}
		else if( i == 10 )	{
			cout << "\t" << "Server 전체 돌의 개수 : " << consecutiveMove[10];
		}
		else if( i == 11 )	{
			cout << "\t" << "Client 전체 돌의 개수 : " << consecutiveMove[11];
		}
		cout << endl;
	}
	cout << "0 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1 1 1 1" << endl;
	cout << "                    0 1 2 3 4 5 6 7 8" << endl << endl;

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
	else if( consecutiveMove[10]+consecutiveMove[11] == 17*17 )	{
		cout << "무승부 입니다!" << endl;
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
		
		if( gameMode == Client && number == 1 && i == 1 )
			break;

		// 비정상적인 입력 예외처리 필요 
		cout << "플레이어" << static_cast<char>('A'+nowTurn-1) << msg[i];
		player.RecvData(&gameData);
		x = gameData.x;
		y = gameData.y;

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

void Sixmok::playerInput2()
{
	int x, y;
	string msg[2] = {"의 첫 번째 수의 위치를 입력해주세요 (x, y) : ",
					 "의 두 번째 수의 위치를 입력해주세요 (x, y) : "};

	for(int i=0; i<2; i++)	{
		
		if( gameMode == Server && number == 1 && i == 1 )
			break;

		// 비정상적인 입력 예외처리 필요 
		cout << "플레이어" << static_cast<char>('A'+nowTurn-1) << msg[i];
		cin >> x >> y;
		gameData.x = x;
		gameData.y = y;
		gameData.win = 0;
		player.SendData(&gameData);
		
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
		// 첫 수
		if( number == 1 && gameMode == Server )	{
			x = (rand() % 7) + 6;	// 6~12
			y = (rand() % 7) + 6;	// 6~12
			moveStone(x, y);

			gameData.x = x;
			gameData.y = y;
			gameData.win = 0;
			player.SendData(&gameData);
			
			findConnection();
			printBoard();
			break;
		}
		
		// 가중치 계산하기
		calculateWeight();
		// 계산된 가중치로 놓을 돌의 위치 찾기
		findPosition(x, y);
		// 돌 놓기
		moveStone(x, y);

		gameData.x = x;
		gameData.y = y;
		gameData.win = 0;
		player.SendData(&gameData);
		
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
			if( move[i][j] != empty )
				continue;

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
}

void Sixmok::calculateWeight()
{	
	memset(danger, 0, sizeof(danger));
	memset(promising, 0, sizeof(promising));

	int cnt = 0;

	for(int i=1; i<BOARD_SIZE-1; i++)	{
		for(int j=1; j<BOARD_SIZE-1; j++)	{
			if( move[i][j] == empty )	{
				for(int k=0; k<8; k++)	{
					int newI = i + direction[k][0];
					int newJ = j + direction[k][1];
			
					if( move[newI][newJ] != empty )	{
						cnt = recursiveCount(newJ, newI, 1, k);

						int newCnt = 0;
						for(int l=0; l<6; l++)	{
							int newI2 = newI + (direction[k][0] * l);
							int newJ2 = newJ + (direction[k][1] * l);

							if( move[newI][newJ] == move[newI2][newJ2] )	{
								newCnt++;
							}
							else if( move[newI2][newJ2] != empty )	{
								break;
							}
						}

						int t = 2;

						if( newCnt == 4 && number % 2 == 1 )	{
							for(int l=0; l<=6; l++)	{
								int newI2 = i + (direction[k][0] * l);
								int newJ2 = j + (direction[k][1] * l);

								if( move[newI2][newJ2] == empty && t > 0 )	{
									danger[newI2][newJ2] = CRITICAL;
									t--;
									if( move[newI2+direction[k][0]][newJ2+direction[k][1]] == empty )	
										break;
								}
							}
						}
						else if( newCnt >= 4 && number % 2 == 0 )	{
							danger[i][j] += CRITICAL;
						}
						
						danger[i][j] += pow(2, cnt);
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

			if( move[i][j] == playerA )	{
				consecutiveMove[10]++;
			}
			else if( move[i][j] == playerB )	{
				consecutiveMove[11]++;
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
