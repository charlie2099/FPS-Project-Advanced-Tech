#include "PixelShader.h"

PixelShader::PixelShader(Renderer& renderer, const std::wstring& path)
{
	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	D3DReadFileToBlob(path.c_str(), &pBlob);
	GetDevice(renderer)->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader);
}

void PixelShader::Bind(Renderer& renderer) noexcept
{
	GetDeviceContext(renderer)->PSSetShader(pPixelShader.Get(), nullptr, 0u);
}