#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(Renderer& renderer, const std::vector<Vertex>& vertices) : stride(sizeof(Vertex))
{
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.CPUAccessFlags = 0U;
	bufferDesc.MiscFlags = 0U;
	bufferDesc.ByteWidth = UINT(sizeof(Vertex) * vertices.size());
	bufferDesc.StructureByteStride = sizeof(Vertex);

	D3D11_SUBRESOURCE_DATA subresourceData = {};
	subresourceData.pSysMem = vertices.data();
	renderer.GetDevice()->CreateBuffer(&bufferDesc, &subresourceData, &vertex_buffer);
}

void VertexBuffer::Bind(Renderer& renderer)
{
	const UINT offset = 0u;
	renderer.GetContext()->IASetVertexBuffers(0u, 1u, vertex_buffer.GetAddressOf(), &stride, &offset);
}