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
	UINT stride;
	UINT offset;

	//VertexBuffer vertex_buffer;
	IndexBuffer index_buffer;
	ConstantBuffer constant_buffer_class;

	wrl::ComPtr<ID3D11Buffer> vertex_buffer_old;
	//wrl::ComPtr<ID3D11Buffer> constant_buffer;
	wrl::ComPtr<ID3D11Buffer> constant_buffer2;
	wrl::ComPtr<ID3D11PixelShader> pixel_shader;
	wrl::ComPtr<ID3D11VertexShader> vertex_shader;
	wrl::ComPtr<ID3D11InputLayout> input_layout;
};
