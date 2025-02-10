#include "crossair.hpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    Crossair crossair = Crossair();
    crossair.Start();
}