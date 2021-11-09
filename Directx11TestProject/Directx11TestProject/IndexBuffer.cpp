#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(Renderer& renderer, const std::vector<unsigned short>& indices)
	:
	count((UINT)indices.size())
{
	D3D11_BUFFER_DESC ibd = {};
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.CPUAccessFlags = 0u;
	ibd.MiscFlags = 0u;
	ibd.ByteWidth = UINT(count * sizeof(unsigned short));
	ibd.StructureByteStride = sizeof(unsigned short);
	D3D11_SUBRESOURCE_DATA isd = {};
	isd.pSysMem = indices.data();

    GetDevice(renderer)->CreateBuffer(&ibd, &isd, &pIndexBuffer);
}

void IndexBuffer::Bind(Renderer& renderer) noexcept
{
	GetDeviceContext(renderer)->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0u);
}

UINT IndexBuffer::GetCount() const noexcept
{
	return count;
}

//void IndexBuffer::Init(ID3D11Device* device, const std::vector<unsigned short>& indices)
//{
//	buffer_size_ = (UINT)indices.size();
//
//	D3D11_BUFFER_DESC index_buffer_desc = {};
//	index_buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
//	index_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
//	index_buffer_desc.CPUAccessFlags = 0u;
//	index_buffer_desc.MiscFlags = 0u;
//	index_buffer_desc.ByteWidth = UINT(buffer_size_ * sizeof(unsigned short));
//	index_buffer_desc.StructureByteStride = sizeof(unsigned short);
//
//	D3D11_SUBRESOURCE_DATA index_subr_data = {};
//	index_subr_data.pSysMem = indices.data();
//	device->CreateBuffer(&index_buffer_desc, &index_subr_data, &index_buffer_);
//}
//
//
//void IndexBuffer::Bind(ID3D11DeviceContext* device_context, UINT offset) noexcept
//{
//	device_context->IASetIndexBuffer(index_buffer_.Get(), DXGI_FORMAT_R16_UINT, offset);
//}
//
//UINT IndexBuffer::GetBufferSize() const noexcept
//{
//	return buffer_size_;
//}