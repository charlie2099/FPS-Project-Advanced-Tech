#pragma once
#include "WindowsHeader.h"
//#include "VertexBuffer.h"
//#include "IndexBuffer.h"
#include <d3d11.h>
#include <wrl.h>
#include <vector>
#include <memory>
#include <directxmath.h>

class Renderer
{
	friend class Bindable;
public:
	Renderer(HWND hWnd);
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;
	~Renderer() = default;

	void EndFrame();
	void ClearBuffer(float red, float green, float blue) noexcept;
	void DrawIndexed(UINT count) noexcept;
	//void DrawCube(float angle, float x, float y, float z);


	void SetProjection(DirectX::FXMMATRIX proj) noexcept;
	DirectX::XMMATRIX GetProjection() const noexcept;

	//void SetCamera(DirectX::FXMMATRIX cam) noexcept;
	//DirectX::XMMATRIX GetCamera() const noexcept;

private:
	DirectX::XMMATRIX projection;
	//DirectX::XMMATRIX camera;

	/// BUFFERS
	//VertexBuffer vertex_buffer;
	//IndexBuffer index_buffer;

	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> device_context;
	Microsoft::WRL::ComPtr<IDXGISwapChain> swap_chain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> render_target_view;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depth_stencil_view;
};