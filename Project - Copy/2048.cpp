#include "iGraphics.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <mmsystem.h>

#define SIZE 4
int board[SIZE][SIZE];
int score = 0;
int gameOver = 0;
int wpage = 1;
bool musicON = true;
int hscr = 0;
bool scoresave = false;
bool game = false;
int optimalcount = 3;

void drawBoard();
void generateTile();
int checkGameOver();
void moveLeft();
void moveRight();
void moveUp();
void moveDown();
void drawHomePage();
void restart();
void welcomepage();
void highscore();
void gameoverpage();
void optimalmove();
void success();

/*
function iDraw() is called again and again by the system.
*/

void drawHomePage()
{
	game = true;
	iSetColor(128, 128, 128);
	iFilledRectangle(0, 0, 720, 720);
	iShowBMP2(0, 0, "hpage.png", 255);
}

void welcomepage()
{

	iSetColor(128, 128, 128);
	iFilledRectangle(0, 0, 720, 720);
	iShowBMP2(0, 0, "welcome.bmp", 255);
	// iFilledRectangle(90, 150, 580, 122);
}

void savescr()
{
	FILE *fptr = fopen("highscore.txt", "a");
	if (fptr != NULL)
	{
		fprintf(fptr, "%d\n", score);
	}
	fclose(fptr);
}

void drawBoard()
{
	// boardbackground
	// iShowBMP2(90, 90,"Untitled design.png", 0);

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			// different tiles
			if (board[i][j] == 0)
			{
				iShowBMP2(j * 120 + 120, i * 120 + 120, "Tile Background.png", 0);
			}

			else if (board[i][j] == 2)
			{
				iShowBMP2(j * 120 + 120, i * 120 + 120, "2 Tile.png", 0);
			}

			else if (board[i][j] == 4)
			{
				iShowBMP2(j * 120 + 120, i * 120 + 120, "4 Tile.png", 0);
			}

			else if (board[i][j] == 8)
			{
				iShowBMP2(j * 120 + 120, i * 120 + 120, "8 Tile.png", 0);
			}

			else if (board[i][j] == 16)
			{
				iShowBMP2(j * 120 + 120, i * 120 + 120, "16 Tile.png", 0);
			}

			else if (board[i][j] == 32)
			{
				iShowBMP2(j * 120 + 120, i * 120 + 120, "32 Tile.png", 0);
			}

			else if (board[i][j] == 64)
			{
				iShowBMP2(j * 120 + 120, i * 120 + 120, "64 Tile.png", 0);
			}

			else if (board[i][j] == 128)
			{
				iShowBMP2(j * 120 + 120, i * 120 + 120, "128 Tile.png", 0);
			}

			else if (board[i][j] == 256)
			{
				iShowBMP2(j * 120 + 120, i * 120 + 120, "256 Tile.png", 0);
			}

			else if (board[i][j] == 512)
			{
				iShowBMP2(j * 120 + 120, i * 120 + 120, "512 Tile.png", 0);
			}

			else if (board[i][j] == 1024)
			{
				iShowBMP2(j * 120 + 120, i * 120 + 120, "1024 Tile.png", 0);
			}

			else if (board[i][j] == 2048)
			{
				iShowBMP2(j * 120 + 120, i * 120 + 120, "2048 Tile.png", 0);
				gameOver = 2;
				success();
			}

			else
			{
				iSetColor(60, 58, 50);
				iFilledRectangle(j * 120 + 110, i * 120 + 110, 100, 100);
			}
		}
	}

	// score display
	iSetColor(255, 255, 255);
	char scoreStr[20];
	sprintf(scoreStr, "Score: %d", score);
	iText(600, 650, scoreStr, GLUT_BITMAP_HELVETICA_18);

	// optimal move reamaining display
	iSetColor(255, 255, 255);
	char omstr[20];
	sprintf(omstr, "Remaining help: %d", optimalcount);
	iText(570, 620, omstr, GLUT_BITMAP_HELVETICA_18);
}

