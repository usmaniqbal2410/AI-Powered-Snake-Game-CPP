// Username : FA21-BSE
// Password : DSA

#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <cstdlib>

#define MinWidth 65
#define Width 120
#define MinHeight 8
#define Height 35

struct Node{
	COORD Data;
	Node *Next,*Previous;
} *Normal_Start,*AI_Start,*List,*temp,*Normal_End,*AI_End;

using namespace std;

COORD Snake_pos;
COORD AI_Snake_pos;
COORD Food_pos;
COORD CutFood_pos;
HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
char Direction,AI_Direction;
int Score,AI_Score,Second,MaxTime = 120,SelfHitCount,AISelfHitCount,MaxSelfHit = 1,Special,Change,Normal_Height ,AI_Height,Length,AI_Length,CutSize = 10;

void game(int Mode);
void Board(int Mode);
void Boarder(int Mode);
void MoveSnake(int Mode,char DirectionOfSnake,COORD Snake,int Type);
void GenerateFood();
void GenerateCutFood();
bool Ate();
bool Collision();
void gotoxy(int x,int y);
void insert(int X,int Y,int Snake);
void DeleteAtHead(int Snake);
void PrintSnake(Node *Element,int Type);
int CheckInSnake(Node *Element,int X,int Y);
bool Hit(int X,int Y,int Type,int N);
void AI_Dir();
void Changeifbody(int New_Direction,int Old_Direction);
void Login();
void startLogo();
void Menu();

int main(){
	Menu();
}

void Menu(){
	system("color f0");
    char CHOICE = ' ',CHOICE2 = ' ';
    int Invalid = 3 , Invalid2;
    Login();
    startLogo();
    do{
        system("cls");
        Invalid2=3;
        cout<<"\n\t\t\t\t\t\t\t\t\t\t    SNAKE GAME "<<"\n";
        cout<<"\t\t\t\t\t\t\t\t\t\t    ---------- ";
        cout<<"\n\n\n\t\t\t\t\t\t\t\t   [1]-> Start the Game ";
        cout<<"\n\n\t\t\t\t\t\t\t\t   [2]-> Exit ";
        cout<<"\n\n\t\t\t\t\t\t\t\t   --------------------------------------------";
        cout<<"\n\n\t\t\t\t\t\t\t\t   Choice : ";
        CHOICE = getch();
        cout<<CHOICE;
        getch();
        switch(CHOICE){
        case '1':
            Invalid=3;
            do{
                system("cls");
                cout<<"\n\t\t\t\t\t\t\t\t\t\t    SNAKE GAME "<<"\n";
                cout<<"\t\t\t\t\t\t\t\t\t\t    ---------- ";
                cout<<"\n\n\n\t\t\t\t\t\t\t\t   [1]-> Normal ";
                cout<<"\n\n\t\t\t\t\t\t\t\t   [2]-> AI_Snake ";                
                cout<<"\n\n\t\t\t\t\t\t\t\t   [3]-> Main Menu ";
                cout<<"\n\n\t\t\t\t\t\t\t\t   --------------------------------------------";
                cout<<"\n\n\t\t\t\t\t\t\t\t   Choice : ";
                CHOICE2 = getch();
                cout<<CHOICE2;
                getch();
                switch(CHOICE2){
                case '1':
                    game(2);
                    CHOICE2 = 4;
                    Invalid2 = 0;
                    break;
                case '2':
                    game(1);
                    CHOICE2 = 4;
                    Invalid2 = 0;
                    break;                
                case '3':
                    break;
                default :
                    cout<<"\n\n\t\t\t\t\t\t\t\t   Invalid Entery !!!";
                    Invalid2--;
                    if(Invalid2>0){
                        cout<<"\n\t\t\t\t\t\t\t\t   "<<Invalid2<<" Chances left !!!";
                        getch();
                    }else{
                        cout<<"\n\t\t\t\t\t\t\t\t   You have used all your chances";
                        getch();
                    }
                }
            }while(CHOICE2 != '4' && Invalid2 != 0);
            break;
        case '2':
            cout<<"\n\n\t\t\t\t\t\t\t\t   Thanks for Playing... ";
            break;
        default :
            cout<<"\n\n\t\t\t\t\t\t\t\t   Invalid Entery !!! ";
            Invalid--;
            if(Invalid>0){
            cout<<"\n\t\t\t\t\t\t\t\t   "<<Invalid<<" Chances left !!!";
            getch();
            }else{
            cout<<"\n\t\t\t\t\t\t\t\t   You have used all your chances";
            getch();
            }
            break;
        }
    }while(CHOICE!='2' && Invalid != 0);
}

