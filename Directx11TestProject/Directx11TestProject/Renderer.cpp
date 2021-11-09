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
	descDepth.Width = 800u;
	descDepth.Height = 600u;
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

void Renderer::DrawCube(float angle, float x, float y, float z)
{
	//namespace wrl = Microsoft::WRL;
	//HRESULT hr;

	//v_buffer.createVBuffer(device.Get(), vertices , 0u );
	//v_buffer.bindVBuffer(device_context.Get(), 0, 1);

	struct Vertex
	{
		struct
		{  
			float x;
			float y;
			float z;
		} pos;
	};

	// vertex buffer 
	const Vertex vertices[] =
	//const /*std::vector<*/Vertex/*>*/ vertices[] =
	//const std::vector<Vertex> vertices =
	{
		{-1.0, -1.0f, -1.0f },
		{1.0f, -1.0f, -1.0f},
		{-1.0f, 1.0f, -1.0f},
		{1.0f, 1.0f, -1.0f},
		{-1.0f, -1.0f, 1.0f},
		{1.0f, -1.0f, 1.0f},
		{-1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f},

		//{0.0f, 0.5f, 255, 0, 0, 0}, //v1
		//{0.5f, -0.5f, 0, 255, 0, 0}, //v2..
		//{-0.5f, -0.5f, 0, 0, 255, 0},
		//{-0.3f, 0.3f, 0, 255, 0, 0},
		//{0.3f, 0.3f, 0, 0, 255, 0}, 
		//{0.0f, -1.0f, 255, 0, 0, 0}, 
	};

	//vertex_buffer.Init(device.Get(), vertices, 0u);
	//vertex_buffer.Bind(device_context.Get(), 0u, 1u);

	wrl::ComPtr<ID3D11Buffer> pVertexBuffer;
	D3D11_BUFFER_DESC bd = {};
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.CPUAccessFlags = 0u;
	bd.MiscFlags = 0u;
	bd.ByteWidth = sizeof(Vertex) * ARRAYSIZE(vertices);
	bd.StructureByteStride = sizeof(Vertex);  
	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem = vertices/*.data()*/;
	device->CreateBuffer(&bd, &sd, &pVertexBuffer);
	
	// Bind vertex buffer to pipeline
	const UINT stride = sizeof(Vertex);
	const UINT offset = 0u;
	device_context->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);



	// index buffer
	const std::vector<unsigned short> indices =
	{
		0,2,1, 2,3,1,
		1,3,5, 3,7,5,
		2,6,3, 3,6,7,
		4,5,7, 4,7,6,
		0,4,2, 2,4,6,
		0,1,4, 1,5,4

		/*0,1,2,
		0,2,3,
		0,4,1,
		2,1,5,*/
	};

	index_buffer.Init(device.Get(), indices);
	index_buffer.Bind(device_context.Get(), 0u);






	// constant buffer for transformation matrix
	struct ConstantBuffer
	{
		dx::XMMATRIX transform;
	};

	const ConstantBuffer const_buffer =
	{
		{
			dx::XMMatrixTranspose(
				dx::XMMatrixRotationZ(angle) *
				dx::XMMatrixRotationX(angle) *
				dx::XMMatrixTranslation(x, y, z + 4.0f) *
				dx::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 60.0f) // 10
			) 
		}
	};
	wrl::ComPtr<ID3D11Buffer> pConstantBuffer;
	D3D11_BUFFER_DESC cbd;
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.MiscFlags = 0u;
	cbd.ByteWidth = sizeof(const_buffer);
	cbd.StructureByteStride = 0u;
	D3D11_SUBRESOURCE_DATA csd = {};
	csd.pSysMem = &const_buffer;
	device->CreateBuffer(&cbd, &csd, &pConstantBuffer);

	// bind constant buffer to vertex shader
	device_context->VSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf());

	struct ConstantBuffer2
	{
		struct
		{
			float r;
			float g;
			float b;
			float a;
		} face_colours[6];
	};
	struct ConstantBuffer2 cb2 =
	{
		{
			//{1.0f, 0.0f, 1.0f}, //pink
			//{0.0f, 1.0f, 0.0f}, //red
			//{0.0f, 1.0f, 0.0f}, //green
			//{0.0f, 0.0f, 1.0f}, //blue
			//{1.0f, 1.0f, 0.0f}, // yellow
			//{0.0f, 1.0f, 1.0f}, //light-blue

		    /*{0.0f, 0.0f, 0.0f},
		    {1.0f, 1.0f, 1.0f},
		    {0.0f, 0.0f, 0.0f},
		    {1.0f, 1.0f, 1.0f},
		    {0.0f, 0.0f, 0.0f},
		    {1.0f, 1.0f, 1.0f},*/

			{0.0f, 0.5f, 1.0f},
			{0.2f, 0.2f, 0.7f},
			{0.1f, 0.8f, 0.5f},
			{0.5f, 1.0f, 0.2f},
			{0.4f, 0.3f, 0.8f},
			{0.8f, 0.9f, 0.3f},
		}
	};
	wrl::ComPtr<ID3D11Buffer> pConstantBuffer2;
	D3D11_BUFFER_DESC cbd2;
	cbd2.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd2.Usage = D3D11_USAGE_DYNAMIC;
	cbd2.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd2.MiscFlags = 0u;
	cbd2.ByteWidth = sizeof(cb2);
	cbd2.StructureByteStride = 0u;
	D3D11_SUBRESOURCE_DATA csd2 = {};
	csd2.pSysMem = &cb2;
	device->CreateBuffer(&cbd2, &csd2, &pConstantBuffer2);

	// bind constant buffer to pixel shader
	device_context->PSSetConstantBuffers(0u, 1u, pConstantBuffer2.GetAddressOf());


	// create pixel shader
	wrl::ComPtr<ID3D11PixelShader> pPixelShader;
	wrl::ComPtr<ID3DBlob> pBlob;
	D3DReadFileToBlob(L"PixelShader.cso", &pBlob);
	device->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader);
	// bind pixel shader
	device_context->PSSetShader(pPixelShader.Get(), nullptr, 0u);


	// create vertex shader
	wrl::ComPtr<ID3D11VertexShader> pVertexShader;
	D3DReadFileToBlob(L"VertexShader.cso", &pBlob);
	device->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader);
	// bind vertex shader
	device_context->VSSetShader(pVertexShader.Get(), nullptr, 0u);


	// input (vertex) layout (2d position only)
	wrl::ComPtr<ID3D11InputLayout>pInputLayout;
	const D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	device->CreateInputLayout(
		ied, (UINT)std::size(ied),
		pBlob->GetBufferPointer(),
		pBlob->GetBufferSize(),
		&pInputLayout
	);
	// bind vertex layout
	device_context->IASetInputLayout(pInputLayout.Get());

	// Set primitive topology to triangle list (groups of 3 vertices)
	device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// configure viewport
	D3D11_VIEWPORT vp;
	vp.Width = 800;
	vp.Height = 600;
	vp.MinDepth = 0;
	vp.MaxDepth = 1;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	device_context->RSSetViewports(1u, &vp);

	device_context->DrawIndexed((UINT)std::size(indices), 0u, 0u);
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