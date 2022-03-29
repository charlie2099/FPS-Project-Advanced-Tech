#include "Cube.h"

Cube::Cube(Renderer& renderer, DirectX::XMFLOAT3 size, DirectX::XMFLOAT3 pos, float rot)
{
    size_ = size;
    position_ = pos;
    rotation_ = rot;
    renderer_ = &renderer;
    transform_ = DirectX::XMMatrixRotationY(-rot) * DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);

    pixel_shader = std::make_unique<PixelShader>(renderer, L"PixelShader.cso");
    vertex_shader = std::make_unique<VertexShader>(renderer, L"VertexShader.cso");

    vertex_buffer = std::make_unique<VertexBuffer>(renderer, std::vector<Vertex>
    {                             //UV mapping
        /*{-size.x, -size.y, -size.z, 1.0f, 0.0f },
        { size.x, -size.y, -size.z, 1.0f, 1.0f },
        {-size.x,  size.y, -size.z, 0.0f, 1.0f },
        { size.x,  size.y, -size.z, 1.0f, 0.0f },

        {-size.x, -size.y,  size.z, 0.0f, 0.0f },
        { size.x, -size.y,  size.z, 1.0f, 0.0f },
        {-size.x,  size.y,  size.z, 0.0f, 1.0f },
        { size.x,  size.y,  size.z, 1.0f, 0.0f },*/


        { -size.x, -size.y, -size.z, 0.0F, 0.0F },
        { +size.x, -size.y, -size.z, 1.0F, 0.0F },
        { -size.x, -size.y, +size.z, 0.0F, 1.0F },
        { +size.x, -size.y, +size.z, 1.0F, 1.0F },
        { -size.x, +size.y, -size.z, 0.0F, 0.0F },
        { +size.x, +size.y, -size.z, 1.0F, 0.0F },
        { -size.x, +size.y, +size.z, 0.0F, 1.0F },
        { +size.x, +size.y, +size.z, 1.0F, 1.0F },
        { -size.x, -size.y, +size.z, 0.0F, 1.0F },
        { +size.x, -size.y, +size.z, 1.0F, 1.0F },
        { -size.x, +size.y, +size.z, 0.0F, 0.0F },
        { +size.x, +size.y, +size.z, 1.0F, 0.0F },
        { -size.x, -size.y, -size.z, 1.0F, 1.0F },
        { +size.x, -size.y, -size.z, 0.0F, 1.0F },
        { -size.x, +size.y, -size.z, 1.0F, 0.0F },
        { +size.x, +size.y, -size.z, 0.0F, 0.0F },
        { -size.x, -size.y, +size.z, 1.0F, 1.0F },
        { -size.x, +size.y, +size.z, 1.0F, 0.0F },
        { -size.x, -size.y, -size.z, 0.0F, 1.0F },
        { -size.x, +size.y, -size.z, 0.0F, 0.0F },
        { +size.x, -size.y, +size.z, 0.0F, 1.0F },
        { +size.x, +size.y, +size.z, 0.0F, 0.0F },
        { +size.x, -size.y, -size.z, 1.0F, 1.0F },
        { +size.x, +size.y, -size.z, 1.0F, 0.0F },
    });

    index_buffer = std::make_unique<IndexBuffer>(renderer, std::vector<unsigned short>
    {
        /*0,2,1,2,3,1,
        1,3,5,3,7,5,
        2,6,3,3,6,7,
        4,5,7,4,7,6,
        0,4,2,2,4,6,
        0,1,4,1,5,4*/

        0, 2, 1, 2, 3, 1,
        4, 5, 6, 6, 5, 7,
        8, 10, 9, 9, 10, 11,
        12, 13, 14, 13, 15, 14,
        16, 18, 17, 17, 18, 19,
        20, 21, 22, 22, 21, 23
    });

    texture = std::make_unique<Texture>(renderer, L"wall.jpg");
    texture_sampler = std::make_unique<TextureSampler>(renderer);
}

