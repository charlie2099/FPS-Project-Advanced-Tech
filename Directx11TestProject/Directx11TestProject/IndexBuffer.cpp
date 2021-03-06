#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(Renderer& renderer, const std::vector<unsigned short>& indices)
{
	index_count_ = indices.size();

	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER; // What to set the buffer up as
	bufferDesc.Usage = D3D11_USAGE_DEFAULT; // What the buffer will be used for
	bufferDesc.CPUAccessFlags = 0U; // Whether the CPU needs to access the buffer (it doesn't yet)
	bufferDesc.MiscFlags = 0u; // 
	bufferDesc.ByteWidth = static_cast<unsigned int>(indices.size() * sizeof(unsigned short)); // Size of the buffer in bytes
	bufferDesc.StructureByteStride = sizeof(unsigned short); // Size of each index
	D3D11_SUBRESOURCE_DATA subresourceData = {};
	subresourceData.pSysMem = indices.data(); // Triangles to use
	renderer.GetDevice()->CreateBuffer(&bufferDesc, &subresourceData, &index_buffer);
}

void IndexBuffer::Bind(Renderer& renderer)
{
	renderer.GetDeviceContext()->IASetIndexBuffer(index_buffer.Get(), DXGI_FORMAT_R16_UINT, 0u);
}

UINT IndexBuffer::GetIndexCount()
{
	return index_count_;
}
