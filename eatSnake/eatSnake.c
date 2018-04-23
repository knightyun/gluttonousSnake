#include<stdio.h>
#include<Windows.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
#include<windows.graphics.h>
#define X 50
#define Y 20
#define SPEED 100
int mapArr[X][Y];
int randX = -1, randY = -1; /* set a random food point in the background */
int foodFlag = 0;      /* judge when to change random food point*/
int sx = 1, sy = 1;				/* body x, y point */
int l = 0;						/* body lenth */
int *body[X * Y];				/* body array */
char input = '6';				/* default direction */
int overFlag = 1;       /* judge when the game over, hit wall or eat self*/
int moveX = 1, moveY = 1;    /* start move effect */
int moveFlag = 0;

void InitMap() /* initialize the background coordinate system */
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

void PrintMap()
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

void StartMsg()
{
	printf
	("press '2(top)', '8(down)', '4(left)', 6(right)'\nor 'w(top)', 'a(left)', 's(down)', 'd(right)'\nto control the snake\n");
}

void SetRandNum()
{
	srand(time(0));
	while ((mapArr[randX + 1][randY + 1] != 0) && (foodFlag == 0))
	{
		randX = rand() % (X - 2), randY = rand() % (Y - 2);
	}
	mapArr[randX + 1][randY + 1] = 3;	/* set foot number 3 */
	foodFlag = 1;
}

void SetSnakeNum()
{
	if (_kbhit())
	{
		int a = _getch();		/* if there is an input, get it; if not, go on
								*/
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
	switch (input)				/* judge the direction by value of input */
	{
	case '2':					/* up */
	case 'w':
		sy--;
		break;
	case '8':					/* down */
	case 's':
		sy++;
		break;
	case '4':					/* left */
	case 'a':
		sx--;
		break;
	case '6':					/* right */
	case 'd':
		sx++;
		break;
	}
	int i;
	for (i = l; i != 0; i--)
	{
		body[i] = body[i - 1];
		*body[i] = 2;
	}
	body[0] = &mapArr[sx][sy];
	if ((*body[0] == 1) || (*body[0] == 2))
	{
		overFlag = 0;
	}
	*body[0] = 2;
}

void EatFood()
{
	if (*body[0] == 3)
	{
		l++;
		foodFlag = 0;
	}
}

void StartGame()
{
	sx = 1;
	sy = 1;
	input = '6';
	int j;
	for (j = 0; j < l; j++)
	{
		body[j] = &mapArr[sx - j][sy];
	}
	while (overFlag)
	{
		InitMap();
		SetSnakeNum();
		SetRandNum();
		EatFood();
		PrintMap();
		StartMsg();
		Sleep(SPEED);
		system("cls");
	}
}

void SetMoveNum()
{
	/* x move 1 -- (X - 2 ); y move 1 -- (Y - 2) */
	/* move x from left to right */
	if ((moveY == 1 + moveFlag) && (moveX < X - 2 - moveFlag))
	{
		mapArr[moveX][moveY] = 2;
		moveX++;
	}
	/* move y from top to buttom */
	else if ((moveX == X - 2 - moveFlag) && (moveY < Y - 2 - moveFlag))
	{
		mapArr[moveX][moveY] = 2;
		moveY++;
	}
	/* move x from right to left */
	else if ((moveY == Y - 2 - moveFlag) && (moveX > 1 + moveFlag))
	{
		mapArr[moveX][moveY] = 2;
		moveX--;
	}
	/* move y from buttom to top */
	else if ((moveX == 1 + moveFlag) && (moveY > 1 + moveFlag))
	{
		mapArr[moveX][moveY] = 2;
		moveY--;
		if (moveY == 2 + moveFlag)
		{
			moveFlag++;
		}
	}
}

void JudgeEnd()
{
	int i, j;
	int tmp = 1;
	for (j = 0; j < Y; j++)
	{
		for (i = 0; i < X; i++)
		{
			if (mapArr[i][j] == 0)
				goto out;
		}
	}
	moveX = 1, moveY = 1;
	InitMap();
	moveFlag = 0;
out:;
}

void StartView()
{
	moveX = 1, moveY = 1;
	int startFlag = 1;
	InitMap();
	while (startFlag)
	{
		SetMoveNum();
		PrintMap();
		printf("Press any key to start game: \n");
		Sleep(10);
		system("cls");
		JudgeEnd();
		if ((_kbhit()) && ((_getch() != '2') && (_getch() != 'w') && (_getch() != '8') && (_getch() != 's') && (_getch() != '4') && (_getch() != 'a') && (_getch() != '6') && (_getch() != 'd')))
			startFlag = 0;
	}
}

int main()
{
	while (1)
	{
		StartView();  /* an animation before game start */
		StartGame();
		printf("Game Over !!!\nPress any key to restart: \n");
		_getch();
		overFlag = 1;   /* restart the game by the flag */
		system("cls");
	}
}