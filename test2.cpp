#include <iostream>
using namespace std;

class sixmok
{
public:
    void intro();
    void showtable();
    void body();
    bool wincheck();
    
private:
    string table[19][19];
    int a_x, a_y, b_x, b_y, a_win=0, b_win=0;
};


int main(){
    
    sixmok game;
    
    game.intro(); // 처음 바둑판을 그림.
    game.showtable(); // 바둑판의 상태를 보여줌.
    game.body();
    
    
    return 0;
}

void sixmok::intro()
{
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

void sixmok::showtable()
{
    int countA=0,countA2=0,countA3=0,countA4=0,countA5=0,countB=0,countB2=0,countB3=0,countB4=0,countB5=0;
    
    for(int i=0; i<19; i++)
    {
        for(int j=0; j<19; j++)
        {
            cout << table[i][j];
        }
        cout << " " << i << endl;
    }
    cout << "0123456789111111111";
    
    for(int i=0; i<19; i++)
    {
       for(int j=0; j<19; j++)
        {
            if (table[i][j]=="●")
                countA++;
            if (table[i][j]=="●" && table[i][j+1]=="●") // 2연속 가로
                countA2++;
            if (table[i][j]=="●" && table[i+1][j]=="●") // 2연속 세로
                countA2++;
            if (table[i][j]=="●" && table[i+1][j+1]=="●") // 2연속 대각선(\)
                countA2++;
            if (table[i][j]=="●" && table[i+1][j-1]=="●") // 2연속 대각선(/)
                countA2++;
            
            if (table[i][j]=="●" && table[i][j+1]=="●" && table[i][j+2]=="●") // 3연속 가로
                countA3++;
            if (table[i][j]=="●" && table[i+1][j]=="●" && table[i+2][j]=="●") // 3연속 세로
                countA3++;
            if (table[i][j]=="●" && table[i+1][j+1]=="●" && table[i+2][j+2]=="●") // 3연속 대각선(\)
                countA3++;
            if (table[i][j]=="●" && table[i-1][j+1]=="●" && table[i-2][j+2]=="●") // 3연속 대각선(/)
                countA3++;
            
            if (table[i][j]=="●" && table[i][j+1]=="●" && table[i][j+2]=="●" && table[i][j+3]=="●") // 4연속 가로
                countA4++;
            if (table[i][j]=="●" && table[i+1][j]=="●" && table[i+2][j]=="●" && table[i+3][j]=="●") // 4연속 세로
                countA4++;
            if (table[i][j]=="●" && table[i+1][j+1]=="●" && table[i+2][j+2]=="●" && table[i-1][j-1]=="●") // 4연속 대각선(\)
                countA4++;
            if (table[i][j]=="●" && table[i-1][j+1]=="●" && table[i-2][j+2]=="●" && table[i+1][j-1]=="●") // 4연속 대각선(/)
                countA4++;
                
            if (table[i][j]=="●" && table[i][j+1]=="●" && table[i][j+2]=="●" && table[i][j+3]=="●" && table[i][j+4]=="●") // 5연속 가로
                countA5++;
            if (table[i][j]=="●" && table[i+1][j]=="●" && table[i+2][j]=="●" && table[i+3][j]=="●" && table[i+4][j]=="●") // 5연속 세로
                countA5++;
            if (table[i][j]=="●" && table[i+1][j+1]=="●" && table[i+2][j+2]=="●" && table[i-1][j-1]=="●" && table[i-2][j-2]=="●") // 5연속 대각선(\)
                countA5++;
            if (table[i][j]=="●" && table[i-1][j+1]=="●" && table[i-2][j+2]=="●" && table[i+1][j-1]=="●" && table[i+2][j-2]=="●") // 5연속 대각선(/)
                countA5++;
        }
    }
    cout << "   흑돌 전체: " << countA << " / 2연속: " << countA2 << " / 3연속: " << countA3 << " / 4연속: " << countA4 << " / 5연속: " << countA5 << endl;
    
    cout << "          012345678";
    
    for(int i=0; i<19; i++)
    {
        for(int j=0; j<19; j++)
        {
            if (table[i][j]=="○")
                countB++;
            if (table[i][j]=="○" && table[i][j+1]=="○") // 2연속 가로
                
                countB2++;
            
            if (table[i][j]=="○" && table[i+1][j]=="○") // 2연속 세로
                
                countB2++;
            
            if (table[i][j]=="○" && table[i+1][j+1]=="○") // 2연속 대각선(\)
                
                countB2++;
            
            if (table[i][j]=="○" && table[i+1][j-1]=="○") // 2연속 대각선(/)
                
                countB2++;
            
            
            
            if (table[i][j]=="○" && table[i][j+1]=="○" && table[i][j+2]=="○") // 3연속 가로
                
                countB3++;
            
            if (table[i][j]=="○" && table[i+1][j]=="○" && table[i+2][j]=="○") // 3연속 세로
                
                countB3++;
            
            if (table[i][j]=="○" && table[i+1][j+1]=="○" && table[i+2][j+2]=="○") // 3연속 대각선(\)
                
                countB3++;
            
            if (table[i][j]=="○" && table[i-1][j+1]=="○" && table[i-2][j+2]=="○") // 3연속 대각선(/)
                
                countB3++;
            
            
            
            if (table[i][j]=="○" && table[i][j+1]=="○" && table[i][j+2]=="○" && table[i][j+3]=="○") // 4연속 가로
                
                countB4++;
            
            if (table[i][j]=="○" && table[i+1][j]=="○" && table[i+2][j]=="○" && table[i+3][j]=="○") // 4연속 세로
                
                countB4++;
            
            if (table[i][j]=="○" && table[i+1][j+1]=="○" && table[i+2][j+2]=="○" && table[i-1][j-1]=="○") // 4연속 대각선(\)
                
                countB4++;
            
            if (table[i][j]=="○" && table[i-1][j+1]=="○" && table[i-2][j+2]=="○" && table[i+1][j-1]=="○") // 4연속 대각선(/)
                
                countB4++;
            
            
            
            if (table[i][j]=="○" && table[i][j+1]=="○" && table[i][j+2]=="○" && table[i][j+3]=="○" && table[i][j+4]=="○") // 5연속 가로
                
                countB5++;
            
            if (table[i][j]=="○" && table[i+1][j]=="○" && table[i+2][j]=="○" && table[i+3][j]=="○" && table[i+4][j]=="○") // 5연속 세로
                
                countB5++;
            
            if (table[i][j]=="○" && table[i+1][j+1]=="○" && table[i+2][j+2]=="○" && table[i-1][j-1]=="○" && table[i-2][j-2]=="○") // 5연속 대각선(\)
                
                countB5++;
            
            if (table[i][j]=="○" && table[i-1][j+1]=="○" && table[i-2][j+2]=="○" && table[i+1][j-1]=="○" && table[i+2][j-2]=="○") // 5연속 대각선(/)
                
                countB5++;
        }
    }
    cout << "   백골 전체: " << countB << " / 2연속: " << countB2 << " / 3연속: " << countB3 << " / 4연속: " << countB4 << " / 5연속: " << countB5 << endl << endl;
}

void sixmok::body()
{
    while (a_win!=1 || b_win!=1) {
        
        
        
        do{
            cout << "플레이어A: 돌을 둘 위치의 좌표값을 입력하세요." << endl;
            
            cout << "x 좌표 (1~17): ";
            cin >> a_x;
            if(a_x > 17 || a_x < 1)
            {
                while(a_x > 17 || a_x < 1)
                {
                    cout << "잘못된 좌표를 입력하였습니다." << endl;
                    cout << "x 좌표 (1~17): ";
                    cin >> a_x;
                }
            }
            
            
            cout << "y 좌표 (1~17): ";
            cin >> a_y;
            if(a_y > 17 || a_y < 1)
            {
                while (a_y > 17 || a_y < 1)
                {
                    cout << "잘못된 좌표를 입력하였습니다." << endl;
                    cout << "y 좌표 (1~17): ";
                    cin >> a_y;
                }
            }
            if (table[a_x][a_y]!="┼")
                cout << "이미 돌이 놓여져 있는 자리입니다." << endl;
            else {
                table[a_x][a_y]="●"; break;}
        }while (table[a_x][a_y]!="┼");
        
        showtable();
        if (wincheck()==1)
        {
            a_win=1; break;}
        
        do{
            cout << "플레이어A: 돌을 둘 위치의 좌표값을 입력하세요." << endl;
            
            cout << "x 좌표 (1~17): ";
            cin >> a_x;
            if(a_x > 17 || a_x < 1)
            {
                while(a_x > 17 || a_x < 1)
                {
                    cout << "잘못된 좌표를 입력하였습니다." << endl;
                    cout << "x 좌표 (1~17): ";
                    cin >> a_x;
                }
            }
            
            
            cout << "y 좌표 (1~17): ";
            cin >> a_y;
            if(a_y > 17 || a_y < 1)
            {
                while (a_y > 17 || a_y < 1)
                {
                    cout << "잘못된 좌표를 입력하였습니다." << endl;
                    cout << "y 좌표 (1~17): ";
                    cin >> a_y;
                }
            }
            if (table[a_x][a_y]!="┼")
                cout << "이미 돌이 놓여져 있는 자리입니다." << endl;
            else {
                table[a_x][a_y]="●"; break;}
        }while (table[a_x][a_y]!="┼");
        
        showtable();
        if (wincheck()==1)
        {
            a_win=1; break;}
        
        
        do{
            cout << "플레이어B: 돌을 둘 위치의 좌표값을 입력하세요." << endl;
            
            cout << "x 좌표 (1~17): ";
            cin >> b_x;
            if(b_x > 17 || b_x < 1)
            {
                while(b_x > 17 || b_x < 1)
                {
                    cout << "잘못된 좌표를 입력하였습니다." << endl;
                    cout << "x 좌표 (1~17): ";
                    cin >> b_x;
                }
            }
            
            
            cout << "y 좌표 (1~17): ";
            cin >> b_y;
            if(b_y > 17 || b_y < 1)
            {
                while (b_y > 17 || b_y < 1)
                {
                    cout << "잘못된 좌표를 입력하였습니다." << endl;
                    cout << "y 좌표 (1~17): ";
                    cin >> b_y;
                }
            }
            if (table[b_x][b_y]!="┼")
                cout << "이미 돌이 놓여져 있는 자리입니다." << endl;
            else {
                table[b_x][b_y]="○"; break;}
        }while (table[b_x][b_y]!="┼");
        
        
        showtable();
        if (wincheck()==1)
        {
            b_win=1; break;
        }
        
        do{
            cout << "플레이어B: 돌을 둘 위치의 좌표값을 입력하세요." << endl;
            
            cout << "x 좌표 (1~17): ";
            cin >> b_x;
            if(b_x > 17 || b_x < 1)
            {
                while(b_x > 17 || b_x < 1)
                {
                    cout << "잘못된 좌표를 입력하였습니다." << endl;
                    cout << "x 좌표 (1~17): ";
                    cin >> b_x;
                }
            }
            
            
            cout << "y 좌표 (1~17): ";
            cin >> b_y;
            if(b_y > 17 || b_y < 1)
            {
                while (b_y > 17 || b_y < 1)
                {
                    cout << "잘못된 좌표를 입력하였습니다." << endl;
                    cout << "y 좌표 (1~17): ";
                    cin >> b_y;
                }
            }
            if (table[b_x][b_y]!="┼")
                cout << "이미 돌이 놓여져 있는 자리입니다." << endl;
            else {
                table[b_x][b_y]="○"; break;}
        }while (table[b_x][b_y]!="┼");
        
        
        showtable();
        if (wincheck()==1)
        {
            b_win=1; break;
        }
        
        
    }
    
    
    if (a_win==1)
        cout << "플레이어A가 승리하였습니다." << endl;
    else if (b_win==1)
        cout << "플레이어B가 승리하였습니다." << endl;
}

bool sixmok::wincheck()
{
    for(int i=0; i<19; i++)
    {
        for(int j=0; j<19; j++)
        {
            if (table[i][j]=="●" && table[i][j+1]=="●" && table[i][j+2]=="●" && table[i][j+3]=="●" && table[i][j+4]=="●" && table[i][j+5]=="●") // 가로
                return true;
            else if (table[i][j]=="●" && table[i+1][j]=="●" && table[i+2][j]=="●" && table[i+3][j]=="●" && table[i+4][j]=="●" && table[i+5][j]=="●") // 세로
                return true;
            else if (table[i][j]=="●" && table[i+1][j+1]=="●" && table[i+2][j+2]=="●" && table[i-1][j-1]=="●" && table[i-2][j-2]=="●" && table[i+3][j+3]=="●") // 대각선(\)
                return true;
            else if (table[i][j]=="●" && table[i-1][j+1]=="●" && table[i-2][j+2]=="●" && table[i+1][j-1]=="●" && table[i+2][j-2]=="●" && table[i-3][j+3]=="●") // 대각선(/)
                return true;
            else if (table[i][j]=="○" && table[i][j+1]=="○" && table[i][j+2]=="○" && table[i][j+3]=="○" && table[i][j+4]=="○" && table[i][j+5]=="○") // 가로
                return true;
            else if (table[i][j]=="○" && table[i+1][j]=="○" && table[i+2][j]=="○" && table[i+3][j]=="○" && table[i+4][j]=="○" && table[i+5][j]=="○") // 세로
                return true;
            else if (table[i][j]=="○" && table[i+1][j+1]=="○" && table[i+2][j+2]=="○" && table[i-1][j-1]=="○" && table[i-2][j-2]=="○" && table[i+3][j+3]=="○") // 대각선(\)
                return true;
            else if (table[i][j]=="○" && table[i-1][j+1]=="○" && table[i-2][j+2]=="○" && table[i+1][j-1]=="○" && table[i+2][j-2]=="○" && table[i-3][j+3]=="○") // 대각선(/)
                return true;
        }
    }
    return false;
}