void success()
{
	// if user makes a 2048 tiles xD
	if (scoresave == false)
	{
		savescr();
		scoresave = true;
	}
	iSetColor(128, 128, 128);
	iFilledRectangle(0, 0, 720, 720);
	iShowBMP2(0, 0, "congrats.png", 0);
}

void gameoverpage()
{
	if (scoresave == false)
	{
		savescr();
		scoresave = true;
	}
	gameOver = 1;
	iSetColor(128, 128, 128);
	iFilledRectangle(0, 0, 720, 720);
	iShowBMP2(0, 0, "Gameover.png", 0);
}

void generateTile()
{
	int empTiles[SIZE * SIZE][2];
	int count = 0;

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (board[i][j] == 0)
			{
				// 0 tiles er index er i, j 2d array
				empTiles[count][0] = i;
				empTiles[count][1] = j;
				count++;
			}
		}
	}
	if (count > 0)
	{
		int randind = rand() % count;
		int x = empTiles[randind][0];
		int y = empTiles[randind][1];
		board[x][y] = (rand() % 2 + 1) * 2; // 2 or 4
	}
}

int checkGameOver()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (board[i][j] == 0)
			{
				return 0;
			}
			if (i < SIZE - 1 && board[i][j] == board[i + 1][j])
			{
				return 0;
			}
			if (j < SIZE - 1 && board[i][j] == board[i][j + 1])
			{
				return 0;
			}
		}
	}

	return 1;
}

void iDraw()
{
	// place your drawing codes here
	iClear();
	if (wpage == 1)
	{
		welcomepage();
	}
	else
	{
		drawHomePage();
		drawBoard();
	}

	if (gameOver == 1)
	{
		gameoverpage();
	}

	else if (gameOver == 2)
	{
		success();
	}

	if (hscr == 1)
	{
		highscore();
	}
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/

void iMouseMove(int mx, int my)
{
	// place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/

void iMouse(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (wpage == 1)
		{
			if (mx >= 253 && mx <= 253 + 365 && my >= 440 && my <= 440 + 90)
			{
				wpage = 0;
				restart();
				generateTile();
			}
			else if (mx >= 253 && mx <= 253 + 365 && my >= 200 && my <= 200 + 90)
			{
				exit(0);
			}
			else if (mx >= 253 && mx <= 253 + 365 && my >= 320 && my <= 320 + 90)
			{
				wpage = 0;
				hscr = 1;
				highscore();
			}
		}

		if (hscr == 1)
		{

			if (mx >= 478 && mx <= 648 && my >= 73 && my <= 73 + 57)
			{
				wpage = 1;
				hscr = 0;
				welcomepage();
			}
		}

		if (gameOver == 1)
		{
			if (mx >= 210 && mx <= 210 + 127 && my >= 382 && my <= 382 + 127)
			{
				gameOver = 0;
				restart();
				generateTile();
			}
			else if (mx >= 381 && mx <= 381 + 127 && my >= 382 && my <= 382 + 127)
			{
				gameOver = 0;
				wpage = 1;
				welcomepage();
			}
			else if (mx >= 299 && mx <= 299 + 127 && my >= 218 && my <= 218 + 127)
			{
				exit(0);
			}
		}

		if (gameOver == 2)
		{
			if (mx >= 73 && mx <= 268 && my >= 153 && my <= 200)
			{
				restart();
				generateTile();
				gameOver = 0;
			}
			else if (mx >= 451 && mx <= 645 && my >= 153 && my <= 200)
			{
				gameOver = 0;
				wpage = 1;
				welcomepage();
			}
			else if (mx >= 261 && mx <= 456 && my >= 73 && my <= 118)
			{
				exit(0);
			}
		}

		if (game == true && optimalcount > 0)
		{
			if (mx >= 525 && mx <= 670 && my >= 62 && my <= 113)
			{
				optimalmove();
				optimalcount--;
			}
		}
	}
}

void optimalmove()
{
	int omove = -1;
	int bestscr = score;

	int tempboard[SIZE][SIZE];
	int tempscre = score;

	// copy to temp board for comparison
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			tempboard[i][j] = board[i][j];
		}
	}

	// for comaparison--> try every possible move
	for (int move = 0; move < 4; move++)
	{
		if (move == 0)
			moveLeft();
		if (move == 1)
			moveRight();
		if (move == 2)
			moveUp();
		if (move == 3)
			moveDown();

		// best move selection
		if (score > bestscr)
		{
			bestscr = score;
			omove = move;
		}

		// Restore the board
		score = tempscre;
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				board[i][j] = tempboard[i][j];
			}
		}
	}

	if (omove == 0)
		moveLeft();
	if (omove == 1)
		moveRight();
	if (omove == 2)
		moveUp();
	if (omove == 3)
		moveDown();

	generateTile();
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/

