#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <string>
#include <cstdlib>
using namespace std;

void textColor(int x)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}
void gotoxy(int x, int y)
{
	HANDLE hCon;
	COORD dwPos;

	dwPos.X = x;
	dwPos.Y = y;

	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hCon, dwPos);
}
void clearScreen() //czyszczenie ekranu
{
	HANDLE hOut;
	COORD Position;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}
void hidecursor() //fix for bliking
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

int width, height;
char map[50][50]; //creates whole map
int HP;
int runda = 1;
int points, playerX, playerY, enemyX, enemyY, shotX, shotY, speed, speedShot;
int button; //button used to move
int fall; //var for falling 
bool isFlying; //to check if shot is flyfing
string kierunek;

void brick(int height)
{
	if (points==0)
	{
		for (int i = 0; i < width; i++)
		{
			map[i][height] = 'b';
		}
	}


}
void line()
{
	for (int i = 0; i <= width; i++)
	{
		cout << "--";
	}
}
void menu()
{
	cout << "Sterownie: \n A - w lewo \n B - w prawo \n W - strzal" << endl;
	cout << "Runda: " << runda << endl;
	cout << "Podaj predkosc od 2 do 20 (5 default)" << endl;
	cin >> speed;
	if (speed < 2 || speed > 20)
	{
		cout << "Glupi ? Predkosc ustawiona na 5" << endl;
		speed=5;
	}
	cout << "Podaj predkosc pilki od 1 do 3 (2 default)" << endl;
	cin >> speedShot;
	if (speed < 1 || speed > 3)
	{
		cout << "Glupi ? Predkosc ustawiona na 2" << endl;
		speedShot = 2;
	}
}


