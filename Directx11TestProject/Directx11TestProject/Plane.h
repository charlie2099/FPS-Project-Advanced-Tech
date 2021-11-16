#pragma once
#include "Renderer.h"
#include "BindableHeaders.h"

class Plane
{
public:
	Plane(Renderer& getRenderer, DirectX::XMFLOAT2 size, DirectX::XMFLOAT3 pos);
	void Render(Renderer& getRenderer);
	DirectX::XMMATRIX transform = DirectX::XMMatrixIdentity();

private:
	std::unique_ptr<PixelShader> pixel_shader;
	std::unique_ptr<VertexShader> vertex_shader;
	std::unique_ptr<VertexBuffer> vertex_buffer;
	std::unique_ptr<IndexBuffer> index_buffer;
	std::unique_ptr<Texture> texture;
	std::unique_ptr<TextureSampler> texture_sampler;
};

