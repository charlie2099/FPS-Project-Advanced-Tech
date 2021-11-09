#include "TransformCbuf.h"

TransformCbuf::TransformCbuf(Renderer& renderer, const Drawable& parent)
	:
	parent(parent)
{
	if (!pVcbuf)
	{
		pVcbuf = std::make_unique<VertexConstantBuffer<DirectX::XMMATRIX>>(renderer);
	}
}

void TransformCbuf::Bind(Renderer& renderer) noexcept
{
	pVcbuf->Update(renderer,
		DirectX::XMMatrixTranspose(
			parent.GetTransformXM() * renderer.GetProjection()
		)
	);
	pVcbuf->Bind(renderer);
}

std::unique_ptr<VertexConstantBuffer<DirectX::XMMATRIX>> TransformCbuf::pVcbuf;