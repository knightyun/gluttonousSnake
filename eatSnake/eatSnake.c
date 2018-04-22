#include<stdio.h>
#include<Windows.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
#include<windows.graphics.h>
#define X 50
#define Y 15
#define SPEED 100
int mapArr[X][Y];
void initMap()
{
	int x, y;
	for (y = 0; y < Y; y++)
	{
		for (x = 0; x < X; x++)

		{
			if ((x == 0) || (x == X - 1) || (y == 0) || (y == Y - 1))
			{
				mapArr[x][y] = 1;
			}
			else
			{
				mapArr[x][y] = 0;
			}
		}
	}
}
/* set a random print point in the background */
int a = -1, b = -1;
int foodFlag = 0;
void setRandNum()
{
	srand(time(0));
	while ((mapArr[a + 1][b + 1] != 0) && (foodFlag == 0))
	{
		a = rand() % (X - 2), b = rand() % (Y - 2);
	}
	mapArr[a + 1][b + 1] = 3; /* set foot number 3 */
	foodFlag = 1;
}
void printMap()
{
	int x, y;
	for (y = 0; y < Y; y++)
	{
		for (x = 0; x < X; x++)
		{
			switch (mapArr[x][y])
			{
			case 0:
				printf(" ");
				break;
			case 1:
				printf("+");
				break;
			case 2:
				printf("*");
				break;
			case 3:
				printf("@");
			}
		}
		printf("\n");
	}
}
void startMsg()
{
	printf
	("press '2(top)', '8(down)', '4(left)', 6(right)'\nor 'w(top)', 'a(left)', 's(down)', 'd(right)'\nto control the snake\n");
}
int sx = 1, sy = 1;				/* head x, y */
int l = 4;					/* body lenth */
int *belly[X * Y];				 /* body */
char input = '6';         /* default direction */
void setSnakeNum()
{
	if (_kbhit())
	{
		int a = _getch();    /* if there is an input, get it; if not, go on*/
		switch (input)
		{
		case '2':
		case '8':
		case 'w':
		case 's':
			if (a == '4' || a == '6' || a == 'a' || a == 'd')
				input = a;
			break;
		case '4':
		case '6':
		case 'a':
		case 'd':
			if (a == '2' || a == '8' || a == 'w' || a == 's')
				input = a;
			break;
		}
	}
	switch (input)       /* judge the direction by value of input*/
	{
	case '2':    /* up */
	case 'w':
		sy--;
		break;
	case '8':   /* down */
	case 's':
		sy++;
		break;
	case '4':   /*  left */
	case 'a':
		sx--;
		break;
	case '6':   /* right */
	case 'd':
		sx++;
		break;
	}
	int i;
	for (i = l; i != 0; i--)
	{
		belly[i] = belly[i - 1];
		*belly[i] = 2;
	}
	belly[0] = &mapArr[sx][sy];
	*belly[0] = 2;
}
int overFlag = 1;
void gameOver()
{

}
void eatFood()
{
	if (*belly[0] == 3)
	{
		l++;
		foodFlag = 0;
	}
}
void judgeEitWall()
{
	if (*belly[0] == 1)
		overFlag = 0;
}
void judgeEatSelf()
{
	if (*belly[0] == 2)
		overFlag = 0;
}
void startGame()
{
	int j;
	for (j = 0; j < l; j++)
	{
		belly[j] = &mapArr[sx - j][sy];
	}
	while (overFlag)
	{
		initMap();
		setSnakeNum();
		setRandNum();
		eatFood();
		printMap();
		startMsg();
		Sleep(SPEED);
		system("cls");
	}
	system("cls");
	printf("Game Over !!!");
	system("pause");

}
int main()
{
	startGame();
}