Cube::Cube(Renderer& renderer, const std::wstring& filepath, DirectX::XMFLOAT3 size, DirectX::XMFLOAT3 pos, float rot)
{
    size_ = size;
    position_ = pos;
    rotation_ = rot;
    renderer_ = &renderer;
    transform_ = DirectX::XMMatrixRotationY(-rot) * DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);

    pixel_shader = std::make_unique<PixelShader>(renderer, L"PixelShader.cso");
    vertex_shader = std::make_unique<VertexShader>(renderer, L"VertexShader.cso");

    vertex_buffer = std::make_unique<VertexBuffer>(renderer, std::vector<Vertex>
    {                             //UV mapping
        /*{-size.x, -size.y, -size.z, 1.0f, 0.0f },
        { size.x, -size.y, -size.z, 1.0f, 1.0f },
        {-size.x,  size.y, -size.z, 0.0f, 1.0f },
        { size.x,  size.y, -size.z, 1.0f, 0.0f },

        {-size.x, -size.y,  size.z, 0.0f, 0.0f },
        { size.x, -size.y,  size.z, 1.0f, 0.0f },
        {-size.x,  size.y,  size.z, 0.0f, 1.0f },
        { size.x,  size.y,  size.z, 1.0f, 0.0f },*/


        { -size.x, -size.y, -size.z, 0.0F, 0.0F },
        { +size.x, -size.y, -size.z, 1.0F, 0.0F },
        { -size.x, -size.y, +size.z, 0.0F, 1.0F },
        { +size.x, -size.y, +size.z, 1.0F, 1.0F },
        { -size.x, +size.y, -size.z, 0.0F, 0.0F },
        { +size.x, +size.y, -size.z, 1.0F, 0.0F },
        { -size.x, +size.y, +size.z, 0.0F, 1.0F },
        { +size.x, +size.y, +size.z, 1.0F, 1.0F },
        { -size.x, -size.y, +size.z, 0.0F, 1.0F },
        { +size.x, -size.y, +size.z, 1.0F, 1.0F },
        { -size.x, +size.y, +size.z, 0.0F, 0.0F },
        { +size.x, +size.y, +size.z, 1.0F, 0.0F },
        { -size.x, -size.y, -size.z, 1.0F, 1.0F },
        { +size.x, -size.y, -size.z, 0.0F, 1.0F },
        { -size.x, +size.y, -size.z, 1.0F, 0.0F },
        { +size.x, +size.y, -size.z, 0.0F, 0.0F },
        { -size.x, -size.y, +size.z, 1.0F, 1.0F },
        { -size.x, +size.y, +size.z, 1.0F, 0.0F },
        { -size.x, -size.y, -size.z, 0.0F, 1.0F },
        { -size.x, +size.y, -size.z, 0.0F, 0.0F },
        { +size.x, -size.y, +size.z, 0.0F, 1.0F },
        { +size.x, +size.y, +size.z, 0.0F, 0.0F },
        { +size.x, -size.y, -size.z, 1.0F, 1.0F },
        { +size.x, +size.y, -size.z, 1.0F, 0.0F },
    });

    index_buffer = std::make_unique<IndexBuffer>(renderer, std::vector<unsigned short>
    {
        /*0,2,1,2,3,1,
        1,3,5,3,7,5,
        2,6,3,3,6,7,
        4,5,7,4,7,6,
        0,4,2,2,4,6,
        0,1,4,1,5,4*/

        0, 2, 1, 2, 3, 1,
        4, 5, 6, 6, 5, 7,
        8, 10, 9, 9, 10, 11,
        12, 13, 14, 13, 15, 14,
        16, 18, 17, 17, 18, 19,
        20, 21, 22, 22, 21, 23
    });
    
    texture = std::make_unique<Texture>(renderer, filepath.c_str());
    texture_sampler = std::make_unique<TextureSampler>(renderer);
}

void Cube::Render(Renderer& renderer)
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

void Cube::Destroy()
{
    _destroyed = true;
}

void Cube::SetPos(DirectX::XMFLOAT3 pos)
{
    position_ = pos;
    transform_ = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
    renderer_->SetModelMatrix(transform_);
}

void Cube::SetRotation(float rot)
{
    rotation_ = rot;
    transform_ = DirectX::XMMatrixRotationY(-rot) * DirectX::XMMatrixTranslation(position_.x, position_.y, position_.z);
    renderer_->SetModelMatrix(transform_);
}
