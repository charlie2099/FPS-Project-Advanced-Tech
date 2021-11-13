#include "ConstantBuffer.h"

void ConstantBuffer::Init(ID3D11Device* device, dx::XMMATRIX const_buffer)
{
	buffer_size_ = sizeof(const_buffer);

	D3D11_BUFFER_DESC cbd;
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.MiscFlags = 0u;
	cbd.ByteWidth = sizeof(const_buffer); // dx::XMMATRIX
	cbd.StructureByteStride = 0u;

	D3D11_SUBRESOURCE_DATA subr_data = {};
	subr_data.pSysMem = &const_buffer;
	device->CreateBuffer(&cbd, &subr_data, &constant_buffer_);
}

void ConstantBuffer::Init(ID3D11Device* device, float const_buffer)
{
	//buffer_size_ = sizeof(const_buffer);

	D3D11_BUFFER_DESC cbd;
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.MiscFlags = 0u;
	cbd.ByteWidth = sizeof(const_buffer);
	cbd.StructureByteStride = 0u;

	D3D11_SUBRESOURCE_DATA subr_data = {};
	subr_data.pSysMem = &const_buffer;
	device->CreateBuffer(&cbd, &subr_data, &constant_buffer_);
}


void ConstantBuffer::BindToVS(ID3D11DeviceContext* device_context) noexcept
{
	device_context->VSSetConstantBuffers(0u, 1u, constant_buffer_.GetAddressOf());
}

void ConstantBuffer::BindToPS(ID3D11DeviceContext* device_context) noexcept
{
	device_context->PSSetConstantBuffers(0u, 1u, constant_buffer_.GetAddressOf());
}

UINT ConstantBuffer::GetBufferSize() const noexcept
{
	return buffer_size_;
}