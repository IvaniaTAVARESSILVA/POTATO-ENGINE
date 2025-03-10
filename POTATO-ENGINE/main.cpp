#include <iostream>

#include "RendererManager.h"

int main()
{
    RendererManager::GetInstance().RenderWnd();
    std::cout << "Hello World!\n";
}

