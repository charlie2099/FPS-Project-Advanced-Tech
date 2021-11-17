#pragma once
#include "Renderer.h"

class TextureSampler
{
public:
	TextureSampler(Renderer& renderer);
	void Bind(Renderer& renderer);

private:
	Microsoft::WRL::ComPtr<ID3D11SamplerState> sampler;
};

