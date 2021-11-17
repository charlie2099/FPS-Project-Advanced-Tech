#pragma once
#include "Renderer.h"
#include "BindableHeaders.h"

class Plane
{
public:
	Plane(Renderer& renderer, DirectX::XMFLOAT2 size, DirectX::XMFLOAT3 pos);
	void Render(Renderer& renderer);

	void SetPos(DirectX::XMFLOAT3 pos);
	DirectX::XMFLOAT3 GetPos() { return position_; };

private:
	DirectX::XMMATRIX transform_;
	DirectX::XMFLOAT3 position_;
	Renderer* renderer_ = nullptr;

	std::unique_ptr<PixelShader> pixel_shader;
	std::unique_ptr<VertexShader> vertex_shader;
	std::unique_ptr<VertexBuffer> vertex_buffer;
	std::unique_ptr<IndexBuffer> index_buffer;
	std::unique_ptr<Texture> texture;
	std::unique_ptr<TextureSampler> texture_sampler;
};

