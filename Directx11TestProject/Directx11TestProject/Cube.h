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
	void Binds(Renderer& renderer);

	UINT stride;
	UINT offset;

	wrl::ComPtr<ID3D11Buffer> vertex_buffer_old; //VertexBuffer vertex_buffer;
	IndexBuffer index_buffer;
	ConstantBuffer constant_buffer;
	//ConstantBuffer constant_buffer2_new;
	wrl::ComPtr<ID3D11Buffer> constant_buffer2;

	PixelShader pixel_shader;
	VertexShader vertex_shader;

	InputLayout input_layout;
};
