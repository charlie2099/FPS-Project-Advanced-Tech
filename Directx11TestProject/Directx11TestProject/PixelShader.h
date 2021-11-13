#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl.h>

class PixelShader
{
public:
	void Create(ID3D11Device* device);
	void Bind(ID3D11DeviceContext* device_context) noexcept;

private:
	Microsoft::WRL::ComPtr<ID3DBlob> blob_;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pixel_shader_;
};