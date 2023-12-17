#include<iostream>
#include<windows.h>

using namespace std;

// Functions of the game
void gotoxy(int x, int y);
void printPlayer();
void erasePlayer();
void movePlayerLeft();
void movePlayerRight();
void movePlayerUp();
void movePlayerDown();
void printEnemy();
void eraseEnemy();
void moveEnemy();
void printMaze();
void printEnemy1();
void eraseEnemy1();
void moveEnemy1();
void printEnemy2();
void eraseEnemy2();
void moveEnemy2();
void Bullet();
void Shoot();
void displayScore();



// Variables of the game
int eX = 1, eY = 1;
int pX = 26, pY = 20;
int eX1 = 60, eY1 = 1;
int eX2 =1, eY2 = 5;
int bulletX, bulletY;
bool eXpattrol = false;
bool eYpattrol = false;

int enemyHealth = 1;
int enemyHealth2 = 1;
int enemyHealth1 = 1;
int score = 0;

bool Shooting = false;


char getCharAtxy(short int x, short int y)
{
 CHAR_INFO ci;
 COORD xy = {0, 0};
 SMALL_RECT rect = {x, y, x, y};
 COORD coordBufSize;
 coordBufSize.X = 1;
 coordBufSize.Y = 1;
 return ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, coordBufSize, xy, &rect) ? ci.Char.AsciiChar
: ' ';
}
int main()
{
    system("cls");
    printMaze();
    printEnemy();
    printEnemy1();
    printEnemy2();
    
	
    while(true)
{
    	if(GetAsyncKeyState(VK_LEFT))
	{
	    movePlayerLeft();
	}
	
    	if(GetAsyncKeyState(VK_RIGHT))
	{
	      movePlayerRight();
	}
	if(GetAsyncKeyState(VK_UP))
	{
		movePlayerUp();
	}
	if(GetAsyncKeyState(VK_DOWN))
	{
		movePlayerDown();
	}
	if(GetAsyncKeyState(VK_SPACE))
	{
		Bullet();
	}
	 if(enemyHealth != 0)
	 {
        moveEnemy();
	 }	
	 else{
		eraseEnemy();
	 }
    if(enemyHealth1 != 0)
	{
        moveEnemy1();
	}	
    else{
		eraseEnemy1();
	}
	if(enemyHealth2 != 0)
	{
	    moveEnemy2();
	}
    else{
		eraseEnemy2();
	}
     
	 displayScore();
	 Shoot();
	 if(enemyHealth == 0 && enemyHealth1 == 0 && enemyHealth2 == 0)
	 {
		system("cls");
		gotoxy(45, 15);
		cout<< "GAME IS OVER!!"
		    << "   YOU WON    "<<endl;
			Sleep(2500);
			false;
    } 
	 Sleep(40);
}
	return 0;
}

