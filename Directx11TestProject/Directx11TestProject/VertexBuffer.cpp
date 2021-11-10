#include "VertexBuffer.h"

void VertexBuffer::Init(ID3D11Device* device, const std::vector<double> vertices, UINT offset)
{
	//buffer_size_ = (UINT)vertices.size();

	//D3D11_BUFFER_DESC vertex_buffer_desc = {};
	//vertex_buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//vertex_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	//vertex_buffer_desc.CPUAccessFlags = 0u;
	//vertex_buffer_desc.MiscFlags = 0u;
	//vertex_buffer_desc.ByteWidth = sizeof(vertices);
	////vertex_buffer_desc.ByteWidth = UINT(buffer_size_ * sizeof(unsigned short));
	//vertex_buffer_desc.StructureByteStride = sizeof(vertices);
	////vertex_buffer_desc.StructureByteStride = sizeof(unsigned short);

	//D3D11_SUBRESOURCE_DATA vertex_subr_data = {};
	//vertex_subr_data.pSysMem = vertices.data();
	////vertex_subr_data.pSysMem = vertices.data();
	//device->CreateBuffer(&vertex_buffer_desc, &vertex_subr_data, &vertex_buffer_);

	//offset_ = offset;
	//stride_ = sizeof(vertices);



	//buffer_size_ = sizeof(vertices);

	//D3D11_BUFFER_DESC vertex_buffer_desc = {};
	//vertex_buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//vertex_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	//vertex_buffer_desc.CPUAccessFlags = 0u;
	//vertex_buffer_desc.MiscFlags = 0u;
	//vertex_buffer_desc.ByteWidth = sizeof(vertices);
	////vertex_buffer_desc.ByteWidth = UINT(buffer_size_ * sizeof(unsigned short));
	//vertex_buffer_desc.StructureByteStride = sizeof(V);

	//D3D11_SUBRESOURCE_DATA vertex_subr_data = {};
	//vertex_subr_data.pSysMem = vertices;
	//device->CreateBuffer(&vertex_buffer_desc, &vertex_subr_data, &vertex_buffer_);

	//offset_ = offset;
	//stride_ = sizeof(vertices);
}

void VertexBuffer::Bind(ID3D11DeviceContext* device_context, UINT start_slot, UINT num_of_buffers) noexcept
{
	device_context->IASetVertexBuffers(start_slot, num_of_buffers, vertex_buffer_.GetAddressOf(), &stride_, &offset_);
}

UINT VertexBuffer::GetBufferSize() const noexcept
{
	return buffer_size_;
}
