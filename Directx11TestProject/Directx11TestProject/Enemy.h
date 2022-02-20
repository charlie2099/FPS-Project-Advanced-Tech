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
	DirectX::XMFLOAT2 GetSize() { return size_; };
	DirectX::XMFLOAT3 GetPos() { return position_; };
	bool IsDestroyed() { return destroyed_; };

	static int enemy_count;

private:
	Renderer* renderer_ = nullptr;
	DirectX::XMMATRIX transform_ = DirectX::XMMatrixIdentity();
	DirectX::XMFLOAT2 size_;
	DirectX::XMFLOAT3 position_;
	float rotation_ = 0;
	bool destroyed_ = false;

	std::unique_ptr<PixelShader> pixel_shader;
	std::unique_ptr<VertexShader> vertex_shader;
	std::unique_ptr<VertexBuffer> vertex_buffer;
	std::unique_ptr<IndexBuffer> index_buffer;
	std::unique_ptr<Texture> texture;
	std::unique_ptr<TextureSampler> texture_sampler;
};


