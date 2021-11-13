#include "PixelShader.h"

void PixelShader::Create(ID3D11Device* device)
{
	D3DReadFileToBlob(L"PixelShader.cso", &blob_);
	device->CreatePixelShader(blob_->GetBufferPointer(), blob_->GetBufferSize(), nullptr, &pixel_shader_);
}

void PixelShader::Bind(ID3D11DeviceContext* device_context) noexcept
{
	device_context->PSSetShader(pixel_shader_.Get(), nullptr, 0u);
}
