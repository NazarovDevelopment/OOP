#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include "conlib.h"
#include "console.h"
#include<windows.h>
#include<time.h>
#include<stdlib.h>
 

//using namespace std;
//
//void initiation(int *maxX, int *maxY, int *count)
//{
//	srand(time(0));
//	MaxXY(maxX,maxY); 
//	cout << "Enter % of blocks:" << endl;
//	int tmp;
//	cin >> tmp;
//	// кол-во блоков: все * 0.tmp
//	*count = (*maxX) * (*maxY) * tmp / 100;
//}
//
//int* createField(int x, int y, int countBlocks)
//{
//	int* field = new int[x*y];
//	for (int i = 0; i < y; i++)
//		for	(int j = 0; j < x; j++)
//			field[i*y + j] = 0;
//	//граница
//		//вверх + низ
//	for (int i = 0; i < x; i++)
//	{
//		field[i] = 1;
//		field[(y-1)*y + i] = 1;
//	}
//		//бок
//	for (int i = 0; i < y; i++)
//	{
//		field[i*y] = 1;
//		field[i*y +x-1] = 1;
//	}
//	int tmp = 0;
//	int randX, randY;
//	while (tmp != countBlocks)
//	{
//		//исключаем границу
//		randX = 1 + rand() % (x-1);
//		randY = 1 + rand() % (x-1);
//		if (field[randY*y + randX] == 0 && (randY != y / 2 || randX != x / 2))
//		{
//			field[randY*y + randX] = 2;
//			tmp++;
//		}
//	}
//	return field;
//}
//
//void drawField(int* field, int x, int y)
//{
//	GotoXY(0, 0);
//	for (int i = 0; i < y; i++)
//	{
//		for (int j = 0; j < x; j++)
//		{
//			if (field[i*y + j] == 0) cout << " ";
//			if (field[i*y + j] == 1) cout << "#";
//			if (field[i*y + j] == 2) cout << "&";
//		}
//		cout << endl;
//	}
//}
//
//void play(int* field, int maxX, int maxY)
//{
//	int x = maxX / 2;
//	int y = maxY / 2;
//	GotoXY(x,y);
//	cout << "?";
//	int key = 0;
//	while(key != KEY_ESC)
//	{
//		while(!KeyPressed()); 
//		key = GetKey();
//		
//		GotoXY(x, y);
//		cout << " ";
//		if (key == KEY_UP && field[(y-1)*maxY + x] == 0) 
//			y--; 
//		if (key == KEY_DOWN && field[(y+1)*maxY + x] == 0) 
//			y++; 
//		if (key == KEY_LEFT && field[y*maxY + x-1] == 0) 
//			x--; 
//		if (key == KEY_RIGHT && field[y*maxY + x+1] == 0) 
//			x++;  
//		GotoXY(x, y);
//		cout << "?";
//	}
//}
struct ship{

	float x, y;
	float speed;
};
struct pula
{
	float x, y;
};
typedef struct ship SHIP;
typedef struct squere SQUERE;


SHIP *myShip = (struct ship*) malloc(sizeof(struct ship));
//SHIP *myShip = (struct ship*) malloc(sizeof(struct ship));
SHIP **bastards; 
pula *myPula = (struct pula*) malloc(sizeof(struct pula));

int Number = 15; 

void DrawMyShip(SHIP * myship);
void DrawOneBastards(SHIP* bastShip);
void DrawAllBasterds();
void RemoveAllBastards();
void update();
void RemoveMyShip(SHIP* myship);
void RemoveOneBastards(SHIP* bastShip);
void create_bastards(int n);
void DeleteAll();
int processing_collision(SHIP* myShip);
int collisionPula();
void ochko();

int minx = 5;
int miny = 2;
int maxx = 15;
int maxy = 40;

int flag = 0;
int flagPula = 0;
int points = 0;
int lives = 3;