void game(int Mode){
	Normal_Start = NULL;
	AI_Start = NULL;
	Normal_End = NULL;
	AI_End = NULL;
    Score = 0;
	AI_Score = 0;
	Direction = ' ';
	AI_Direction = ' ';
	Second = 0;
	Length = 1;
	Normal_Height = 0;
	AI_Length = 1;
	AI_Height = 0;
	SelfHitCount = 0;
	AISelfHitCount = 0;
	Special = 1;
	Change = 0;
	Snake_pos.Y = (MinHeight+Height)/2;
	if(Mode == 1){
		Snake_pos.X = ((MinWidth+Width)/2)-10;
    	AI_Snake_pos.X = ((MinWidth+Width)/2)+10;
		AI_Snake_pos.Y = (MinHeight+Height)/2;
		insert(AI_Snake_pos.X,AI_Snake_pos.Y,2);
	}else if(Mode == 2) Snake_pos.X = (MinWidth+Width)/2;
    insert(Snake_pos.X,Snake_pos.Y,1);
    char Over = ' ',CheckDirection = ' ';
    int miliSec = 0,NanoSec = 1,Check = 0,Remove;
    bool GameOver = false;
    srand(time(NULL));
    GenerateFood();
    if(Mode == 2) GenerateCutFood();
    CheckDirection = Direction;
    Boarder(Mode);
    while(!GameOver){
    	PrintSnake(Normal_Start,1);
    	if(Mode == 1) PrintSnake(AI_Start,2);
        if(Check == 0){
            CheckDirection = Direction;
        }else if(Check == 1 && Direction != ' '){
            Check = 0;
        }
        if((SelfHitCount+AISelfHitCount) == MaxSelfHit){
            Board(Mode);
            goto Label2;
        }
        Board(Mode);
        if(Direction == ' ' && Second == 0){
        	SetConsoleTextAttribute(H,0xf0);
            gotoxy(((MinWidth+Width)/2)-13,((MinHeight+Height)/2)-1);
            cout<<"Press any Key to Start !!!";
            Remove = 0;
        }else if(Direction == ' '){
        	SetConsoleTextAttribute(H,0xf0);
            gotoxy(((MinWidth+Width)/2)-15,((MinHeight+Height)/2)-1);
            cout<<"Press any Key to Continue !!!";
            Remove = 0;
        }else if(Direction != ' ' && Remove == 0){
        	system("cls");
        	Boarder(Mode);
        	Remove = 1;
		}
		AI_Dir();
        if(kbhit()){
            switch(getch()){
            case 72: if(CheckDirection != 80 || Length == 1) Direction = 72; break;
            case 80: if(CheckDirection != 72 || Length == 1) Direction = 80; break;
            case 75: if(CheckDirection != 77 || Length == 1) Direction = 75; break;
            case 77: if(CheckDirection != 75 || Length == 1) Direction = 77; break;
            case 27:
                {
                	SetConsoleTextAttribute(H,0xf0);
                    system("cls");
                    cout<<"\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t-------------------------------------------------"<<"\n";
                    cout<<"\t\t\t\t\t\t\t\t\t|                                               |"<<"\n";
                    cout<<"\t\t\t\t\t\t\t\t\t|            Do you want to EXIT !!!            |"<<"\n";
                    cout<<"\t\t\t\t\t\t\t\t\t|                                               |"<<"\n";
                    cout<<"\t\t\t\t\t\t\t\t\t|               YES          N0                 |"<<"\n";
                    cout<<"\t\t\t\t\t\t\t\t\t|                                               |"<<"\n";
                    cout<<"\t\t\t\t\t\t\t\t\t|     Note : If yes then Press Y or y and If    |"<<"\n";
                    cout<<"\t\t\t\t\t\t\t\t\t|             No then Press any other Key       |"<<"\n";
                    cout<<"\t\t\t\t\t\t\t\t\t|                                               |"<<"\n";
                    cout<<"\t\t\t\t\t\t\t\t\t-------------------------------------------------"<<"\n";
                    Over = getch();
                    if(Over == 'Y' || Over == 'y'){
                        goto Label;
                    }else{
                    	Boarder(Mode);
                        CheckDirection = Direction;
                        Direction = ' ';
                        Check = 1;
                    }
                }
                break;
            }
        }
        if(Second>MaxTime-1){
        	SetConsoleTextAttribute(H,0xf0);
            gotoxy(((MinWidth+Width)/2)-7,((MinHeight+Height)/2)-4);
            cout<<"Times Up !!!";
            gotoxy(((MinWidth+Width)/2)-7,((MinHeight+Height)/2)-3);
            cout<<"------------";
            gotoxy(((MinWidth+Width)/2)-15,((MinHeight+Height)/2)-1);
            cout<<"Press any Key to Continue !!!";
            getch();
            goto Label;
        }
        if(Hit(Snake_pos.X,Snake_pos.Y,1,1)){
        	SetConsoleTextAttribute(H,0xf0);
            SelfHitCount++;
            gotoxy(((MinWidth+Width)/2)-7,((MinHeight+Height)/2)-4);
            cout<<"Self Hit !!!";
            gotoxy(((MinWidth+Width)/2)-7,((MinHeight+Height)/2)-3);
            cout<<"------------";
            gotoxy(((MinWidth+Width)/2)-15,((MinHeight+Height)/2)-1);
            cout<<"Press any Key to Continue !!!";
            getch();
            system("cls");
            Boarder(Mode);
        }
        if (Hit(AI_Snake_pos.X,AI_Snake_pos.Y,2,1))
        {
        	SetConsoleTextAttribute(H,0xf0);
            AISelfHitCount++;
            gotoxy(((MinWidth+Width)/2)-8,((MinHeight+Height)/2)-4);
            cout<<"AI Self Hit !!!";
            gotoxy(((MinWidth+Width)/2)-8,((MinHeight+Height)/2)-3);
            cout<<"---------------";
            gotoxy(((MinWidth+Width)/2)-15,((MinHeight+Height)/2)-1);
            cout<<"Press any Key to Continue !!!";
            getch();
            system("cls");
            Boarder(Mode);
		}
        if(Direction != ' '){
            MoveSnake(Mode,Direction,Snake_pos,1);
            if(Mode == 1) MoveSnake(1,AI_Direction,AI_Snake_pos,2);
            NanoSec = 10;
            miliSec = miliSec + (NanoSec*15);
            Second = miliSec/1000;
        }
        GameOver = Collision();
        if(Hit(Food_pos.X,Food_pos.Y,1,0) || Hit(Food_pos.X,Food_pos.Y,2,0)){
        	if(Change == 1){
        		Change = 0;
        		if(Special == 1) Special = 2;
        		else Special = 1;
			}
			if(Hit(Food_pos.X,Food_pos.Y,1,0)){
				Length += 2;
				Score += 10;
			}
			else if(Hit(Food_pos.X,Food_pos.Y,2,0)){
				AI_Length+=2;
				AI_Score += 10;
			}
            GenerateFood();
        }
        if(Hit(CutFood_pos.X,CutFood_pos.Y,1,0) && Mode == 2){
			Length -= CutSize;
			if(Length < 1) Length = 1;
			for(int i = 0;i<CutSize;i++){
				if(Normal_Height > Length) DeleteAtHead(1);
			}
			Score += 10;
			GenerateCutFood();
		}
		
		if(Mode == 1 && (Hit(Snake_pos.X,Snake_pos.Y,2,0) || Hit(AI_Snake_pos.X,AI_Snake_pos.Y,1,0))){
			SetConsoleTextAttribute(H,0xf0);
			if(Hit(Snake_pos.X,Snake_pos.Y,2,0)){
				gotoxy(((MinWidth+Width)/2)-15,((MinHeight+Height)/2)-4);
            	cout<<"You Hit With Other Snake  !!!";
            	PrintSnake(Normal_Start,1);
            	Score = Score-50;
            	if(Score < 0) Score = 0;
			}else if(Hit(AI_Snake_pos.X,AI_Snake_pos.Y,1,0)){
				gotoxy(((MinWidth+Width)/2)-15,((MinHeight+Height)/2)-4);
            	cout<<"Other Snake Hit Your Snake !!!";
            	PrintSnake(AI_Start,2);
            	AI_Score = AI_Score-50;
            	if(AI_Score < 0) AI_Score = 0;
			}
			SetConsoleTextAttribute(H,0xf0);
			gotoxy(((MinWidth+Width)/2)-15,((MinHeight+Height)/2)-3);
            cout<<"-----------------------------";
            gotoxy(((MinWidth+Width)/2)-15,((MinHeight+Height)/2)-1);
            cout<<"Press any Key to Continue !!!";
            getch();
            goto Label;
		}
        Sleep(10);
    }
    Label2:
    SetConsoleTextAttribute(H,0xf0);
    gotoxy(((MinWidth+Width)/2)-6,((MinHeight+Height)/2)-4);
    cout<<"GAME OVER!!!";
    gotoxy(((MinWidth+Width)/2)-6,((MinHeight+Height)/2)-3);
    cout<<"------------";
    gotoxy(((MinWidth+Width)/2)-15,((MinHeight+Height)/2)-1);
    cout<<"Press any Key to Continue !!!";
    getch();
    Label:
    SetConsoleTextAttribute(H,0xf0);
    system("cls");
    cout<<"\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t-------------------------------------------------"<<"\n";
    cout<<"\t\t\t\t\t\t\t\t\t                                               "<<"\n";
    cout<<"\t\t\t\t\t\t\t\t\t                   SCORE CARD                  "<<"\n";
    cout<<"\t\t\t\t\t\t\t\t\t                   ----------                  "<<"\n";
    cout<<"\t\t\t\t\t\t\t\t\t                                               "<<"\n";
    if(Mode == 2){
    cout<<"\t\t\t\t\t\t\t\t\t            Score      :  "<<Score<<"\n";
    cout<<"\t\t\t\t\t\t\t\t\t            SELF HIT    : "<<SelfHitCount<<endl;  
    }else{
    	if(AI_Score>Score) cout<<"\t\t\t\t\t\t\t\t\t            WINNER      :  AI SNAKE\n";
    	if(Score>AI_Score) cout<<"\t\t\t\t\t\t\t\t\t            WINNER      :  YOU\n";
    	if(Score==AI_Score) cout<<"\t\t\t\t\t\t\t\t\t            WINNER      :  No Winner(Both)\n";     	
    	cout<<"\t\t\t\t\t\t\t\t\t            Your Score  :  "<<Score<<"\n";
    	cout<<"\t\t\t\t\t\t\t\t\t            AI Score    :  "<<AI_Score<<"\n";
    	
	}
    cout<<"\t\t\t\t\t\t\t\t\t            TIME PLAYED :  "<<Second<<" Sec\n";
    cout<<"\t\t\t\t\t\t\t\t\t                                               "<<"\n";
    cout<<"\t\t\t\t\t\t\t\t\t   Note : Press any key to Go to the Main Menu"<<"\n";
    cout<<"\t\t\t\t\t\t\t\t\t-------------------------------------------------\n\n\n";
    getch();
}
 
