#pragma once
#include "Renderer.h"

class Topology
{
public:
	Topology(Renderer& renderer, D3D11_PRIMITIVE_TOPOLOGY type);
	void Bind(Renderer& renderer);

private:
	D3D11_PRIMITIVE_TOPOLOGY topology_type;
};
