#pragma once
#include <DirectXMath.h>
#include <d3d11.h>
#include <wrl.h>

class ConstantBuffer
{
public:
	struct Data
	{
		DirectX::XMMATRIX model = DirectX::XMMatrixTranspose(DirectX::XMMatrixIdentity());
		DirectX::XMMATRIX view = DirectX::XMMatrixTranspose(DirectX::XMMatrixTranslation(0.0F, 0.0F, 0.0f));
		DirectX::XMMATRIX projection = DirectX::XMMatrixTranspose(DirectX::XMMatrixPerspectiveRH(1.0F, 3.0F / 4.0F, 0.5F, 100.0F));
	};

	ConstantBuffer(ID3D11Device* device, const Data& bufferData);
	void Bind(ID3D11DeviceContext* device_context, const Data& bufferData);

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> constant_buffer;
};
