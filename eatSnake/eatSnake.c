#include <stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<Windows.h>
#include<time.h>
#define X 50
#define Y 15
#define SPEED 300000
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
/* set a random print point ih the background */
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
int x = 1, y = 1;
int flag = 0;
void setMoveNum()
{
	/*
	x move 1 -- (X - 2 ); y move 1 -- (Y - 2) */
	/* move x from left to right */
	if ((y == 1 + flag) && (x < X - 2 - flag))
	{
		mapArr[x][y] = 2;
		x++;
	}
	/* move y from top to buttom */
	else if ((x == X - 2 - flag) && (y < Y - 2 - flag))
	{
		mapArr[x][y] = 2;
		y++;
	}
	/* move x from right to left */
	else if ((y == Y - 2 - flag) && (x > 1 + flag))
	{
		mapArr[x][y] = 2;
		x--;
	}
	/* move y from buttom to top */
	else if ((x == 1 + flag) && (y > 1 + flag))
	{
		mapArr[x][y] = 2;
		y--;
		if (y == 2 + flag)
		{
			flag++;
		}
	}
}
/* judge the end of moving */
void judgeEnd()
{
	int i, j;
	int tmp = 1;
	for (j = 1; j < Y - 1; j++)
	{
		for (i = 1; i < X - 1; i++)
		{
			tmp *= mapArr[i][j];
		}
	}
	// printf("%d\n", tmp);
	if (tmp != 0)
	{
		flag = 0;
	}
}
int sx = 1, sy = 1;
int l = 3;
char input = '6';
char inputB = '6';
int belly[X * Y];
void setSnakeNum()
{
	if (kbhit())
	{
		int a = getch();
		if (a == '2' || a == '4' || a == '6' || a == '8' || a == 'w' || a == 'a' || a == 's'
			|| a == 'd')
		{
			input = a;
		}
	}
	switch (input)
	{
	case '2':
	case 'w':
		sy--;
		break;
	case '8':
	case 's':
		sy++;
		break;
	case '4':
	case 'a':
		sx--;
		break;
	case '6':
	case 'd':
		sx++;
		break;
	}
	mapArr[sx][sy] = 2;
}
void startMsg()
{
	printf
	("press '2(top)', '8(down)', '4(left)', 6(right)'\nor 'w(top)', 'a(left)', 's(down)', 'd(right)'\nto control the snake\n");
}
void startGame()
{
	while (1)
	{
		initMap();
		/* setMoveNum(); */
		setSnakeNum();
		setRandNum();
		printMap();
		startMsg();
		judgeEnd();
		Sleep(SPEED);
		system("cls");
	}
}
int main()
{
	startGame();
}