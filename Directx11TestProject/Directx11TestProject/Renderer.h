#pragma once
#include "WindowsHeader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include <d3d11.h>
#include <wrl.h>
#include <vector>
#include <memory>
#include <directxmath.h>

class Renderer
{
public:
	Renderer(HWND hWnd);
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;
	~Renderer() = default;

	void EndFrame();
	void ClearBuffer(float red, float green, float blue) noexcept;

	void SetTransformMatrix(DirectX::XMMATRIX transform_matrix) noexcept;
	DirectX::XMMATRIX GetTransformMatrix() const noexcept;

	// Camera
	void SetProjection(DirectX::FXMMATRIX proj) noexcept;
	DirectX::XMMATRIX GetProjection() const noexcept;
	void SetCamera(DirectX::FXMMATRIX cam) noexcept;
	DirectX::XMMATRIX GetCamera() const noexcept;

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetContext();
	//Microsoft::WRL::ComPtr<ID3D11Device>& GetDevice();
	//Microsoft::WRL::ComPtr<ID3D11DeviceContext>& GetDeviceContext();

private:
	DirectX::XMMATRIX transform_matrix_{};
	DirectX::XMMATRIX projection{};
	DirectX::XMMATRIX camera{};

	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> device_context;
	Microsoft::WRL::ComPtr<IDXGISwapChain> swap_chain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> render_target_view;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depth_stencil_view;
};