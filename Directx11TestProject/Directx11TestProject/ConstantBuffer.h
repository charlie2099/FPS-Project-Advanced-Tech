#pragma once
#include <DirectXMath.h>
#include <d3d11.h>
#include <wrl.h>

class ConstantBuffer
{
public:
	struct Data
	{
		DirectX::XMMATRIX world;
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX projection;
	};

	ConstantBuffer(ID3D11Device* device, const Data& bufferData);
	void Bind(ID3D11DeviceContext* device_context, const Data& bufferData);

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> constant_buffer;
};
