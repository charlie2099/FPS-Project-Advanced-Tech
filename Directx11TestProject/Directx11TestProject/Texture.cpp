#include "Texture.h"
#include "TextureLoader.h"
Texture::Texture(Renderer& renderer, const std::wstring& filepath)
{
	auto result = DirectX::CreateWICTextureFromFile(renderer.GetDevice(), filepath.c_str(), NULL, &shaderResourceView);
	assert(SUCCEEDED(result));

}

void Texture::Bind(Renderer& renderer)
{
	renderer.GetContext()->PSSetShaderResources
	(
		0U,
		1U,
		shaderResourceView.GetAddressOf()
	);
}