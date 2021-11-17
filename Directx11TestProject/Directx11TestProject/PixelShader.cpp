#include "PixelShader.h"

PixelShader::PixelShader(Renderer& renderer, const std::wstring& path)
{
	Microsoft::WRL::ComPtr<ID3DBlob> blob_;
	D3DReadFileToBlob(path.c_str(), &blob_);
	renderer.GetDevice()->CreatePixelShader(blob_->GetBufferPointer(), blob_->GetBufferSize(), nullptr, &pixel_shader_);
}

void PixelShader::Bind(Renderer& renderer)
{
	renderer.GetDeviceContext()->PSSetShader(pixel_shader_.Get(), nullptr, 0u);
}