void Board(int Mode){
    for(int i=MinHeight+1 ; i <= Height-1 ; i++){
        for(int j=MinWidth+1 ; j < Width ; j++){           
			if(i == Snake_pos.Y && j == Snake_pos.X){
				gotoxy(j,i);
				SetConsoleTextAttribute(H,0xf1);
                cout<<"O";
            }if(i == AI_Snake_pos.Y && j == AI_Snake_pos.X && Mode == 1){
				gotoxy(j,i);
				SetConsoleTextAttribute(H,0xf4);
                cout<<"^";
            }else if(i == Food_pos.Y && j == Food_pos.X && Score%50 == 0 && Length != 1 && Mode == 2){
            	gotoxy(j,i);
            	SetConsoleTextAttribute(H,0xf0);
                cout<<"@";
                Change = 1;
            }else if(i == CutFood_pos.Y && j == CutFood_pos.X && Score%30 == 0  && Length != 1 && Mode == 2){
            	gotoxy(j,i);
            	SetConsoleTextAttribute(H,0xf0);
                cout<<"V";
            }else if(i == CutFood_pos.Y && j == CutFood_pos.X && Score%40 == 0  && Length != 1 && Mode == 2){
            	gotoxy(j,i);
                cout<<" ";
                GenerateCutFood();
            }else if(i == Food_pos.Y && j == Food_pos.X){
				gotoxy(j,i);
				SetConsoleTextAttribute(H,0xf0);
                cout<<"*";
            }
        }
    }
    SetConsoleTextAttribute(H,0xf0);
    gotoxy(MinWidth+17,Height+3);
    cout<<Score;
    gotoxy(MinWidth+17,Height+4);
    cout<<SelfHitCount;
    gotoxy(MinWidth+17,Height+5);
    cout<<Second;
    if(Mode == 1){
    	gotoxy(MinWidth+47,Height+3);
        cout<<AI_Score;
        gotoxy(MinWidth+47,Height+4);
        cout<<AISelfHitCount;
        gotoxy(MinWidth+21,Height+6);
        cout<<MaxSelfHit;
	}if(Mode==2){
    gotoxy(MinWidth+47,Height+4);
    cout<<MaxSelfHit;
    }    
    gotoxy(MinWidth+47,Height+5);
    cout<<MaxTime;
    Sleep(100);
}

