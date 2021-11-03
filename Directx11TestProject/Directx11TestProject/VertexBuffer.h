#pragma once
#include <d3d11.h>
#include <wrl.h>
#include <vector>

class VertexBuffer
{
public:
	VertexBuffer() = default;
	~VertexBuffer() = default;

	struct Vertex
	{
		struct
		{
			float x;
			float y;
			float z;
		} pos;
	};

	void createVBuffer(ID3D11Device* device, const std::vector<Vertex>& vertices, UINT offset);
	void bindVBuffer(ID3D11DeviceContext* device_context, UINT start_slot, UINT num_of_buffers);

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> vertex_buffer;
	D3D11_BUFFER_DESC buffer_desc = {};
	D3D11_SUBRESOURCE_DATA subresource_data{};

	UINT offset_ = 0u;
	UINT stride_ = 0u;

	
};