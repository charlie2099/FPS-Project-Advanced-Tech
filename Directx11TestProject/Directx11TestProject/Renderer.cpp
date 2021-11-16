#include "Renderer.h"
#include <d3dcompiler.h>
#include <sstream>
#include <cmath>
#include <DirectXMath.h>
#include "Cube.h"

namespace wrl = Microsoft::WRL;
namespace dx = DirectX;

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

Renderer::Renderer(HWND hWnd)
{
	DXGI_SWAP_CHAIN_DESC swapchain_desc = {};
	swapchain_desc.BufferDesc.Width = 0;
	swapchain_desc.BufferDesc.Height = 0;
	swapchain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapchain_desc.BufferDesc.RefreshRate.Numerator = 0;
	swapchain_desc.BufferDesc.RefreshRate.Denominator = 0;
	swapchain_desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapchain_desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapchain_desc.SampleDesc.Count = 1;
	swapchain_desc.SampleDesc.Quality = 0;
	swapchain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapchain_desc.BufferCount = 1;
	swapchain_desc.OutputWindow = hWnd;
	swapchain_desc.Windowed = TRUE;
	swapchain_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapchain_desc.Flags = 0;
	//device for front/back buffers, renderer and swap chain.
	D3D11CreateDeviceAndSwapChain
	(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&swapchain_desc,
		&swap_chain,
		&device,
		nullptr,
		&device_context
	);
	//acess to texture subresource, back buffer
	ID3D11Resource* back_buffer = nullptr;
	swap_chain->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**>(&back_buffer));
	device->CreateRenderTargetView
	(
		back_buffer,
		nullptr,
		&render_target_view
	);
	back_buffer->Release();

	//create depth stensil state
	D3D11_DEPTH_STENCIL_DESC dpstencil_desc = {};
	dpstencil_desc.DepthEnable = TRUE;
	dpstencil_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dpstencil_desc.DepthFunc = D3D11_COMPARISON_LESS;
	wrl::ComPtr<ID3D11DepthStencilState> dpstencil_state;
	device->CreateDepthStencilState(&dpstencil_desc, &dpstencil_state);

	//bind depth state
	device_context->OMSetDepthStencilState(dpstencil_state.Get(), 1u);

	//create depth stensil texture
	wrl::ComPtr<ID3D11Texture2D> texture2d;
	D3D11_TEXTURE2D_DESC descDepth = {};
	descDepth.Width = Constants::WINDOW_WIDTH;
	descDepth.Height = Constants::WINDOW_HEIGHT;
	descDepth.MipLevels = 1u;
	descDepth.ArraySize = 1u;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1u;
	descDepth.SampleDesc.Quality = 0u;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	device->CreateTexture2D(&descDepth, nullptr, &texture2d);

	//create view of depth stensil texture
	D3D11_DEPTH_STENCIL_VIEW_DESC dpstencil_vdesc = {};
	dpstencil_vdesc.Format = DXGI_FORMAT_D32_FLOAT;
	dpstencil_vdesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dpstencil_vdesc.Texture2D.MipSlice = 0u;
	device->CreateDepthStencilView(texture2d.Get(), &dpstencil_vdesc, &depth_stencil_view);

	//bind depth stensil view to OM
	device_context->OMSetRenderTargets(1u, render_target_view.GetAddressOf(), depth_stencil_view.Get());

	device_context->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	D3D11_VIEWPORT viewport;
	viewport.Width = Constants::VIEW_WIDTH;
	viewport.Height = Constants::VIEW_HEIGHT;
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1;
	viewport.TopLeftX = Constants::WINDOW_WIDTH / 2 - Constants::VIEW_WIDTH / 2;
	viewport.TopLeftY = Constants::WINDOW_HEIGHT / 2 - Constants::VIEW_HEIGHT / 2;
	device_context->RSSetViewports(1u, &viewport);
	constant_buffer = std::make_unique<ConstantBuffer>(device.Get(), constantBufferData);
}

void Renderer::ClearBuffer(float red, float green, float blue) noexcept
{
	const float colour[] = { red, green, blue, 1.0f };
	device_context->ClearRenderTargetView(render_target_view.Get(), colour);
	device_context->ClearDepthStencilView(depth_stencil_view.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
}

void Renderer::ClearBuffer(DirectX::XMFLOAT3 colour) noexcept
{
	const float colour_arr[] = { colour.x, colour.y, colour.z, 1.0f };
	device_context->ClearRenderTargetView(render_target_view.Get(), colour_arr);
	device_context->ClearDepthStencilView(depth_stencil_view.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
}

ID3D11Device* Renderer::GetDevice()
{
	return device.Get();
}

ID3D11DeviceContext* Renderer::GetContext()
{
	return device_context.Get();
}

ConstantBuffer::ConstantBufferData& Renderer::GetConstantBufferData()
{
	return constantBufferData;
}

void Renderer::SetModelMatrix(DirectX::XMMATRIX model)
{
	constantBufferData.model = DirectX::XMMatrixTranspose(model);
	constant_buffer->Bind(device_context.Get(), constantBufferData);
}
//void Renderer::SetViewMatrix(DirectX::XMMATRIX view)
//{
//	constantBufferData.view = DirectX::XMMatrixTranspose(view);
//	constant_buffer->Bind(device_context.Get(), constantBufferData);
//}
void Renderer::EndFrame()
{
	swap_chain->Present(1u, 0u);
}
