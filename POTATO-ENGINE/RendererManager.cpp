#include "RendererManager.h"

RendererManager& RendererManager::GetInstance()
{
	static RendererManager instance;
	return instance;

}

bool RendererManager::CreateWnd(int width, int height, bool windowed)
{
	WNDCLASSEX wndClass{
		.cbSize = sizeof(WNDCLASSEX),
		.style = CS_HREDRAW | CS_VREDRAW,
		.lpfnWndProc = WndProc,
		.cbClsExtra = NULL,
		.cbWndExtra = NULL,
		.hInstance = hInstance,
		.hIcon = LoadIcon(NULL, IDI_WINLOGO),
		.hCursor = LoadCursor(NULL, IDC_ARROW),
		.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2),
		.lpszMenuName = NULL,
		.lpszClassName = WndClassName,
		.hIconSm = LoadIcon(NULL, IDI_WINLOGO),
	};

	if (!RegisterClassExW(&wndClass))
	{
		MessageBoxW(NULL, L"Error registering window class", L"Error", MB_OK | MB_ICONERROR);
		return false;
	}

	hwnd = CreateWindowEx(
		NULL,
		WndClassName,
		L"Potato Engine",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		width,
		height,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hwnd)
	{
		MessageBox(NULL, L"Error creating window", L"Error", MB_OK | MB_ICONERROR);
	}
	ShowWindow(hwnd, SW_SHOW);

	UpdateWindow(hwnd);

	return hwnd != NULL;
}

int RendererManager::MessageLoop()
{
	MSG msg;

	ZeroMemory(&msg, sizeof(MSG));

	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

int __stdcall RendererManager::RenderWnd()
{
	if (!CreateWnd(WINDOW_WIDTH, WINDOW_HEIGHT, true))
	{
		MessageBox(0, L"Window Initialization - Failed",
			L"Error", MB_OK);
		return -1;
	}

	return MessageLoop();
}

