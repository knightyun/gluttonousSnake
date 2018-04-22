#include <stdio.h>
#include<Windows.h>
#include<conio.h>
#include<stdlib.h>
#define X 50
#define Y 15
#define SPEED 500
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
	mapArr[a + 1][b + 1] = 3;
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

int sx = 1, sy = 1, ssx, ssy;
int l = 3;
char input = '6';
void setSnakeNum()
{
	//	mapArr[sx-1][sy] =mapArr[sx][sy];
	ssx = sx, ssy = sy; 
	//sssx = sx, sssy = sy;
	if (_kbhit())
	{
		int a = _getch();
		if (a == '2' || a == '4' || a == '6' || a == '8' || a == 'w' || a == 'a' || a == 's'
			|| a == 'd')
		{
			input = a;
		}
	}
	switch (input)
	{
	case '2':    /* up */
	case 'w':
		ssy = sy--;

		break;
	case '8':   /* down */
	case 's':
		ssy = sy++;
		
		break;
	case '4':   /* left */
	case 'a':
		ssx = sx--;

		break;
	case '6':   /* right */
	case 'd':
		ssx = sx++;

		break;
	}
	mapArr[sx][sy] = 2;   /* head */
	mapArr[ssx][ssy] = 2;

	// mapArr[sssx][sssy] = 2;
}
void startGame()
{
	while (1)
	{
		initMap();
		setSnakeNum();
		setRandNum();
		printMap();
		startMsg();
		Sleep(SPEED);
		system("cls");
	}
}
int main()
{
	startGame();
}