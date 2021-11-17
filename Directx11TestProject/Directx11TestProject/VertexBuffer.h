#pragma once
#include "Renderer.h"
#include "Vertex.h"

class VertexBuffer
{
public:
	VertexBuffer(Renderer& renderer, const std::vector<Vertex>& vertices);
	void Bind(Renderer& renderer);

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> vertex_buffer;
	UINT stride;
};