void ramka()
{
	int i =0;
	for (i = 0; i < maxx+5; i++)
	{
		GotoXY(i, 0);
	printf("*");

	}

	i = 0;
	for (i = 0; i < maxy+5; i++)
	{
		GotoXY(0, i);
		printf("*");
		
	}

	i = 0;
	for (i = 0; i < maxx+7; i++)
	{
		GotoXY(i, maxy+5);
		printf("*");
	
	}

	i = 0;
	for (i = 0; i < maxy+5; i++)
	{
		GotoXY(maxx+7, i);
		printf("*");
	
	}

	i = 0;
}
void DrawMyShip(SHIP * myship)
{
	GotoXY((int)myship->x, (int)myship->y);
	printf("^");

	GotoXY((int)myship->x - 1, (int)myship->y + 1);
	printf("/");

	GotoXY((int)myship->x, (int)myship->y + 1);
	printf("|");

	GotoXY((int)myship->x + 1, (int)myship->y + 1);
	printf("\\");

}

void DrawOneBastards(SHIP* bastShip)
{
	GotoXY(bastShip->x, bastShip->y);
	printf("*");

	GotoXY(bastShip->x - 1, bastShip->y - 1);
	printf("\\");

	GotoXY(bastShip->x, bastShip->y - 1);
	printf("|");

	GotoXY(bastShip->x + 1, bastShip->y - 1);
	printf("/");
}

void DrawAllBasterds()
{
	int i;
	for (i = 0; i < Number; i++)
	{
		DrawOneBastards(bastards[i]);
	}
}
void createPula()
{
	myPula->x = myShip->x;
	myPula->y = myShip->y;

	flagPula = 1;
}

void removePula()

{
	GotoXY(myPula->x, myPula->y);
	printf(" ");
}
void RemoveAllBastards()
{
	int i;

	for (i = 0; i < Number; i++)
		RemoveOneBastards(bastards[i]);
}

void update()
{
	int i;
	srand(time(0));

	//ClearConsole();
	RemoveAllBastards();
	for (i = 0; i < Number; i++)
	{
		bastards[i]->y = bastards[i]->y + bastards[i]->speed;
	}

		
	for (i = 0; i < Number; i++)
	{
		if (bastards[i]->y >= maxy+3)
		{
			bastards[i]->y = miny;
			bastards[i]->x = minx + rand()%maxx;
			bastards[i]->speed = 0.3 + 0.5 *(rand() % 3);
		}
	}

	if (flagPula)
	{
		removePula();

		myPula->y = myPula->y - 1.6 ;

		GotoXY(myPula->x, myPula->y);
		printf("@");

		if (myPula->y <= miny+1)
		{
			flagPula = 0;

			removePula();
		}
	}

	DrawAllBasterds();

	if (!processing_collision(myShip))
	{
		return;
	}
	if (flagPula)
	collisionPula();
}

void RemoveMyShip(SHIP* myship)
{
	GotoXY(myship->x, myship->y);
	printf(" ");

	GotoXY(myship->x - 1, myship->y + 1);
	printf(" ");

	GotoXY(myship->x, myship->y + 1);
	printf(" ");

	GotoXY(myship->x + 1, myship->y + 1);
	printf(" ");
}

void RemoveOneBastards(SHIP* bastShip)
{
	GotoXY(bastShip->x, bastShip->y);
	printf(" ");

	GotoXY(bastShip->x - 1, bastShip->y - 1);
	printf(" ");

	GotoXY(bastShip->x, bastShip->y - 1);
	printf(" ");

	GotoXY(bastShip->x + 1, bastShip->y - 1);
	printf(" ");
}

void create_bastards(int n)
{
	int i;
	srand(time(0));

	Number = n;

	for (i = 0; i < Number; i++)
	{
		bastards[i] = (SHIP*)malloc(sizeof(SHIP));
		bastards[i]->x = minx + rand() % maxx;
		bastards[i]->y = miny+4;
		bastards[i]->speed = 0.3 + 0.5 *(rand() % 3);
	}
}