int main()
{
	
		SetConsoleTitle(TEXT("Spaceship Game"));
		srand(time(NULL));

	height = 25;
	width = 30;
	fall = 0;
	HP = 3;
	points = 0;
	playerX = width / 2;
	playerY = height - 1;
	shotX = playerX;
	shotY = playerY - 1;

	menu();

	system("cls");
		hidecursor();
	bool work = true;
	string confirm;
	string kierunek="upLeft"; //upLeft upRight downLeft downRight
	while (work) //drawing board
	{

		gotoxy(0, 0);
		map[playerX][playerY] = 'x';      //seting players pos
		map[playerX + 1][playerY] = 'x';
		map[playerX - 1][playerY] = 'x';
		map[shotX][shotY] = 'd';  //seting shot's pos

		if (HP == 0)work = false; //stoping loop if hp is 0
		if (points == 30)runda = 2;
		if (runda == 1)
		{
			brick(4);
		}
		else if (runda == 2)
		{
			brick(4);
			brick(5);
		}
		textColor(255);
		line();//upper line
		

		//creates bricks
		cout << endl;
		for (int i = 0; i <= height; i++) //left and right walls 
		{
			cout << "|";
			for (int j = 0; j < width; j++)
			{
				if (map[j][i] == 'x') //darwing player's positon
				{
					textColor(255);
					cout << "xx";
					textColor(7);
				}
				else if (map[j][i] == 'd') //darwing shot's positon
				{
					textColor(7);
					cout << "oo";
					textColor(255);
				}
				else if (map[j][i] == 'b') //darwing brick's positon
				{
					textColor(10);
					cout << "##";
					textColor(255);
				}
				else
				{
					textColor(7);
					cout << "  ";
					textColor(255);
				}

			}
			cout << "|" << endl;
		}
		line();//lower line
		textColor(7);
		cout << endl << "Punkty ";
		textColor(10);
		cout << points;
		textColor(7);
		cout << "|HP ";
		textColor(4);
		cout << HP;
		textColor(7);
		cout << "Runda: " << runda;

	if (fall % speedShot == 0) // w celu mozliwosci kontroli predkosci pilki
	{	if (isFlying)
			{
				if (shotY > (height-1))
				{
					isFlying = false;
					map[shotX][shotY] = 'p';
					shotX = playerX;
					shotY = playerY;
					kierunek = "upLeft";
					HP--;
				}
				
				if (map[shotX - 1][shotY - 1] == 'b' && kierunek == "upLeft")//odbijanie od cekiełek przy uderzeniu pod katem od dołu z lewej strony
				{
					map[shotX - 1][shotY - 1] = ' ';
					points++;
					kierunek = "downRight";
				}
				else if (map[shotX + 1][shotY - 1] == 'b' && kierunek == "upRight") //odbijanie od cekiełek przy uderzeniu pod katem od dołu z prawej strony
				{
					map[shotX + 1 ][shotY - 1] = ' ';
					points++;
					kierunek = "downLeft";
				}
				else if (map[shotX - 1 ][shotY + 1] == 'b' && kierunek == "downRight") //odbijanie od cekiełek przy uderzeniu pod katem od góry  z prawej strony
				{
					map[shotX - 1][shotY + 1] = ' ';
					points++;
					kierunek = "upLeft";
				}
				else if (map[shotX + 1][shotY + 1] == 'b' && kierunek == "downLeft") //odbijanie od cekiełek przy uderzeniu pod katem od góry  z lewej strony
				{
					map[shotX + 1][shotY + 1] = ' ';
					points++;
					kierunek = "upRight";
				}
				else if (map[shotX][shotY - 1] == 'b' && kierunek == "upLeft")//odbijanie od cekiełek przy uderzeniu pod katem od dołu z lewej strony
				{
					map[shotX][shotY - 1] = ' ';
					points++;
					kierunek = "downRight"; 
				}
				else if (map[shotX][shotY - 1] == 'b' && kierunek == "upRight") //odbijanie od cekiełek przy uderzeniu od dołu z prawej strony
				{
					map[shotX][shotY - 1] = ' ';
					points++;
					kierunek = "downLeft";
				}
				else if (map[shotX][shotY + 1] == 'b' && kierunek == "downRight") //odbijanie od cekiełek przy uderzeniu od góry  z prawej strony
				{
					map[shotX][shotY + 1] = ' ';
					points++;
					kierunek = "upLeft";
				}
				else if (map[shotX][shotY + 1] == 'b' && kierunek == "downLeft") //odbijanie od cekiełek przy uderzeniu od góry  z lewej strony
				{
					map[shotX][shotY + 1] = ' ';
					points++;
					kierunek = "upRight";
				}
				else if (shotY == playerY - 1 && (shotX == playerX || shotX == playerX + 1 || shotX == playerX - 1) && kierunek == "downRight") //odbijanie od rekietki przy uderzeniu z prawej strony
				{
					kierunek = "upLeft";
				}
				else if (shotY == playerY - 1 && (shotX == playerX || shotX ==  playerX + 1 || shotX ==  playerX - 1) && kierunek == "downLeft") //odbijanie od rekietki przy uderzeniu z prawej strony
				{
					kierunek = "upRight";
				}
				else if (shotX < 1 && kierunek == "downRight") //odbijanie od w doł lewej scianki przy uderzeniu od dołu z prawej strony
				{
					kierunek = "downLeft";
				}
				else if (shotX > (width-2) && kierunek == "downLeft") //odbijanie od w dół prawej scianki przy uderzeniu od dołu z lewej strony
				{
					kierunek = "downRight";
				}
				else if (shotX < 1)  //odbijanie w góre przy uderzeniu w lewa scianke
				{
					kierunek = "upRight";

				}
				else if (shotX >(width - 2)) //odbijanie w góre przy uderzeniu w prawa scianke
				{
					kierunek = "upLeft";
				}
				else if (shotY < 1 && kierunek == "upRight") //odbijanieod sufitu w lewo
				{
					kierunek = "downLeft";

				}
				else if (shotY < 1 && kierunek == "upLeft") //odbijanieod sufitu w prawo
				{
					kierunek = "downRight";

				}
				map[shotX][shotY] = 'p';
				//instrukcje co do kierunków 
				if (kierunek == "upLeft") 
				{
					shotX--;
					shotY--;
				}
				else if (kierunek == "upRight")
				{
					shotX++;
					shotY--;

				}
				else if (kierunek == "downLeft")
				{
					shotX++;
					shotY++;

				}
				else if (kierunek == "downRight")
				{
					shotX--;
					shotY++;
				}
			}
	}	//pobieranie klawisza
		if (_kbhit())
		{
			button = _getch();
			switch (button)
			{
			case 97: //moving left 
			{
				if (playerX > 1)
				{
					map[playerX][playerY] = 'p';
					map[playerX + 1][playerY] = 'p';
					map[playerX - 1][playerY] = 'p';
					playerX--;
					if (!isFlying)
					{
						map[shotX][shotY] = 'p';
						shotX = playerX;

					}
				}
			}
			break;
			case 100: //moving right
			{
				if (playerX < (width - 1))
				{
					map[playerX][playerY] = 'p';
					map[playerX + 1][playerY] = 'p';
					map[playerX - 1][playerY] = 'p';
					playerX++;
					if (!isFlying)
					{
						map[shotX][shotY] = 'p';
						shotX = playerX;
					}
				}
			}
			break;
			case 119: // for shoting
			{
				if (!isFlying)
				{
					map[shotX][shotY] = 'p';
					isFlying = true;
				}
			}
			break;
			}
		}

		fall++;
		Sleep(speed * 10);
	}
	system("cls");
	cout << "GAME OVER" << endl;
	cout << "Twoje punkty ";
	textColor(10);
	cout << points << endl;
	textColor(7);
	cout << "jesli chcesz zagrac pownownie wpisz 'tak'" << endl;
	cin >> confirm;
	if (confirm == "tak")
	{
		map[playerX][playerY] = ' ';
		map[playerX + 1][playerY] = ' ';
		map[playerX - 1][playerY] = ' ';
		map[shotX][shotY] = ' ';
		runda = 1;
		main();
	}
	system("pause");
	return 0;
}