void iKeyboard(unsigned char key)
{
	if (key == 'q' || key == 'Q')
	{
		exit(0);
	}
	// place your codes for other keys here
	if (key == 'r' || key == 'R')
	{
		restart();
		generateTile();
	}
	if (key == 'a' || key == 'A')
	{
		moveLeft();
		generateTile();
		gameOver = checkGameOver();
	}
	if (key == 'd' || key == 'D')
	{
		moveRight();
		generateTile();
		gameOver = checkGameOver();
	}
	if (key == 'w' || key == 'W')
	{
		moveUp();
		generateTile();
		gameOver = checkGameOver();
	}
	if (key == 's' || key == 'S')
	{
		moveDown();
		generateTile();
		gameOver = checkGameOver();
	}
	if (key == 'b' || key == 'B')
	{
		welcomepage();
	}
	if (gameOver == 1)
		game = false;
}

void moveRight()
{
	// CODDE FOR rightmove
	for (int i = 0; i < SIZE; i++)
	{
		// temporary array to store the row after merging
		int temp[SIZE] = {0};
		int pos = SIZE - 1;

		// non-0 tiles--> right
		for (int j = SIZE - 1; j >= 0; j--)
		{
			if (board[i][j] != 0)
			{
				temp[pos] = board[i][j];
				pos--;
			}
		}

		// combine
		for (int j = SIZE - 1; j > 0; j--)
		{
			if (temp[j] == temp[j - 1] && temp[j] != 0)
			{
				temp[j] *= 2;
				score += temp[j];
				temp[j - 1] = 0; // Clear tile
			}
		}

		// shift again to fill any gaps created by merging
		pos = SIZE - 1;
		for (int j = pos; j >= 0; j--)
		{
			if (temp[j] != 0)
			{
				board[i][pos] = temp[j];
				pos--;
			}
		}

		// others 0
		for (int j = pos; j >= 0; j--)
		{
			board[i][j] = 0;
		}
	}
}

void moveLeft()
{
	// CODDE FOR leftmove
	for (int i = 0; i < SIZE; i++)
	{
		int temp[SIZE] = {0};
		int position = 0;

		// non-0-->left
		for (int j = 0; j < SIZE; j++)
		{
			if (board[i][j] != 0)
			{
				temp[position] = board[i][j];
				position++;
			}
		}

		// combine
		for (int j = 0; j < SIZE - 1; j++)
		{
			if (temp[j] == temp[j + 1] && temp[j] != 0)
			{
				temp[j] *= 2;
				score += temp[j];
				temp[j + 1] = 0; // Clear the merged tile
			}
		}

		// fill gap
		position = 0;
		for (int j = 0; j < SIZE; j++)
		{
			if (temp[j] != 0)
			{
				board[i][position] = temp[j];
				position++;
			}
		}

		// others 0
		for (int j = position; j < SIZE; j++)
		{
			board[i][j] = 0;
		}
	}
}

void moveDown()
{
	// CODDE FOR downmove
	for (int j = 0; j < SIZE; j++)
	{
		int temp[SIZE] = {0}; // temp array to store the coloumn after merging
		int position = 0;

		// non-0-->up
		for (int i = 0; i < SIZE; i++)
		{
			if (board[i][j] != 0)
			{
				temp[position] = board[i][j];
				position++;
			}
		}

		// combine
		for (int i = 0; i < SIZE - 1; i++)
		{
			if (temp[i] == temp[i + 1] && temp[i] != 0)
			{
				temp[i] *= 2;
				score += temp[i];
				temp[i + 1] = 0; // clear merged one
			}
		}

		// gap fill for merging
		position = 0;
		for (int i = 0; i < SIZE; i++)
		{
			if (temp[i] != 0)
			{
				board[position][j] = temp[i];
				position++;
			}
		}

		// others 0
		for (int i = position; i < SIZE; i++)
		{
			board[i][j] = 0;
		}
	}
}