void DeleteAll()
{
	int i;
	free(myShip);
	for (i = 0; i < Number; i++)
	{
		free(bastards[i]);
	}
	free(bastards);
}

void table()
{ 
	GotoXY(maxx + 10, miny + 4);
	printf("SCORE");
	ochko();
	GotoXY(maxx + 10, miny + 8);
	printf("LIVES");
	GotoXY(maxx + 10, maxy);
	printf("EXIT ESC");
}

void ochko()
{
	GotoXY(maxx + 10, miny + 6);
	printf("%d", points);

}

int processing_collision(SHIP* myship)
{
	int i;
	for (i = 0; i < Number; i++)
	{
		if (bastards[i]->y >= myShip->y)
		{
			if ((((bastards[i]->x - 1) >= (myShip->x - 1)) && ((bastards[i]->x - 1) <= (myShip->x + 1))) 
				|| (((bastards[i]->x + 1) >= (myShip->x - 1)) && ((bastards[i]->x + 1) <= (myShip->x + 1))))
			{
				flag = 1;
				bastards[i]->y = miny;
				bastards[i]->x = minx + rand() % maxx;
				bastards[i]->speed = 0.3 + 0.5 *(rand() % 3);
				return 0;
			}
		}
	}
}

int collisionPula()
{
	int i;
	for (i = 0; i < Number; i++)
	{
		if (bastards[i]->y >= myPula->y)
		{
			if (((bastards[i]->x - 1) <= (myPula->x)) && ((bastards[i]->x + 1) >= (myPula->x)))
			{
				removePula();
				RemoveOneBastards(bastards[i]);
				bastards[i]->y = miny;
				bastards[i]->x = minx + rand() % maxx;
				bastards[i]->speed = 0.3 + 0.5 *(rand() % 3);

				flagPula = 0;
				points = points + 1;
				ochko();
				return 0;
			}
		}
	}
	return 0;
}
int main()
{
	/*int maxX, maxY, countBlocks;
	initiation(&maxX,&maxY,&countBlocks);
	int* field = createField(maxX, maxY, countBlocks);
	drawField(field, maxX, maxY);	
	play(field, maxX, maxY);
	ClearConsole();
	GotoXY(maxX/2, maxY/2);
	cout << "Please press any key" << endl;*/
	
	int key = 0;
	int MaxY;
	int MaxX;
	int x, y;

	//SHIP *myShip = (struct ship*) malloc(sizeof(struct ship));
	
	bastards = (struct ship**) malloc(Number* sizeof(struct ship*));;

	MaxXY(&x, &y);
	myShip->x = minx;
	myShip->y = maxy;
	myShip->speed = 0;

	create_bastards(Number);

	while (lives > 0)
	{

		DrawMyShip(myShip);
		ramka();
		table();


		while (1)
		{
			if (!KeyPressed())
			{
				Sleep(100);
				update();

				if (flag)
				{
					lives = lives - 1;
					//MessageBeep(MB_ICONQUESTION);
					Beep(750, 300);

					ClearConsole();
					GotoXY(maxx / 3, maxy / 2);
					printf("GAME OVER, LOSER!");
					flag = 0;
					Sleep(1000);
					break;
					
				}
				DrawMyShip(myShip);
			}
			else
			{
				key = GetKey();
				RemoveMyShip(myShip);

				if (key == KEY_LEFT)
				{
					if (myShip->x > minx)
						myShip->x--;
				}

				if (key == KEY_RIGHT)
				{
					if (myShip->x < maxx)
					{
						myShip->x++;
					}
				}
				if (key == KEY_UP && flagPula == 0)
				{
					createPula();
				}
				if (key == KEY_ESC)
				{
					return 0;
				}
				DrawMyShip(myShip);
			}

		}
		ClearConsole();

	}
	getchar();
	
	return 0;
}

