#include "pch.h"
#include "screen.h"

using namespace std;
int gamescore = 0;

void Screen::Render() 
{
	Background();
	DrawBoard(1,1,1+BOARD_WIDTH,1+BOARD_HIGHT);
	NextBlock(15,4,26,10);
	Drawscore(15,13,26,19,10000);


	DWORD written;

	isSuccess = WriteConsoleOutputCharacter(
		hScreenBuf,
		(LPCSTR)screen,
		SCREEN_WIDTH * SCREEN_HEIGHT,
		coord,
		&written);
	if (!isSuccess)
		Error((char*)"WriteConsoleOutputCharacter");

	isSuccess = WriteConsoleOutputAttribute(
		hScreenBuf,
		(const WORD*)color,
		SCREEN_WIDTH * SCREEN_HEIGHT,
		coord,
		&written);
	if (!isSuccess)
		Error((char*)"WriteConsoleOutputAttribute");
}

void Screen::InitRenderSystem()
{
	system("chcp 437");
	system("cls");

	hScreenBuf = CreateConsoleScreenBuffer(
		GENERIC_READ |
		GENERIC_WRITE,
		0,
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL);

	if (!SetConsoleActiveScreenBuffer(hScreenBuf))
		Error((char*)"SetConsoleActiveScreenBuffer");

	coord.X = 0;
	coord.Y = 0;

	hInput = CreateFile("CONIN$", GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, 0);
	if (hInput == INVALID_HANDLE_VALUE) {
		//fprintf(stderr, "입력버퍼핸들얻기 실패\n");
	}
}

void Screen::Error(char* s)
{
	exit(0);
};

void Screen::Background()
{
	for (int y = 0; y < SCREEN_HEIGHT; ++y) {
		for (int x = 0; x < SCREEN_WIDTH; ++x) {
			screen[y][x] = 219;
			color[y][x] = FOREGROUND_INTENSITY;


		}
	}

}

void Screen::Update() {
	
	static int check = 0;
	if (status == PAUSE||status == GAMEOVER) {
		return;
	}
	for (int i = 0; i < 4; ++i) {
		if (Cur_Block.position.y + Cur_Block.bcoord[i].y >= BOARD_HIGHT - 1
			|| board[Cur_Block.position.y + Cur_Block.bcoord[i].y + 1][Cur_Block.position.x + Cur_Block.bcoord[i].x] == 219) {
			for (int j = 0; j < 4; ++j) {
				board[Cur_Block.position.y + Cur_Block.bcoord[j].y][Cur_Block.position.x + Cur_Block.bcoord[j].x] = 219;
			}
			Cur_Block.ChangeType(Next_Block.type);
			Cur_Block.position = { BOARD_WIDTH / 2-1,0 };

			Cur_Block.changeAngle(Next_Block.angle);


			std::random_device rd;
			std::default_random_engine dre(rd());
			std::uniform_int_distribution<> uid(0, end_count - 1);
			Next_Block.ChangeType((TYPE)uid(dre));

			break;

		}
	}

	check++;
	
	if (check % 4 == 0) {
		++Cur_Block.position.y;
		check = 0;
	}

	int to_delete[4] = { -1,-1,-1,-1 };
	int didx = 0;

	for (int y = 0; y < BOARD_HIGHT; ++y) {
		for (int x = 0; x < BOARD_WIDTH; ++x) {
			if (board[y][x] != 219)
				break;

			if (x == BOARD_WIDTH - 1) {
				to_delete[didx++] = y;
				gamescore++;
			}
		}

	}

	for (int i = 0; i < didx; ++i) {
		for (int j = 0; j < BOARD_WIDTH; ++j) {
			board[to_delete[i]][j] = ' ';
		}

	}

	for (int i = 0; i < didx; ++i) {
		for (int y = to_delete[i] - 1; y >-1 ; --y) {
			for (int x = 0; x < BOARD_WIDTH; ++x) {
				board[y + 1][x] = board[y][x];

			}
		}
	}

	for (int x = 0; x < BOARD_WIDTH; ++x) {
		if (board[0][x] == 219)
			status = GAMEOVER;

	}
}




void Screen::inittetris() {
	
	Cur_Block.position = { BOARD_WIDTH / 2-1,0 };

	status = RUN;
}


void Screen::DrawBoard(int LT_x, int LT_y , int RB_x , int RB_y)
{
	for (int y = LT_y; y < RB_y; ++y) {
		for (int x = LT_x; x < RB_x; ++x) {
			screen[y][x] = ' ';

		}
	}

	for (int i = 0; i < BOARD_HIGHT; ++i) {
		for (int j = 0; j < BOARD_WIDTH; ++j) {
			screen[i + LT_y][j + LT_x] = board[i][j];
			color[i+1][j+1]= FOREGROUND_GREEN;
		}
	}

	for (int i = 0; i < 4; i++) {
		screen[Cur_Block.bcoord[i].y + Cur_Block.position.y+LT_y][Cur_Block.bcoord[i].x + Cur_Block.position.x+ LT_x] = 219;
		color[Cur_Block.bcoord[i].y + Cur_Block.position.y + LT_y][Cur_Block.bcoord[i].x + Cur_Block.position.x + LT_x] = FOREGROUND_INTENSITY | FOREGROUND_GREEN;
	}
}