void Boarder(int Mode){
	system("cls");
	SetConsoleTextAttribute(H,0xf0);
	gotoxy(((MinWidth+Width)/2)-5,3);
	cout<<"SNAKE GAME";
	gotoxy(((MinWidth+Width)/2)-5,4);
	cout<<"==========";
	for(int i=MinWidth;i<=Width+4;i++){
		gotoxy(i-2,MinHeight-1);
		cout<<"*";
		gotoxy(i-2,MinHeight);
		cout<<"-";
		gotoxy(i-2,Height);
		cout<<"-";
		gotoxy(i-2,Height+1);
		cout<<"*";
	}
	for(int j=MinHeight; j<Height+1; j++){
		gotoxy(MinWidth-2,j);
		cout<<"|";
		gotoxy(MinWidth,j);
		cout<<"|";
		gotoxy(Width,j);
		cout<<"|";
		gotoxy(Width+2,j);
		cout<<"|";
	}
	gotoxy(MinWidth+1,Height+3);
    cout<<"Score         :";
    gotoxy(MinWidth+17,Height+3);
    cout<<Score;
    gotoxy(MinWidth+1,Height+4);
    cout<<"You Self Hit  :";
    gotoxy(MinWidth+17,Height+4);
    cout<<SelfHitCount;
    gotoxy(MinWidth+1,Height+5);
    cout<<"Time          :";
    gotoxy(MinWidth+17,Height+5);
    cout<<Second;
    gotoxy(MinWidth+27,Height+5);
    if(Mode==1){
    gotoxy(MinWidth+27,Height+3);
    cout<<"AI Score          :";
    gotoxy(MinWidth+47,Height+3);
    cout<<AI_Score;	
    gotoxy(MinWidth+27,Height+4);
    cout<<"AI Self Hit       :";
    gotoxy(MinWidth+47,Height+4);
    cout<<AISelfHitCount;
    gotoxy(MinWidth+1,Height+6);
    cout<<"Maximum Self Hit  :";
    gotoxy(MinWidth+21,Height+6);
    cout<<MaxSelfHit;
	}
	if(Mode==2){
	gotoxy(MinWidth+27,Height+4);
    cout<<"Maximum Self Hit  :";
    gotoxy(MinWidth+47,Height+4);
    cout<<MaxSelfHit;
    }
    gotoxy(MinWidth+27,Height+5);
    cout<<"Maximum Time      :";
    gotoxy(MinWidth+47,Height+5);
    cout<<MaxTime;
		
}

