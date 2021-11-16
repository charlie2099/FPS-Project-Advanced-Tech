#pragma once
#include "Renderer.h"
#include <string>

class InputLayout
{
public:
	InputLayout(Renderer& renderer, const std::wstring& path);
	void Bind(Renderer& renderer);

private:
	Microsoft::WRL::ComPtr<ID3D11InputLayout> input_layout;

protected:
	Microsoft::WRL::ComPtr<ID3DBlob> blob;
};