#include "sixmok.h"

int main()
{
	int gameMode;
	int participant = 0;

	cout<<"1. This Machine will work as a Server"<<endl;
	cout<<"2. This Machine will work as a Client"<<endl;
	cin>>gameMode;
	cout << "1. 사람이 플레이" << endl;
	cout << "2. 인공지능이 플레이" << endl;
	cin >> participant;

	Sixmok *game = new Sixmok(gameMode, participant);
	game->play();
}