void MoveSnake(int Mode,char DirectionOfSnake,COORD Snake,int Type){
	if(Special == 1 || Mode == 1){
		switch(DirectionOfSnake){
    	case 72: Snake.Y -= 1; break; //Up
    	case 80: Snake.Y += 1; break; //Down
    	case 77: Snake.X += 1; break; //Right
    	case 75: Snake.X -= 1; break; //Left
    	}
	}else{
		switch(DirectionOfSnake){
    	case 72: Snake.Y -= 1; Snake.X +=1; break; //Right-Up
    	case 80: Snake.Y += 1; Snake.X -=1; break; //Left-Down
    	case 77: Snake.X += 1; Snake.Y +=1; break; //Right-Down
    	case 75: Snake.X -= 1; Snake.Y -=1; break; //Left-Up
    	}
	}
    if(Snake.X >= Width)           Snake.X = MinWidth+1;
    else if(Snake.X < MinWidth+1)  Snake.X = Width-1;
    if(Snake.Y >= Height)          Snake.Y = MinHeight+1;
    else if(Snake.Y < MinHeight+1) Snake.Y = Height-1;
    
    insert(Snake.X,Snake.Y,Type);
    if(Type == 1){
    	Snake_pos.X = Snake.X;
    	Snake_pos.Y = Snake.Y;
	}else if(Type == 2){
    	AI_Snake_pos.X = Snake.X;
    	AI_Snake_pos.Y = Snake.Y;
	}
	if(Normal_Height > Length || AI_Height > AI_Length) DeleteAtHead(Type);
}

void GenerateFood(){
    Food_pos.X = (rand() % ((Width-1)-MinWidth))+ (MinWidth+1);     // (rand % Upper - lower + 1) + Lower
    Food_pos.Y = (rand() % ((Height-1)-MinHeight)) + (MinHeight+1);
    if(Hit(Food_pos.X,Food_pos.Y,1,0) || Hit(Food_pos.X,Food_pos.Y,2,0))   GenerateFood();
}

void GenerateCutFood(){
    CutFood_pos.X = (rand() % ((Width-1)-MinWidth))+ (MinWidth+1);     // (rand % Upper - lower + 1) + Lower
    CutFood_pos.Y = (rand() % ((Height-1)-MinHeight)) + (MinHeight+1);
    if(Hit(CutFood_pos.X,CutFood_pos.Y,1,0) || Hit(CutFood_pos.X,CutFood_pos.Y,2,0) || ((CutFood_pos.X == Food_pos.X) && (CutFood_pos.Y == Food_pos.Y)))   GenerateCutFood();
}

bool Collision(){
    return (Snake_pos.X <= MinWidth || Snake_pos.X > Width || Snake_pos.Y <= MinHeight || Snake_pos.Y > Height);
}

bool Hit(int X,int Y,int Type,int N){
    int Count = 0;
    if(Type == 1) Count = CheckInSnake(Normal_Start,X,Y);
    else if(Type == 2) Count = CheckInSnake(AI_Start,X,Y);
    
    return (Count > N);
}

