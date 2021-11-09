#pragma once
#include "Bindable.h"

class VertexBuffer : public Bindable
{
public:
	template<class V>
	VertexBuffer(Renderer& renderer, const std::vector<V>& vertices)
		:
		stride(sizeof(V))
	{
		D3D11_BUFFER_DESC bd = {};
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.CPUAccessFlags = 0u;
		bd.MiscFlags = 0u;
		bd.ByteWidth = UINT(sizeof(V) * vertices.size());
		bd.StructureByteStride = sizeof(V);
		D3D11_SUBRESOURCE_DATA sd = {};
		sd.pSysMem = vertices.data();
		GetDevice(renderer)->CreateBuffer(&bd, &sd, &pVertexBuffer);
	}
	void Bind(Renderer& renderer) noexcept override;

protected:
	UINT stride;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;
};














//#include <d3d11.h>
//#include <wrl.h>
//#include <vector>
//
//class VertexBuffer
//{
//public:
//	//template<class V>
//	//void Init(ID3D11Device* device, const V vertices, UINT offset)
//	//{
//	//	buffer_size_ = sizeof(vertices);
//
//	//	D3D11_BUFFER_DESC vertex_buffer_desc = {};
//	//	vertex_buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//	//	vertex_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
//	//	vertex_buffer_desc.CPUAccessFlags = 0u;
//	//	vertex_buffer_desc.MiscFlags = 0u;
//	//	vertex_buffer_desc.ByteWidth = sizeof(vertices);
//	//	//vertex_buffer_desc.ByteWidth = UINT(buffer_size_ * sizeof(unsigned short));
//	//	vertex_buffer_desc.StructureByteStride = sizeof(V);
//
//	//	D3D11_SUBRESOURCE_DATA vertex_subr_data = {};
//	//	vertex_subr_data.pSysMem = vertices;
//	//	device->CreateBuffer(&vertex_buffer_desc, &vertex_subr_data, &vertex_buffer_);
//
//	//	offset_ = offset;
//	//	stride_ = sizeof(vertices);
//	//}
//
//	void Init(ID3D11Device* device, const std::vector<double> vertices, UINT offset);
//	//void Init(ID3D11Device* device, const Vertex vertices[], UINT offset);
//	//void Init(ID3D11Device* device, const std::vector<unsigned short>& vertices, UINT offset);
//	void Bind(ID3D11DeviceContext* device_context, UINT start_slot, UINT num_of_buffers) noexcept;
//	UINT GetBufferSize() const noexcept;
//
//private:
//	Microsoft::WRL::ComPtr<ID3D11Buffer> vertex_buffer_;
//	UINT buffer_size_;
//	UINT offset_ = 0u;
//	UINT stride_ = 0u;
//};