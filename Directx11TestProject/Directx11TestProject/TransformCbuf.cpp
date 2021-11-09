#include "TransformCbuf.h"

TransformCbuf::TransformCbuf(Renderer& renderer, const Drawable& parent)
	:
	vcbuf(renderer),
	parent(parent)
{}

void TransformCbuf::Bind(Renderer& renderer) noexcept
{
	vcbuf.Update(renderer,
		DirectX::XMMatrixTranspose(
			parent.GetTransformXM() * renderer.GetProjection()
		)
	);
	vcbuf.Bind(renderer);
}