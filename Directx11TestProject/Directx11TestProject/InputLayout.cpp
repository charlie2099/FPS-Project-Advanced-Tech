#include "InputLayout.h"

InputLayout::InputLayout(Renderer& renderer,
	const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout,
	ID3DBlob* pVertexShaderBytecode)
{
	GetDevice(renderer)->CreateInputLayout(
		layout.data(), (UINT)layout.size(),
		pVertexShaderBytecode->GetBufferPointer(),
		pVertexShaderBytecode->GetBufferSize(),
		&pInputLayout
	);
}

void InputLayout::Bind(Renderer& renderer) noexcept
{
	GetDeviceContext(renderer)->IASetInputLayout(pInputLayout.Get());
}