void gotoxy(int x, int y){
    COORD CursorPosition;
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}

void insert(int X,int Y,int Snake){
	if(Snake == 1 && Normal_Start == NULL){
		Normal_Height = 1;
		Normal_Start = new Node;
		Normal_Start->Data.X = X;
		Normal_Start->Data.Y = Y;
		Normal_Start->Next = NULL;
		Normal_Start->Previous = NULL;
		Normal_End = Normal_Start;
	}else if(Snake == 2 && AI_Start == NULL){
		AI_Height = 1;
		AI_Start = new Node;
		AI_Start->Data.X = X;
		AI_Start->Data.Y = Y;
		AI_Start->Next = NULL;
		AI_Start->Previous = NULL;
		AI_End = AI_Start;
	}else{
		temp = new Node;
		temp->Data.X = X;
		temp->Data.Y = Y;
		temp->Next = NULL;
		if(Snake == 1){
			Normal_Height += 1;
			temp->Previous = Normal_End;
			Normal_End->Next = temp;
			Normal_End = temp;
		}else if(Snake == 2){
			AI_Height += 1;
			temp->Previous = AI_End;
			AI_End->Next = temp;
			AI_End = temp;
		}
	}
}

void DeleteAtHead(int Snake){
	if(Snake == 1){
		Normal_Height -= 1;
		List = Normal_Start;
		gotoxy(List->Data.X,List->Data.Y);
		cout<<" ";
		Normal_Start = List->Next;
		Normal_Start->Previous = NULL;
	}else if(Snake == 2){
		AI_Height -= 1;
		List = AI_Start;
		gotoxy(List->Data.X,List->Data.Y);
		cout<<" ";
		AI_Start = List->Next;
		AI_Start->Previous = NULL;
	}
	delete List;
}

void PrintSnake(Node *Element,int Type){
	List = Element;
	if(List != NULL){
		while(List->Next != NULL){
			gotoxy(List->Data.X,List->Data.Y);
			if(Type == 1){
				SetConsoleTextAttribute(H,0xf1);
				cout<<"o";
			}
			else if(Type == 2){
				SetConsoleTextAttribute(H,0xf4);
				cout<<"+";
			}
			List = List->Next;
		}
		if(List->Next == NULL){
			gotoxy(List->Data.X,List->Data.Y);
			if(Type == 1)      cout<<"o";
			else if(Type == 2) cout<<"+";
		}
	}
}

int CheckInSnake(Node *Element,int X,int Y){
	List = Element;
	int FoundInList = 0;
	if(List != NULL){
		while(List->Next != NULL){
			if(List->Data.X == X && List->Data.Y == Y)   FoundInList += 1;
			List = List->Next;
		}
		if(List->Next == NULL && List->Data.X == X && List->Data.Y == Y)   FoundInList += 1;
	}
	return FoundInList;
}

void AI_Dir(){
	if(AI_Snake_pos.Y < Food_pos.Y)       Changeifbody(80,80);
	else if(AI_Snake_pos.Y > Food_pos.Y)  Changeifbody(72,72);
	else if(AI_Snake_pos.Y == Food_pos.Y){
		if(AI_Snake_pos.X < Food_pos.X)       Changeifbody(77,77);
		else if(AI_Snake_pos.X > Food_pos.X)  Changeifbody(75,75);
	}
}

