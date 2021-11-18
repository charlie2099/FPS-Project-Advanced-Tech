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
public:
	Renderer(HWND handle);
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;
	~Renderer() = default;

	void ClearBuffer(float red, float green, float blue) noexcept;
	void ClearBuffer(DirectX::XMFLOAT3 colour) noexcept;
	void EndFrame();
	
	void SetModelMatrix(DirectX::XMMATRIX model);

	void SetViewMatrix(DirectX::XMMATRIX view);
	DirectX::XMMATRIX GetViewMatrix() { return view_matrix_; };

	void SetViewPos(DirectX::XMFLOAT3 pos); // CAMERA CLASS
	DirectX::XMFLOAT3 GetViewPos() { return view_pos_; };
	//void UpdateViewPos();

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();
	ConstantBuffer::Data& GetCBufferData();

private:
	DirectX::XMMATRIX view_matrix_ = DirectX::XMMatrixIdentity();
	DirectX::XMFLOAT3 view_pos_;

	std::unique_ptr<ConstantBuffer> constant_buffer;
	ConstantBuffer::Data cbuffer_data;

	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> device_context;
	Microsoft::WRL::ComPtr<IDXGISwapChain> swap_chain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> render_target_view;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depth_stencil_view;
};


