#pragma once
#include "Renderer.h"
#include "Keyboard.h"
#include <memory>
#include <optional>

class Window
{
public:
	Window(int width, int height, const char* name) noexcept;
	~Window();
	//Window(const Window&) = delete;
	//Window& operator=(const Window&) = delete;
	static std::optional<int> ProcessMessages();
	Renderer& getRenderer();
	Keyboard keyboard;

private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lParam);
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lParam);
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;

	UINT		width;
	UINT		height;
	HWND		window_handle;
	std::unique_ptr<Renderer> renderer;

private:
	class WindowClass
	{
	public:
		static const char* GetName() noexcept;
		static HINSTANCE GetInstance() noexcept;
	private:
		WindowClass() noexcept;
		~WindowClass();
		WindowClass(const WindowClass&) = delete;
		static constexpr const char* wndClassName = "Direct3D Engine Window";
		static WindowClass wndClass;
		HINSTANCE hInst;
	};
};

