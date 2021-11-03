#include "VertexBuffer.h"

void VertexBuffer::createVBuffer(ID3D11Device* device, const std::vector<Vertex>& vertices, UINT offset)
{
	buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	buffer_desc.CPUAccessFlags = 0u;
	buffer_desc.MiscFlags = 0u;
	buffer_desc.ByteWidth = sizeof(vertices);
	buffer_desc.StructureByteStride = sizeof(Vertex);
	subresource_data.pSysMem = vertices.data();
	device->CreateBuffer(&buffer_desc, &subresource_data, &vertex_buffer);

	offset_ = offset;
	stride_ = sizeof(Vertex);
}

void VertexBuffer::bindVBuffer(ID3D11DeviceContext* device_context, UINT start_slot, UINT num_of_buffers)
{
	device_context->IASetVertexBuffers(start_slot, num_of_buffers, vertex_buffer.GetAddressOf(), &stride_, &offset_);
}
