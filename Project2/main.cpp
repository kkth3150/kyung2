#include "pch.h"


Screen g_screen;

int main() {
   
    g_screen.InitRenderSystem();
    g_screen.inittetris();
    while (1) {
        g_screen.ProcessKey();
        g_screen.Update();
        g_screen.Render();
        Sleep(100);
    }

}