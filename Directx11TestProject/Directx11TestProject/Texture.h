#pragma once
#include "Renderer.h"
#include <string>

class Texture
{
public:
	Texture(Renderer& renderer, const std::wstring& filepath);
	void Bind(Renderer& renderer);
private:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shaderResourceView;
};
