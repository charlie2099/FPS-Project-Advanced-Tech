#pragma once
#include <d3d11.h>
#include <wrl.h>
#include <vector>

class IndexBuffer
{
public:
	void Init(ID3D11Device* device, const std::vector<unsigned short>& indices);
	void Bind(ID3D11DeviceContext* device_context, UINT offset) noexcept;
	UINT GetBufferSize() const noexcept;

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> index_buffer_;
	UINT buffer_size_;
};
