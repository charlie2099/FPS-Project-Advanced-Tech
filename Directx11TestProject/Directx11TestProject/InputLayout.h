#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl.h>
#include <sstream>

class InputLayout
{
public:
	void Create(ID3D11Device* device, Microsoft::WRL::ComPtr <ID3DBlob> blob);
	void Bind(ID3D11DeviceContext* device_context) noexcept;

private:
	Microsoft::WRL::ComPtr<ID3D11InputLayout> input_layout_;
};