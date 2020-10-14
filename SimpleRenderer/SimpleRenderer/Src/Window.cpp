#include "Window.h"
#include "Context.h"

Window::Window(uint32_t width_, uint32_t height_) : width{width_}, height{ height_}
{
    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = DefWindowProc;
	wndClass.hInstance = GetModuleHandle(nullptr);
	wndClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wndClass.hbrBackground = GetSysColorBrush(COLOR_WINDOW);   
	wndClass.lpszClassName = TEXT("D3D11");  
	RegisterClass(&wndClass);

	wndRect = RECT{ 0, 0, (LONG) width, (LONG) height };
	AdjustWindowRect(&wndRect, WS_OVERLAPPEDWINDOW, false);  
	wndHandler = CreateWindow(wndClass.lpszClassName, TEXT("D3D11 Renderer"),
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		wndRect.right - wndRect.left, wndRect.bottom - wndRect.top,
		nullptr, nullptr, wndClass.hInstance, nullptr);
}

void Window::Show() const
{
	ShowWindow(wndHandler, SW_NORMAL);
}

void Window::Run(const Context& context) const
{
	context.GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	while (true)
	{
		MSG msg;
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		RECT client_rect;
		GetClientRect(wndHandler, &client_rect);
		D3D11_VIEWPORT vp = { 0, 0, client_rect.right - client_rect.left, client_rect.bottom - client_rect.top, 0, 1 };
		context.GetDeviceContext()->RSSetViewports(1, &vp);

		if (OnUpdate)
			OnUpdate();
	}
}