void Changeifbody(int New_Direction,int Old_Direction){
	COORD Next_pos;
	switch(New_Direction){
		case 72: Next_pos.Y = AI_Snake_pos.Y-1; Next_pos.X = AI_Snake_pos.X; break;
        case 80: Next_pos.Y = AI_Snake_pos.Y+1; Next_pos.X = AI_Snake_pos.X; break;
        case 75: Next_pos.X = AI_Snake_pos.X-1; Next_pos.Y = AI_Snake_pos.Y; break;
        case 77: Next_pos.X = AI_Snake_pos.X+1; Next_pos.Y = AI_Snake_pos.Y; break;
	}
    
    if(Next_pos.X >= Width)           Next_pos.X = MinWidth+1;
    else if(Next_pos.X < MinWidth+1)  Next_pos.X = Width-1;
    if(Next_pos.Y >= Height)          Next_pos.Y = MinHeight+1;
    else if(Next_pos.Y < MinHeight+1) Next_pos.Y = Height-1;
    
	if(Hit(Next_pos.X,Next_pos.Y,2,0) || Hit(Next_pos.X,Next_pos.Y,1,0) || (Next_pos.X == Snake_pos.X+1 && Next_pos.Y == Snake_pos.Y) || (Next_pos.X == Snake_pos.X-1 && Next_pos.Y == Snake_pos.Y) || (Next_pos.X == Snake_pos.X && Next_pos.Y == Snake_pos.Y-1) || (Next_pos.X == Snake_pos.X && Next_pos.Y == Snake_pos.Y+1)){
		if(Old_Direction == 72){
			if(New_Direction == 72)       Changeifbody(75,72);
			else if(New_Direction == 75)  Changeifbody(77,72);
			else if(New_Direction == 77)  Changeifbody(80,72);
			else if(New_Direction == 80)  AI_Direction=Old_Direction;
		}else if(Old_Direction == 80){
			if(New_Direction == 80)       Changeifbody(75,80);
			else if(New_Direction == 75)  Changeifbody(77,80);
			else if(New_Direction == 77)  Changeifbody(72,80);
			else if(New_Direction == 72)  AI_Direction=Old_Direction;
		}else if(Old_Direction == 75){
			if(New_Direction == 75)       Changeifbody(72,75);
			else if(New_Direction == 72)  Changeifbody(80,75);
			else if(New_Direction == 80)  Changeifbody(77,75);
        	else if(New_Direction == 77)  AI_Direction=Old_Direction;
		}else if(Old_Direction == 77){
			if(New_Direction == 77)       Changeifbody(72,77);
			else if(New_Direction == 72)  Changeifbody(80,77);
			else if(New_Direction == 80)  Changeifbody(75,77);
			else if(New_Direction == 75)  AI_Direction=Old_Direction;
		}
	}else AI_Direction = New_Direction;
}

void Login(){
    int z=1;
    int i=0;
    char username[25];
    char m;
    char password[10];
    do{
    system("cls");
    if(z==3){
        cout<<"\n\n       Last Chance for Login!!!\n";
    }
    cout<<"\n\n   \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n";
    cout<<"\t      Project";
    cout<<"\n   \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n\n";
    cout<<"   \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd  LOGIN FORM  \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd  ";
    cout<<"\n\n   ENTER USERNAME: ";
    gets(username);
    cout<<" \n   ENTER PASSWORD: ";
    while(i<10){
        password[i]=getch();
        m=password[i];
        if(m==13){
            break;
        }
        else if(m==8){
            if(i==0){
                i--;
            }
            else if(i==1){
                i=i-2;
            }
        }
        else{
            cout<<"*";
        }
        i++;
    }
    password[i]='\0';
    if(strcmp(username,"FA21-BSE")==0 && strcmp(password,"DSA")==0){
        cout<<"\n   \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd";
        cout<<"  \n\n   WELCOME USER !!!!";
        cout<<"\n\n\n   Press any key to continue...";
        getch();
        system("cls");
        break;
    }
    else{
        cout<<"\n   \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd";
        if(strcmp(username,"FA21-BSE")!=0 && strcmp(password,"DSA")!=0){
            cout<<"\n\n   Invalid Username and Password !!!";
        }else if(strcmp(username,"FA21-BSE")!=0){
            cout<<"\n\n   Invalid Username !!!";
        }else if(strcmp(password,"DSA")!=0){
            cout<<"\n\n   Invalid Password !!!";
        }
        getch();
        z++;
        i=0;
    }
    }while(z<4);   //this loop will run 3 times only.
if (z==4){
    cout<<"\n\n   Sorry you have entered the wrong \n   username and password for three \n   times!!!\n";
    cout<<"\n   \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd";
    getch();
    exit(0);
}
}

