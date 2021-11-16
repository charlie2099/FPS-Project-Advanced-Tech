#pragma once
#include "ConstantBuffer.h"
#include "Constants.h"
#include <d3d11.h>
#include <vector>
#include <memory>
#include <wrl.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

class Renderer
{
	friend class Bindable;
public:
	Renderer(HWND handle);
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;
	~Renderer() = default;

	void EndFrame();
	void ClearBuffer(float red, float green, float blue) noexcept;
	void ClearBuffer(DirectX::XMFLOAT3 colour) noexcept;

	void SetModelMatrix(DirectX::XMMATRIX model);
	//void SetViewMatrix(DirectX::XMMATRIX view);

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetContext();

	std::unique_ptr<ConstantBuffer> constant_buffer;
	ConstantBuffer::ConstantBufferData constantBufferData;

private:
	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> device_context;
	Microsoft::WRL::ComPtr<IDXGISwapChain> swap_chain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> render_target_view;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depth_stencil_view;
};


