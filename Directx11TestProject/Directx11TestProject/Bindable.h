#pragma once
#include "Renderer.h"
#include <string>
#include <d3dcompiler.h>

class Bindable
{
public:
	virtual void Bind(Renderer& renderer) noexcept = 0;
	virtual ~Bindable() = default;

protected:
	static ID3D11DeviceContext* GetDeviceContext(Renderer& renderer) noexcept;
	static ID3D11Device* GetDevice(Renderer& renderer) noexcept;
};