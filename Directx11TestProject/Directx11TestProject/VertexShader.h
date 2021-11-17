#pragma once
#include "Renderer.h"
//#include "InputLayout.h"
#include <string>

//class VertexShader
//{
//public:
//	VertexShader(Renderer& renderer);
//	void Bind(Renderer& renderer);
//
//private:
//	Microsoft::WRL::ComPtr<ID3D11VertexShader> vertex_shader;
//
//	friend class InputLayout;
//};

class VertexShader
{
public:
	VertexShader(Renderer& renderer, const std::wstring& path);
	void Bind(Renderer& renderer);

private:
	Microsoft::WRL::ComPtr<ID3DBlob> blob;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> vertex_shader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> input_layout;
};


