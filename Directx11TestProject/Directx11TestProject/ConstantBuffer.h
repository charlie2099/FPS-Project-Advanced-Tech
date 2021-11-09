#pragma once
#include "Bindable.h"

template<typename C>
class ConstantBuffer : public Bindable
{
public:
	void Update(Renderer& renderer, const C& consts)
	{

		D3D11_MAPPED_SUBRESOURCE msr;
		GetDeviceContext(renderer)->Map(
			pConstantBuffer.Get(), 0u,
			D3D11_MAP_WRITE_DISCARD, 0u,
			&msr
		);
		memcpy(msr.pData, &consts, sizeof(consts));
		GetDeviceContext(renderer)->Unmap(pConstantBuffer.Get(), 0u);
	}

	ConstantBuffer(Renderer& renderer, const C& consts)
	{
		D3D11_BUFFER_DESC cbd;
		cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbd.Usage = D3D11_USAGE_DYNAMIC;
		cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbd.MiscFlags = 0u;
		cbd.ByteWidth = sizeof(consts);
		cbd.StructureByteStride = 0u;

		D3D11_SUBRESOURCE_DATA csd = {};
		csd.pSysMem = &consts;
		GetDevice(renderer)->CreateBuffer(&cbd, &csd, &pConstantBuffer);
	}

	ConstantBuffer(Renderer& renderer)
	{
		D3D11_BUFFER_DESC cbd;
		cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbd.Usage = D3D11_USAGE_DYNAMIC;
		cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbd.MiscFlags = 0u;
		cbd.ByteWidth = sizeof(C);
		cbd.StructureByteStride = 0u;
		GetDevice(renderer)->CreateBuffer(&cbd, nullptr, &pConstantBuffer);
	}
protected:
	Microsoft::WRL::ComPtr<ID3D11Buffer> pConstantBuffer;
};

template<typename C>
class VertexConstantBuffer : public ConstantBuffer<C>
{
	using ConstantBuffer<C>::pConstantBuffer;
	using Bindable::GetDeviceContext;
public:
	using ConstantBuffer<C>::ConstantBuffer;
	void Bind(Renderer& renderer) noexcept override
	{
		GetDeviceContext(renderer)->VSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf());
	}
};

template<typename C>
class PixelConstantBuffer : public ConstantBuffer<C>
{
	using ConstantBuffer<C>::pConstantBuffer;
	using Bindable::GetDeviceContext;
public:
	using ConstantBuffer<C>::ConstantBuffer;
	void Bind(Renderer& renderer) noexcept override
	{
		GetDeviceContext(renderer)->PSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf());
	}
};