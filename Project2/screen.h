#pragma once
#include <Windows.h>
#define SCREEN_HEIGHT 25
#define SCREEN_WIDTH 80

#define BOARD_HIGHT 22
#define BOARD_WIDTH 10


enum GAME_STATUS { RUN, PAUSE ,GAMEOVER};



class Screen {
private:
    HANDLE hScreenBuf;
    COORD coord;
    HANDLE hInput;
    BOOL isSuccess;
    GAME_STATUS status;


public:
    unsigned char screen[SCREEN_HEIGHT][SCREEN_WIDTH];
    unsigned char board[BOARD_HIGHT][BOARD_WIDTH];
    WORD color[SCREEN_HEIGHT][SCREEN_WIDTH];

    Block Next_Block;
    Block Cur_Block;


public:

    void InitRenderSystem();
    void Error(char* s);
    void Render();
    WORD GetKey();

    void Background();//백그라운드 바꾸기
    void DrawBoard(int LT_x, int LT_y, int RB_x, int RB_y);//게임 플레이 화면
    void NextBlock(int LT_x, int LT_y, int RB_x, int RB_y);//다음 블록
    void Drawscore(int LT_x, int LT_y, int RB_x, int RB_y, int score);//스코어 나오기
    void inittetris();
  
    void ProcessKey();

    void Update();
};