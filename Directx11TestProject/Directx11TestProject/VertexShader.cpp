#include "VertexShader.h"

VertexShader::VertexShader(Renderer& renderer, const std::wstring& path, const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout)
{
	D3DReadFileToBlob(path.c_str(), &blob);
	renderer.GetDevice()->CreateInputLayout(layout.data(), layout.size(), blob->GetBufferPointer(), blob->GetBufferSize(), &input_layout);

	renderer.GetDevice()->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &vertex_shader);
}

void VertexShader::Bind(Renderer& renderer)
{
	renderer.GetContext()->IASetInputLayout(input_layout.Get());
	renderer.GetContext()->VSSetShader(vertex_shader.Get(), nullptr, 0u);
}
