#include "Topology.h"

Topology::Topology(Renderer& renderer, D3D11_PRIMITIVE_TOPOLOGY type)
{
	topology_type = type;
}

void Topology::Bind(Renderer& renderer)
{
	renderer.GetDeviceContext()->IASetPrimitiveTopology(topology_type);
}
