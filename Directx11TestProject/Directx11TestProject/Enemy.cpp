#include "Enemy.h"

Enemy::Enemy(Renderer& renderer, DirectX::XMFLOAT2 size, DirectX::XMFLOAT3 pos) : transform(DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z))
{
    pixel_shader = std::make_unique<PixelShader>(renderer, L"PixelShader.cso");

    vertex_shader = std::make_unique<VertexShader>(renderer, L"VertexShader.cso",
        std::vector<D3D11_INPUT_ELEMENT_DESC>{
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
            { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    });

    vertex_buffer = std::make_unique<VertexBuffer>(renderer, std::vector<Vertex>
    {
        { -size.x, -size.y, 0.0F, 0.0F, 1.0F },
        { -size.x, +size.y, 0.0F,  0.0F, 0.0F },
        { +size.x, -size.y, 0.0F,  1.0F, 1.0F },
        { +size.x, +size.y, 0.0F,  1.0F, 0.0F },
    });

    index_buffer = std::make_unique<IndexBuffer>(renderer, std::vector<unsigned short>{
        0, 1, 2, 2, 1, 3,
    });

    texture = std::make_unique<Texture>(renderer, L"wolfenstein_head.jpg");
    texture_sampler = std::make_unique<TextureSampler>(renderer);
}

void Enemy::Draw(Renderer& renderer)
{
    pixel_shader->Bind(renderer);
    vertex_shader->Bind(renderer);
    vertex_buffer->Bind(renderer);
    index_buffer->Bind(renderer);
    texture->Bind(renderer);
    texture_sampler->Bind(renderer);

    renderer.SetModelMatrix(transform);
    renderer.GetContext()->DrawIndexed(36U, 0U, 0U);
}