void printEnemy()
{
	gotoxy(eX,eY);
	cout<< "(~~~)  (~~~)";
    gotoxy(eX,eY+1);
	cout<< "|=| |  | |=|";
   	gotoxy(eX,eY+2);
	cout<< "    !!!!    ";
}
void eraseEnemy()
{
	gotoxy(eX,eY);
	cout<< "             ";
    gotoxy(eX,eY+1);
	cout<< "             ";
   	gotoxy(eX,eY+2);
	cout<< "             ";
}
void moveEnemy()
{
        eraseEnemy();
		if(!eXpattrol)
	{	
		eX=eX+1;
    
	if(eX==50)
	{
		eXpattrol=true;
	}
	}
if(eXpattrol)
{
	eX=eX-1;
	if(eX==1)
	eXpattrol=false;
}
printEnemy();
}
void printEnemy1()
{
	gotoxy(eX1,eY1);
	cout<< "       |||       ";
    gotoxy(eX1,eY1+1);
	cout<< "     |.|.|.|     ";
   	gotoxy(eX1,eY1+2);
	cout<< " [-------------] ";
}
void eraseEnemy1()
{
	gotoxy(eX1,eY1);
	cout<< "                 ";
    gotoxy(eX,eY1+1);
	cout<< "                 ";
   	gotoxy(eX1,eY1+2);
	cout<< "                 ";
	
}
void moveEnemy1()
{
        eraseEnemy1();
		if(!eYpattrol)
	{	
		eY1=eY1+1;
    
	if(eY1==15)
	{
		eYpattrol=true;
	}
	}
if(eYpattrol)
{
	eY1=eY1-1;
	if(eY1==5)
	eYpattrol=false;
}
printEnemy1();
}
void printEnemy2()
{
	gotoxy(eX2,eY2);
	cout<<   "      [||]       ";
    gotoxy(eX2,eY2+1);
	cout<<   "   [||||||||]    ";
   	gotoxy(eX2,eY2+2);
	cout<<   "[|~|~|~|~|~|~|]  ";
}	
void eraseEnemy2()
{
	gotoxy(eX2,eY2);
	cout<< "                 ";
    gotoxy(eX2,eY2+1);
	cout<< "                 ";
   	gotoxy(eX2,eY2+2);
	cout<< "                 ";
}
void moveEnemy2()
{
        eraseEnemy2();
		static bool movediagonaldown=true;
		if(movediagonaldown)
	{	
		eX2=eX2+1, eY2=eY2+1;
    
	if(eX2==11&&eY2==15)
	{
		movediagonaldown=false;
	}
	}
else{
	eX2=eX2-1, eY2=eY2-1;
	if(eX2==1&&eY2==5)
	movediagonaldown=true;
}
printEnemy2();
}
void printMaze()
{
	cout<< "########################################################################################################" <<endl;
	cout<< "#                                                                                                      #" <<endl;
	cout<< "#                                                                                                      #" <<endl;
	cout<< "#                                                                                                      #" <<endl;
	cout<< "#                                                                                                      #" <<endl;
	cout<< "#	                         					                                                       #" <<endl;
	cout<< "#                                                                                                      #" <<endl;
	cout<< "#                                                                                                      #" <<endl;
	cout<< "#                                                                                                      #" <<endl;
	cout<< "#                                                                                                      #" <<endl;
	cout<< "#                                                                                                      #" <<endl;
	cout<< "#                                                                                                      #" <<endl;
	cout<< "#                                                                                                      #" <<endl;
	cout<< "#                                                                                                      #" <<endl;
	cout<< "#                                                                                                      #" <<endl;
	cout<< "#                                                                                                      #" <<endl;
	cout<< "#                                                                                                      #" <<endl;
	cout<< "#                                                                                                      #" <<endl;
	cout<< "#                                                                                                      #" <<endl;
	cout<< "#                                                                                                      #" <<endl;
	cout<< "#                                                                                                      #" <<endl;
	cout<< "#                                                                                                      #" <<endl;
	cout<< "#                                                                                                      #" <<endl;
	cout<< "#                                                                                                      #" <<endl;
	cout<< "#                                                                                                      #" <<endl;
	cout<< "########################################################################################################" <<endl;
}
void printPlayer()
{
	gotoxy(pX,pY);
	cout<< "     ||||     ";
	gotoxy(pX,pY+1);
	cout<< "  __|~~~~|__   ";
	gotoxy(pX,pY+2);
	cout<< "/   |    |   \\ ";
  	gotoxy(pX,pY+3);
  	cout<< "=====.  .=====  ";
	gotoxy(pX,pY+4);
	cout<< "     ||||       ";
}
void movePlayerLeft()
{
	if(getCharAtxy(pX - 1, pY) == ' ')
   	{
   	erasePlayer();
	pX = pX - 1;
    printPlayer();
	}
}
void movePlayerRight()
{
	if(pX + 15 < 100 && getCharAtxy(pX + 15, pY) == ' ')
	{
	erasePlayer();
	pX = pX + 1;
	printPlayer();
	}
}
void movePlayerUp()
{
	if(pY > 1 && getCharAtxy(pX, pY - 1) == ' ')
	{
		erasePlayer();
		pY--;
		printPlayer();
	}
}
void movePlayerDown()
{
	if(pY + 5< 24 && getCharAtxy(pX, pY + 6 ))
	{
		erasePlayer();
		pY++;
		printPlayer();
	}
}

void erasePlayer()
{
	gotoxy(pX,pY);
	cout<< "               ";
	gotoxy(pX,pY+1);
	cout<< "               ";
	gotoxy(pX,pY+2);
	cout<< "               ";
  	gotoxy(pX,pY+3);
  	cout<< "               ";
	gotoxy(pX,pY+4);
	cout<< "               ";
}
void gotoxy(int x, int y)
{
   COORD coordinates;
   coordinates.X = x;
   coordinates.Y = y;
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

void Bullet()
{
	if(!Shooting)
	{
		Shooting = true;
        bulletX = pX + 5;
		bulletY = pY - 1;
		gotoxy(bulletX, bulletY);
		cout << "^";
	}
}

void Shoot()
{
	// if(!Shooting)
	// {
	//	Shooting = true;
    //  bulletX = pX + 5;    position of bullet
	//	bulletY = pY - 1;

	// }
      gotoxy(bulletX, bulletY);
	  cout << " ";
	  bulletY = bulletY - 1;
	  if(bulletY < 0)
	  {
		Shooting = false;
	  }
	  else{
		gotoxy(bulletX, bulletY);
		cout << "^";
	  }
}

void displayScore()
{
	gotoxy(120, 19);
	cout<< "&&&&&&&&&&&&&&&&&&&&&&&&&&&&"<<endl;
	gotoxy(120, 20);
	cout<< "Score: "<<score<<endl;
	gotoxy(120, 21);
	cout<< "Health of enemy 1: "<<enemyHealth<<endl;
	gotoxy(120, 22);
	cout<< "Health of enemy 2: "<<enemyHealth1<<endl;
	gotoxy(120, 23);
	cout<< "Health of enemy 3: "<<enemyHealth2<<endl;
	gotoxy(120, 24);
	cout<< "&&&&&&&&&&&&&&&&&&&&&&&&&&&&"<<endl;
}

