#pragma once
#include <d3d11.h>
#include <wrl.h>
#include <vector>
#include <directxmath.h>

namespace dx = DirectX;

class ConstantBuffer
{
public:
	void Init(ID3D11Device* device, dx::XMMATRIX const_buffer);
	void Init(ID3D11Device* device, float const_buffer);
	void BindToVS(ID3D11DeviceContext* device_context) noexcept;
	void BindToPS(ID3D11DeviceContext* device_context) noexcept;
	UINT GetBufferSize() const noexcept;

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> constant_buffer_;
	UINT buffer_size_;
};
