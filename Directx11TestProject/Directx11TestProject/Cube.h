#pragma once
#include "Renderer.h"
#include "BindableHeaders.h"

class Cube
{
public:
	//Cube(Renderer& renderer);
	//Cube() = default;
	Cube(Renderer& getRenderer, DirectX::XMFLOAT3 size, DirectX::XMFLOAT3 pos);

	void Render(Renderer& getRenderer);
	void SetPos(DirectX::XMFLOAT3 pos);

	DirectX::XMMATRIX transform = DirectX::XMMatrixIdentity();

private:
	std::unique_ptr<PixelShader> pixel_shader;
	std::unique_ptr<VertexShader> vertex_shader;
	std::unique_ptr<VertexBuffer> vertex_buffer;
	//std::unique_ptr<InputLayout> input_layout;
	std::unique_ptr<IndexBuffer> index_buffer;
	std::unique_ptr<Texture> texture;
	std::unique_ptr<TextureSampler> texture_sampler;

	DirectX::XMFLOAT3 pos_;
	Renderer* renderer_ = nullptr;
};

