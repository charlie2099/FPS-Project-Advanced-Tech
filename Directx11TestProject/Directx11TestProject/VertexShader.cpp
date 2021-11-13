#include "VertexShader.h"

void VertexShader::Create(ID3D11Device* device)
{
	D3DReadFileToBlob(L"VertexShader.cso", &blob_);
	device->CreateVertexShader(blob_->GetBufferPointer(), blob_->GetBufferSize(), nullptr, &vertex_shader_);
}

void VertexShader::Bind(ID3D11DeviceContext* device_context) noexcept
{
	device_context->VSSetShader(vertex_shader_.Get(), nullptr, 0u);
}

Microsoft::WRL::ComPtr<ID3DBlob> VertexShader::GetBlob()
{
	return blob_;
}


