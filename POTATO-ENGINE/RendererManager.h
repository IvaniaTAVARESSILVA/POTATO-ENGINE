#pragma once


#pragma region DX11 Includes
#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#pragma endregion

#pragma region EngineCore Includes
#include"Libraries\imgui\imgui.h"
#include"Libraries\imgui\backends\imgui_impl_win32.h"
#pragma endregion


#include<Windows.h>
#include <iostream>

#define WINDOW_WIDTH 1020
#define WINDOW_HEIGHT 720

//extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) {
			if (MessageBox(0, L"Are you sure  you want to exit ", L"Really", MB_YESNO | MB_ICONQUESTION) == IDYES) 
			{

				DestroyWindow(hwnd);

			}
		}
		return 0;
	case WM_KEYUP:
	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_MOUSEWHEEL:
		//ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	//Pass messages to default handler for any other messages
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

class RendererManager
{
public:

	static RendererManager& GetInstance();

	RendererManager operator= (const RendererManager&) = delete;

	bool CreateWnd(int width, int height, bool windowed);

	int MessageLoop();

	int WINAPI RenderWnd();

	~RendererManager() {};

private:

	HINSTANCE hInstance = nullptr;

	LPCTSTR WndClassName = L"Potato Engine";

	HWND hwnd = NULL;

	RendererManager() {};
};

//static RendererManager& renderManager = RendererManager::GetInstance();