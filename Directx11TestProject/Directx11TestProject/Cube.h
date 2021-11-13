#pragma once
#include "Renderer.h"
#include <d3d11.h>
#include <wrl.h>
#include <vector>
#include <memory>

namespace wrl = Microsoft::WRL;
namespace dx = DirectX;

class Cube
{
public:
	Cube(Renderer& renderer, float angle, float x, float y, float z);
	~Cube() = default;

	void Update();
	void Render(Renderer& renderer);

private:
	wrl::ComPtr<ID3D11Buffer> pVertexBuffer;
	wrl::ComPtr<ID3D11Buffer> pConstantBuffer;
	wrl::ComPtr<ID3D11Buffer> pConstantBuffer2;
	wrl::ComPtr<ID3D11PixelShader> pPixelShader;
	wrl::ComPtr<ID3D11VertexShader> pVertexShader;
	wrl::ComPtr<ID3D11InputLayout> pInputLayout;

	/// BUFFERS
	VertexBuffer vertex_buffer;
	IndexBuffer index_buffer;

	std::vector<unsigned short> indices_;

	UINT stride;
	UINT offset;
};
