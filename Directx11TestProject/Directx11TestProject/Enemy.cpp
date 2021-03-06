#include "Enemy.h"

int Enemy::enemy_count = 0;

Enemy::Enemy(Renderer& renderer, DirectX::XMFLOAT2 size, DirectX::XMFLOAT3 pos, float rot)
{
    enemy_count += 1;
    size_ = size;
    position_ = pos;
    rotation_ = rot;
    renderer_ = &renderer;
    transform_ = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z) * DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(rot));

    pixel_shader = std::make_unique<PixelShader>(renderer, L"PixelShader.cso");
    vertex_shader = std::make_unique<VertexShader>(renderer, L"VertexShader.cso");

    vertex_buffer = std::make_unique<VertexBuffer>(renderer, std::vector<Vertex>
    {
        { -size.x, -size.y, 0.0F,  0.0F, 1.0F },
        { -size.x, +size.y, 0.0F,  0.0F, 0.0F },
        { +size.x, -size.y, 0.0F,  1.0F, 1.0F },
        { +size.x, +size.y, 0.0F,  1.0F, 0.0F },
    });

    index_buffer = std::make_unique<IndexBuffer>(renderer, std::vector<unsigned short>
    {
        0, 1, 2, 2, 1, 3,
    });

    texture = std::make_unique<Texture>(renderer, L"wolfenstein_head.jpg");
    texture_sampler = std::make_unique<TextureSampler>(renderer);
}

void Enemy::Render(Renderer& renderer)
{
    pixel_shader->Bind(renderer);
    vertex_shader->Bind(renderer);
    vertex_buffer->Bind(renderer);
    index_buffer->Bind(renderer);
    texture->Bind(renderer);
    texture_sampler->Bind(renderer);

    renderer.SetModelMatrix(transform_);
    renderer.GetDeviceContext()->DrawIndexed(index_buffer->GetIndexCount(), 0u, 0u);
}

void Enemy::Destroy()
{
    destroyed_ = true;
}

void Enemy::SetPos(DirectX::XMFLOAT3 pos)
{
    position_ = pos;
    transform_ = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
    renderer_->SetModelMatrix(transform_);
}

void Enemy::SetRotation(float rot)
{
    rotation_ = rot;
    transform_ = DirectX::XMMatrixRotationY(-rot) * DirectX::XMMatrixTranslation(position_.x, position_.y, position_.z);
    renderer_->SetModelMatrix(transform_);
}

