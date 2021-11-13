#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl.h>

class VertexShader
{
public:
	void Create(ID3D11Device* device);
	void Bind(ID3D11DeviceContext* device_context) noexcept;
	Microsoft::WRL::ComPtr<ID3DBlob> GetBlob();

private:
	Microsoft::WRL::ComPtr<ID3DBlob> blob_;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> vertex_shader_;
};