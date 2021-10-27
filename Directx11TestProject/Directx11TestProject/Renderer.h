#pragma once
#include "WindowsHeader.h"
#include <d3d11.h>
#include <wrl.h>

class Renderer
{
public:
	Renderer(HWND hWnd);
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;
	~Renderer() = default;
	void EndFrame();
	void ClearBuffer(float red, float green, float blue) noexcept;
	void DrawCube(float angle, float x, float y);
private:
	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<IDXGISwapChain> swap_chain;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> device_context;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> render_target_view;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depth_stencil_view;
};