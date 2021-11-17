#pragma once
#include "Renderer.h"

class IndexBuffer
{
public:
	IndexBuffer(Renderer& renderer, const std::vector<unsigned short>& indices);
	void Bind(Renderer& renderer);
	UINT GetIndexCount();

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> index_buffer;
	UINT index_count_ = 0;
};
