#pragma once
#include "Renderer.h"
#include "BindableHeaders.h"

class Enemy
{
public:
	Enemy(Renderer& renderer, DirectX::XMFLOAT2 size, DirectX::XMFLOAT3 pos, float rot = 0);
	void Render(Renderer& renderer);

	void Destroy();

	// SETTERS
	void SetPos(DirectX::XMFLOAT3 pos);
	void SetRotation(float rot);

	// GETTERS
	DirectX::XMFLOAT3 GetPos() { return position_; };
	bool IsAlive() { return alive_; };

private:
	DirectX::XMMATRIX transform_ = DirectX::XMMatrixIdentity();
	DirectX::XMFLOAT3 position_;
	DirectX::XMFLOAT3 size_;
	float rotation_ = 0;
	bool alive_ = true;
	Renderer* renderer_ = nullptr;

	std::unique_ptr<PixelShader> pixel_shader;
	std::unique_ptr<VertexShader> vertex_shader;
	std::unique_ptr<VertexBuffer> vertex_buffer;
	std::unique_ptr<IndexBuffer> index_buffer;
	std::unique_ptr<Texture> texture;
	std::unique_ptr<TextureSampler> texture_sampler;
};


