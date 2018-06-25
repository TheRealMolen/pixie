#include <stdlib.h>
#include "pixie.h"

static const char* PixieWindowClass = "PixieWindowClass";

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_KEYUP:
		{
			if (wParam == VK_ESCAPE)
				DestroyWindow(hWnd);
			break;
		}

		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

bool Pixie::Open(const char* title, int width, int height)
{
	HINSTANCE hInstance = GetModuleHandle(0);

	WNDCLASS wc;
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = NULL;
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = PixieWindowClass;

	if (!RegisterClass(&wc))
		return 0;

	m_window = CreateWindow(PixieWindowClass, title, WS_OVERLAPPED, CW_USEDEFAULT, CW_USEDEFAULT, width, height, NULL, NULL, hInstance, NULL);
	if (m_window != 0)
	{
		SetWindowLongPtr(m_window, GWL_USERDATA, (LONG)this);
		ShowWindow(m_window, SW_SHOW);
	}

	return m_window != 0;
}

bool Pixie::Update()
{
	MSG msg;
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		if (msg.message == WM_QUIT)
			return false;
	}

	return true;
}

void Pixie::Close()
{
	//DestroyWindow(m_window);
}

extern int main(int argc, char** argv);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hInstPrev, LPSTR lpCmdLine, int nCmdShow)
{
	return main(__argc, __argv);
}