void Screen::NextBlock(int LT_x, int LT_y, int RB_x, int RB_y)
{
	for (int y = LT_y; y < RB_y; ++y) {
		for (int x = LT_x; x < RB_x; ++x) {
			screen[y][x] = ' ';
		}
	}

	memcpy(&screen[LT_y][LT_x+((RB_x-LT_x)/2)-2], "NE XT", 5);

	Next_Block.position = {LT_x + ((RB_x - LT_x) / 2)-1,LT_y + 2 };

	for (int i = 0; i < 4; i++) {
		screen[Next_Block.bcoord[i].y + Next_Block.position.y][Next_Block.bcoord[i].x + Next_Block.position.x] = 219;
		color[Next_Block.bcoord[i].y + Next_Block.position.y][Next_Block.bcoord[i].x + Next_Block.position.x] = FOREGROUND_INTENSITY | FOREGROUND_GREEN;
	}

}

void Screen::Drawscore(int LT_x, int LT_y, int RB_x, int RB_y, int score)
{
	for (int y = LT_y; y < RB_y; ++y) {
		for (int x = LT_x; x < RB_x; ++x) {
			screen[y][x] = ' ';
		}
	}

	memcpy(&screen[LT_y][LT_x + ((RB_x - LT_x)/2) - 2], "SCORE", 5);

	char game_score[2];
	_itoa_s(gamescore, game_score, 10);

	memcpy(&screen[LT_y+2][LT_x + ((RB_x - LT_x) / 2)], game_score,2);

}

void Screen::ProcessKey() {

	switch (GetKey()) {
	
	case 'p':
	case 'P':

		if(status == RUN){
			status = PAUSE;
		}
		else if(status = PAUSE){
			status = RUN;
		}

		break;
		
	case VK_LEFT: {
		if (status == PAUSE || status == GAMEOVER)
			return;
		for (int i = 0; i < 4; ++i) {
			if (Cur_Block.position.x + Cur_Block.bcoord[i].x <= 0 
				|| board[Cur_Block.position.y + Cur_Block.bcoord[i].y][Cur_Block.position.x + Cur_Block.bcoord[i].x-1] == 219) 
			{
				return;
			}
		}

			--Cur_Block.position.x;
	}
				break;
	case VK_RIGHT: {
		if (status == PAUSE || status == GAMEOVER)
			return;

		for (int i = 0; i < 4; ++i) {
			if (Cur_Block.position.x + Cur_Block.bcoord[i].x >= BOARD_WIDTH - 1
				|| board[Cur_Block.position.y + Cur_Block.bcoord[i].y][Cur_Block.position.x + Cur_Block.bcoord[i].x + 1] == 219)
			{
				return;
			}
		}
			++Cur_Block.position.x;

	}
				 break;
	case VK_DOWN: {
		if (status == PAUSE || status == GAMEOVER)
			return;

		for (int i = 0; i < 4; ++i) {

			if (Cur_Block.position.y + Cur_Block.bcoord[i].y >= BOARD_HIGHT - 1
				|| board[Cur_Block.position.y + Cur_Block.bcoord[i].y + 1][Cur_Block.position.x + Cur_Block.bcoord[i].x] == 219)

				return;
		}
			++Cur_Block.position.y;
		
	}
				break;

	case VK_SPACE: {
		if (status == PAUSE || status == GAMEOVER)
			return;
	}            
				 int a = Cur_Block.angle;
				 a++;

				 if (a == 4) {
					 a = 0;
				 }
				 
				 Cur_Block.changeAngle((ANGLE)a);

				 for (int i = 0; i < 4; ++i) {
					 if (Cur_Block.position.x + Cur_Block.bcoord[i].x >= BOARD_WIDTH
				         ||Cur_Block.position.x + Cur_Block.bcoord[i].x <0
						 || board[Cur_Block.position.y + Cur_Block.bcoord[i].y][Cur_Block.position.x + Cur_Block.bcoord[i].x] == 219
						 ||Cur_Block.position.y + Cur_Block.bcoord[i].y >= BOARD_HIGHT
						 )
					 {
						 a--;
						 if (a == -1) {
							 a = 3;
						 }
						 Cur_Block.changeAngle((ANGLE)a);
						 return;
					 }
				 }
				 
				 
				 break;
	}
}

WORD Screen::GetKey(void)
{
	INPUT_RECORD ir;
	DWORD sz;

	if (PeekConsoleInput(hInput, &ir, 1, &sz)) {
		if (1 <= sz)
			FlushConsoleInputBuffer(hInput);
		if (ir.EventType == KEY_EVENT) {
			if (ir.Event.KeyEvent.bKeyDown) {
				return ir.Event.KeyEvent.wVirtualKeyCode;
			}
		}
	}
	return 0;
}