void startLogo(){
	int minwidth = 5;
    int width = 155;
    int minheight = 10;
    int height = 27;
	int i=0,j=0;
	SetConsoleTextAttribute(H,0xf0);
	for(int i=minwidth;i<=width+4;i++){
		gotoxy(i-2,minheight-1);cout<<"";gotoxy(i-2,minheight);cout<<"-";gotoxy(i-2,height);cout<<"-";	gotoxy(i-2,height+1);cout<<"";
	}
	for(int j=minheight; j<height+1; j++){
		gotoxy(minwidth-2,j);cout<<"|";gotoxy(minwidth,j);cout<<"|";gotoxy(width,j);cout<<"|";gotoxy(width+2,j);cout<<"|";
	}j=6;
	SetConsoleTextAttribute(H,0xf1);
    int k=1; gotoxy(20,7); cout<<"O<**";    
    for(i=28;i<=76;){
    	if(i%6==0 && i!=50){
    		if(k==1) k=2;
    		else k=1;
		}if(k==1){
		gotoxy(i,j);cout<<"*";j--;
		}if(k==2){
    		gotoxy(i,j);cout<<"*";j++;
		}
		i+=2;
	}j=7;
	SetConsoleTextAttribute(H,0xf4);
	for(i=80;i<=130;){
    	if(i%6==0 && i!=50){
    		if(k==1) k=2;
    		else k=1;
		}if(k==1){
    		gotoxy(i,j);cout<<"*";j--;
		}if(k==2){
    		gotoxy(i,j);cout<<"*";j++;
		}i+=2;
	}
	gotoxy(132,6); cout<<"**>O";
	SetConsoleTextAttribute(H,0xf0);	
	gotoxy(((minwidth+width)/2)-6,33);	cout<<"DEVELOPED BY";
	gotoxy(((minwidth+width)/2)-16,35); cout<<"USMAN IQBAL, ARHAM NASIR, IBRAHIM";
	gotoxy(((minwidth+width)/2)-6,37); cout<<"FA21-BSE-014";
	gotoxy(((minwidth+width)/2)-6,39); cout<<"FA21-BSE-062";
	gotoxy(((minwidth+width)/2)-6,41); cout<<"FA21-BSE-131";
	//S
	j=12;
	for(i=20;i>=10;i--){
		gotoxy(i,j);cout<<"*";Sleep(10);
	}for(;j<=18;j++){
		gotoxy(i,j);cout<<"*";Sleep(10);
	}for(;i<=20;i++){
		gotoxy(i,j);cout<<"*";Sleep(10);
	}for(;j<=25;j++){
		gotoxy(i,j);cout<<"*";Sleep(10);
	}for(i=20;i>=9;i--){
		gotoxy(i,j);cout<<"*";Sleep(10);
	}
	//N
	i=40;
	for(j=12;j<=25;j++){
		gotoxy(i,j);cout<<"*";Sleep(10);
	}for(;j>=12;i--){
		gotoxy(i,j);cout<<"*";j--;
	}i=25;
	for(j=12;j<=26;j++){
		gotoxy(i,j);cout<<"*";Sleep(10);
	}	
	//A
	i=42;
	for(j=26;j>=13;i++){
		gotoxy(i,j);cout<<"*";gotoxy(i+1,j-1);cout<<"*";Sleep(10);j-=2;
	}for(j=12;j<=26;i++){
		gotoxy(i,j);cout<<"*";Sleep(10);j+=2;
	}
	j=20;
	for(i=46;i<=52;i++){
		gotoxy(i,j);cout<<"*";Sleep(10);
	}
	//K
	i=59;
	for(j=12;j<=26;j++){
		gotoxy(i,j);cout<<"*";Sleep(10);
	}i=73;
	for(j=12;j<=19;j++){
		gotoxy(i,j);cout<<"*";Sleep(10);i-=2;
	}i=59;
	for(j=19;j<=26;j++){
		gotoxy(i,j);cout<<"*";Sleep(10);i+=2;
	}	
	//E
	i=75;
	for(j=12;j<=26;j++){
		gotoxy(i,j);cout<<"*";Sleep(10);
	}i=87;
	for(;i>=75;i--){
		gotoxy(i,12);cout<<"*";	gotoxy(i,20);cout<<"*";	gotoxy(i,26);cout<<"*";	Sleep(10);
	}	
	//G
	j=12;
	for(i=108;i>=96;i--){
		gotoxy(i,j);cout<<"*";Sleep(10);
	}i=96;
	for(j=12;j<=25;j++){
		gotoxy(i,j);cout<<"*";Sleep(10);
	}for(;i<=111;i++){
		gotoxy(i,j);cout<<"*";Sleep(10);
	}for(;j>=21;j--){
		gotoxy(i,j);cout<<"*";Sleep(10);
	}for(;i>=100;i--){
		gotoxy(i,j);cout<<"*";Sleep(10);
	}
	//A
	i=113;
	for(j=26;j>=13;i++){
		gotoxy(i,j);cout<<"*";gotoxy(i+1,j-1);cout<<"*";Sleep(10);j-=2;
	}j=12;
	for(;j<=26;i++){
		gotoxy(i,j);cout<<"*";Sleep(10);j+=2;
	}j=20;
	for(i=118;i<=125;i++){
		gotoxy(i,j);cout<<"*";Sleep(10);
	}	
	//M
	i=128;
	for(j=12;j<=26;j++){
		gotoxy(128,j);cout<<"*";gotoxy(142,j);cout<<"*";Sleep(10);	
	}for(j=12;j<=18;j++){
		gotoxy(i,j);cout<<"*";Sleep(10);i++;
	}for(j=18;j>=12;j--){
		gotoxy(i,j);cout<<"*";Sleep(10);i++;
	}
	//E
	i=144;
	for(j=12;j<=26;j++){
		gotoxy(i,j);cout<<"*";Sleep(10);
	}for(i=153;i>=144;i--){
		gotoxy(i,12);cout<<"*";gotoxy(i,20);cout<<"*";gotoxy(i,26);cout<<"*";Sleep(10);
	}	
getch();
}
