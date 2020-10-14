#pragma once

#include <stdint.h>
#include <wtypes.h>
#include <functional>

class Context;

class Window
{
public:
	Window(uint32_t width, uint32_t height);
	Window(const Window&) = delete;
	Window(Window&&) = delete;
	Window& operator=(const Window&) = delete;
	Window& operator=(Window&&) = delete;

	void Show() const;
	void Run(const Context& context) const;
	const HWND& GetHandler() const { return wndHandler; }
	inline const int Width() const { return width; }
	inline const int Height() const { return height; }
	inline const float GetAspectRatio() const { return ((float)width) / ((float)height); }

	std::function<void()> OnUpdate;

private:
	WNDCLASS wndClass;
	RECT wndRect;
	HWND wndHandler;
	const uint32_t width;
	const uint32_t height;
};

