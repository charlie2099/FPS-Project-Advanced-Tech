#include "Texture.h"
#include "WICTextureLoader.h"

Texture::Texture(Renderer& renderer, const std::wstring& filepath)
{
	DirectX::CreateWICTextureFromFile(renderer.GetDevice(), filepath.c_str(), NULL, &shader_resource_view);
}

void Texture::Bind(Renderer& renderer)
{
	renderer.GetDeviceContext()->PSSetShaderResources(0u, 1u, shader_resource_view.GetAddressOf());
}
