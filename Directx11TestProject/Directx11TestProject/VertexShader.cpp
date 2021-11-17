#include "VertexShader.h"

//VertexShader::VertexShader(Renderer& renderer)
//{
//	renderer.GetDevice()->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &vertex_shader);
//}
//
//void VertexShader::Bind(Renderer& renderer)
//{
//	renderer.GetDeviceContext()->VSSetShader(vertex_shader.Get(), nullptr, 0u);
//}

VertexShader::VertexShader(Renderer& renderer, const std::wstring& path)
{
	std::vector<D3D11_INPUT_ELEMENT_DESC> input_element_desc
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	D3DReadFileToBlob(path.c_str(), &blob);
	renderer.GetDevice()->CreateInputLayout(input_element_desc.data(), input_element_desc.size(), blob->GetBufferPointer(), blob->GetBufferSize(), &input_layout);

	renderer.GetDevice()->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &vertex_shader);
}

void VertexShader::Bind(Renderer& renderer)
{
	renderer.GetDeviceContext()->IASetInputLayout(input_layout.Get());
	renderer.GetDeviceContext()->VSSetShader(vertex_shader.Get(), nullptr, 0u);
}
