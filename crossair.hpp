#pragma once

#include <GLFW/glfw3.h>
#include <Windows.h>
#include <map>
#include "colore.hpp"

class Crossair
{
public:

    Crossair();
    void Start();

    float crossSize;
    float thickness;
    bool active;
    bool menuAttivo; 
    bool f2Premuto;
    int numeroMenu; 
    int windowWidth; 
    int windowHeight;
    int screenWidth;
    int screenHeight;

    Colore coloreCorrente;
    std::map<int, Colore> mappaColore;

    GLFWwindow* window;
    const GLFWvidmode* mode;

    void drawCross(float thickness, float crossSize, int windowWidth, int windowHeight, Colore& coloreCorrente);
    void menu(float& crossSize, float& thickness, bool& active, int& numeroMenu, Colore& coloreCorrente, std::map<int, Colore>& mappaColore, GLFWwindow* window);
};