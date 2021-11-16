#pragma once
#include "Renderer.h"
#include <string>

class VertexShader
{
public:
	VertexShader(Renderer& renderer, const std::wstring& path, const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout);
	void Bind(Renderer& renderer);

private:
	Microsoft::WRL::ComPtr<ID3DBlob> blob;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> vertex_shader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> input_layout;
};


