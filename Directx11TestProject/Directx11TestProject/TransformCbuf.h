#pragma once
#include "ConstantBuffer.h"
#include "Drawable.h"
#include <DirectXMath.h>

class TransformCbuf : public Bindable
{
public:
	TransformCbuf(Renderer& renderer, const Drawable& parent);
	void Bind(Renderer& renderer) noexcept override;

private:
	static std::unique_ptr<VertexConstantBuffer<DirectX::XMMATRIX>> pVcbuf;
	const Drawable& parent;
};