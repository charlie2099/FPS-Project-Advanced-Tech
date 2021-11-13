#include "Renderer.h"
#include <sstream>
#include <d3dcompiler.h>
#include <DirectXMath.h>

namespace wrl = Microsoft::WRL;
namespace dx = DirectX;

#pragma comment (lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

Renderer::Renderer(HWND hWnd)
{
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0; 
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 0;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = hWnd;
	sd.Windowed = true;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;

	D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&swap_chain,
		&device,
		nullptr,
		&device_context
	);

	// gain access to texture subresource in swap chain (back buffer)
	wrl::ComPtr<ID3D11Resource> pBackBuffer;
	swap_chain->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer);
	device->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &render_target_view);

	// create depth stensil state
	D3D11_DEPTH_STENCIL_DESC dsDesc = {};
	dsDesc.DepthEnable = TRUE;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
	wrl::ComPtr<ID3D11DepthStencilState> pDSState;
	device->CreateDepthStencilState(&dsDesc, &pDSState);

	// bind depth state
	device_context->OMSetDepthStencilState(pDSState.Get(), 1u);

	// create depth stencil texture
	wrl::ComPtr<ID3D11Texture2D> pDepthStencil;
	D3D11_TEXTURE2D_DESC descDepth = {};
	descDepth.Width = 1280u;
	descDepth.Height = 720u;
	descDepth.MipLevels = 1u;
	descDepth.ArraySize = 1u;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1u;
	descDepth.SampleDesc.Quality = 0u;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	device->CreateTexture2D(&descDepth, nullptr, &pDepthStencil);

	// create view of depth stencil texture
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
	descDSV.Format = DXGI_FORMAT_D32_FLOAT;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0u;
	device->CreateDepthStencilView(pDepthStencil.Get(), &descDSV, &depth_stencil_view);

	// bind depth stencil view to OM
	device_context->OMSetRenderTargets(1u, render_target_view.GetAddressOf(), depth_stencil_view.Get());


	// constant buffer for transformation matrix
	//struct ConstantBuffer
	//{
	//	dx::XMMATRIX transform;
	//};

	//const ConstantBuffer const_buffer =
	//{
	//	{
	//		dx::XMMatrixTranspose(
	//			dx::XMMatrixRotationZ(0) *
	//			dx::XMMatrixRotationX(0) *
	//			dx::XMMatrixTranslation(0, 0, 0 + 4.0f) *
	//			GetCamera() * GetProjection() *
	//			dx::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 60.0f) // 10
	//		)
	//	}
	//};
	//wrl::ComPtr<ID3D11Buffer> constant_buffer;
	//D3D11_BUFFER_DESC cbd;
	//cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//cbd.Usage = D3D11_USAGE_DYNAMIC;
	//cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	//cbd.MiscFlags = 0u;
	//cbd.ByteWidth = sizeof(const_buffer);
	//cbd.StructureByteStride = 0u;

	//D3D11_SUBRESOURCE_DATA csd = {};
	//csd.pSysMem = &const_buffer;
	//device->CreateBuffer(&cbd, &csd, &constant_buffer);

	//// bind constant buffer to vertex shader
	//device_context->VSSetConstantBuffers(0u, 1u, constant_buffer.GetAddressOf());

	// configure viewport
	D3D11_VIEWPORT vp;
	vp.Width = 1280;
	vp.Height = 720;
	vp.MinDepth = 0;
	vp.MaxDepth = 1;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	device_context->RSSetViewports(1u, &vp);
}

void Renderer::EndFrame()
{
	swap_chain->Present(1u, 0u);
}

void Renderer::ClearBuffer(float red, float green, float blue) noexcept
{
	const float color[] = { red, green, blue, 1.0f };
	device_context->ClearRenderTargetView(render_target_view.Get(), color);
	device_context->ClearDepthStencilView(depth_stencil_view.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
}

void Renderer::SetTransformMatrix(DirectX::XMMATRIX transform_matrix) noexcept
{
	transform_matrix_ = transform_matrix;
}

DirectX::XMMATRIX Renderer::GetTransformMatrix() const noexcept
{
	return transform_matrix_;
}

void Renderer::SetProjection(DirectX::FXMMATRIX proj) noexcept
{
	projection = proj;
}

DirectX::XMMATRIX Renderer::GetProjection() const noexcept
{
	return projection;
}

void Renderer::SetCamera(DirectX::FXMMATRIX cam) noexcept
{
	camera = cam;
}

DirectX::XMMATRIX Renderer::GetCamera() const noexcept
{
	return camera;
}

ID3D11Device* Renderer::GetDevice()
{
	return device.Get();
}

ID3D11DeviceContext* Renderer::GetContext()
{
	return device_context.Get();
}