#include "VertexShader.h"

VertexShader::VertexShader(Renderer& renderer, const std::wstring& path)
{
	D3DReadFileToBlob(path.c_str(), &pBytecodeBlob);
	GetDevice(renderer)->CreateVertexShader(
		pBytecodeBlob->GetBufferPointer(),
		pBytecodeBlob->GetBufferSize(),
		nullptr,
		&pVertexShader
	);
}

void VertexShader::Bind(Renderer& renderer) noexcept
{
	GetDeviceContext(renderer)->VSSetShader(pVertexShader.Get(), nullptr, 0u);
}

ID3DBlob* VertexShader::GetBytecode() const noexcept
{
	return pBytecodeBlob.Get();
}