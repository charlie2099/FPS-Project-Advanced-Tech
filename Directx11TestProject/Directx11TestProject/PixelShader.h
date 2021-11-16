#pragma once
#include "Renderer.h"
#include <string>
#include <d3dcompiler.h>
#include <wrl.h>

class PixelShader
{
public:
	PixelShader(Renderer& renderer, const std::wstring& path);
	void Bind(Renderer& renderer);

private:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pixel_shader_;
};