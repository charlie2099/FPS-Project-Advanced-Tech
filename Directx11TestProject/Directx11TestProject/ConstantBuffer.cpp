#include "ConstantBuffer.h"

ConstantBuffer::ConstantBuffer(ID3D11Device* device, const Data& bufferData)
{
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.MiscFlags = 0u;
	bufferDesc.ByteWidth = sizeof(bufferData);
	bufferDesc.StructureByteStride = 0u;

	D3D11_SUBRESOURCE_DATA subresourceData = {};
	subresourceData.pSysMem = &bufferData;
	device->CreateBuffer(&bufferDesc, &subresourceData, &constant_buffer);
}

void ConstantBuffer::Bind(ID3D11DeviceContext* device_context, const Data& bufferData)
{
	D3D11_MAPPED_SUBRESOURCE mappedSubresource;
	device_context->Map(constant_buffer.Get(), 0U, D3D11_MAP_WRITE_DISCARD, 0U, &mappedSubresource);
	memcpy(mappedSubresource.pData, &bufferData, sizeof(bufferData));
	device_context->Unmap(constant_buffer.Get(), 0U);

	device_context->VSSetConstantBuffers(0U, 1U, constant_buffer.GetAddressOf());
}
