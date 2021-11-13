#include "InputLayout.h"

void InputLayout::Create(ID3D11Device* device, Microsoft::WRL::ComPtr <ID3DBlob> blob)
{
	const D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	device->CreateInputLayout(
		ied, (UINT)std::size(ied),
		blob->GetBufferPointer(),
		blob->GetBufferSize(),
		&input_layout_
	);
}

void InputLayout::Bind(ID3D11DeviceContext* device_context) noexcept
{
	device_context->IASetInputLayout(input_layout_.Get());
}
