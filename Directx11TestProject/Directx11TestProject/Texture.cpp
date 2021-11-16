#include "Texture.h"
#include "TextureLoader.h"

Texture::Texture(Renderer& getRenderer, const std::wstring& filepath)
{
	auto result = DirectX::CreateWICTextureFromFile(getRenderer.GetDevice(), filepath.c_str(), NULL, &shader_resource_view);
	assert(SUCCEEDED(result));

}

void Texture::Bind(Renderer& getRenderer)
{
	getRenderer.GetContext()->PSSetShaderResources
	(
		0U,
		1U,
		shader_resource_view.GetAddressOf()
	);
}