void moveUp()
{
	// CODDE FOR upmove
	for (int j = 0; j < SIZE; j++)
	{
		int temp[SIZE] = {0};
		int position = SIZE - 1;

		for (int i = SIZE - 1; i >= 0; i--)
		{
			if (board[i][j] != 0)
			{
				temp[position] = board[i][j];
				position--;
			}
		}

		for (int i = SIZE - 1; i > 0; i--)
		{
			if (temp[i] == temp[i - 1] && temp[i] != 0)
			{
				temp[i] *= 2;
				score += temp[i];
				temp[i - 1] = 0;
			}
		}

		// merge
		position = SIZE - 1;
		for (int i = SIZE - 1; i >= 0; i--)
		{
			if (temp[i] != 0)
			{
				board[position][j] = temp[i];
				position--;
			}
		}

		// others 0
		for (int i = position; i >= 0; i--)
		{
			board[i][j] = 0;
		}
	}
}

void highscore()
{
	iShowBMP2(0, 0, "leaderboard.png", 0);
	FILE *fptr = fopen("highscore.txt", "r");
	if (fptr == NULL)
	{
		return;
	}

	int score[1000];
	int count = 0;

	for (count = 0; count < 1000; count++)
	{
		if (fscanf(fptr, "%d", &score[count]) == EOF)
		{
			break;
		}
	}

	// selection sort
	for (int i = 0; i < count - 1; i++)
	{
		int maxind = i;
		for (int j = i + 1; j < count; j++)
		{
			if (score[j] > score[maxind])
			{
				maxind = j;
			}
		}

		int temp = score[maxind];
		score[maxind] = score[i];
		score[i] = temp;
	}

	// top 5 display
	for (int i = 0; i < count && i < 5; i++)
	{
		char scrstr[20];
		sprintf(scrstr, "%d. %d", i + 1, score[i]);
		iText(250, 450 - i * 50, scrstr, GLUT_BITMAP_TIMES_ROMAN_24);
	}
	fclose(fptr);
}

void restart()
{
	// gamebrd reset
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			board[i][j] = 0;
		}
	}

	score = 0;
	gameOver = 0;
	scoresave = false;
	generateTile();
	optimalcount = 3;
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/

void iSpecialKeyboard(unsigned char key)
{
	if (key == GLUT_KEY_LEFT)
	{
		moveLeft();
		generateTile();
		gameOver = checkGameOver();
	}
	else if (key == GLUT_KEY_RIGHT)
	{
		moveRight();
		generateTile();
		gameOver = checkGameOver();
	}
	else if (key == GLUT_KEY_UP)
	{
		moveUp();
		generateTile();
		gameOver = checkGameOver();
	}
	else if (key == GLUT_KEY_DOWN)
	{
		moveDown();
		generateTile();
		gameOver = checkGameOver();
	}
	else if (key == GLUT_KEY_F1)
	{
		if (musicON)
		{
			musicON = false;
			PlaySound(NULL, 0, 0);
		}
		else
		{
			musicON = true;
			PlaySound("background.wav", NULL, SND_LOOP | SND_ASYNC);
		}
	}
}

int main()
{
	srand(time(NULL));
	if (musicON)
	{
		PlaySound("background.wav", NULL, SND_LOOP | SND_ASYNC);
	}
	generateTile();
	generateTile();
	// place your own initialization codes here.
	iInitialize(720, 720, "2048 Game");
	return 0;
}

// tasks to do--->
//  A* algorithm(idk how to do)
// optimal move(done)
//  leaderboard file i/o(DONE)
//  image for tiles (Done)