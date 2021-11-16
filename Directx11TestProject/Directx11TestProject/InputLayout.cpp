#include "InputLayout.h"

InputLayout::InputLayout(Renderer& renderer, const std::wstring& path)
{
	std::vector<D3D11_INPUT_ELEMENT_DESC> input_element_desc
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	D3DReadFileToBlob(path.c_str(), &blob);
	renderer.GetDevice()->CreateInputLayout(input_element_desc.data(), input_element_desc.size(), blob->GetBufferPointer(), blob->GetBufferSize(), &input_layout);
}

void InputLayout::Bind(Renderer& renderer)
{
	renderer.GetContext()->IASetInputLayout(input_layout.Get());
}