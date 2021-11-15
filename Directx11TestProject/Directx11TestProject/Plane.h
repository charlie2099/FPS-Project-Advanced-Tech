#pragma once
#include "Renderer.h"
#include "Vertex.h"
#include <d3d11.h>
#include <wrl.h>
#include <vector>
#include <memory>

namespace wrl = Microsoft::WRL;
namespace dx = DirectX;

class Plane
{
public:
	Plane(Renderer& renderer, dx::XMFLOAT3 pos);
	~Plane() = default;

	void Update();
	void Render(Renderer& renderer);

	void setPosition(dx::XMMATRIX pos);
	void setRotation(dx::XMMATRIX rot);

private:
	void Binds(Renderer& renderer);

	UINT stride;
	UINT offset;

	dx::XMFLOAT3 pos_;
	dx::XMFLOAT3 rot_;

	wrl::ComPtr<ID3D11Buffer> vertex_buffer_old; //VertexBuffer vertex_buffer;
	IndexBuffer index_buffer;
	ConstantBuffer constant_buffer;
	//ConstantBuffer constant_buffer2_new;
	wrl::ComPtr<ID3D11Buffer> constant_buffer2;

	PixelShader pixel_shader;
	VertexShader vertex_shader;

	InputLayout input_layout;
};