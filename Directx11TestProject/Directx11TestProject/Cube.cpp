#include "Cube.h"

Cube::Cube(Renderer& renderer, DirectX::XMFLOAT3 size, DirectX::XMFLOAT3 pos) : transform(DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z))
{
    renderer_ = &renderer;

    /*pixel_shader = std::make_unique<PixelShader>(renderer);
    input_layout = std::make_unique<InputLayout>(renderer, L"VertexShader.cso", std::vector<D3D11_INPUT_ELEMENT_DESC>
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    });*/

    pixel_shader = std::make_unique<PixelShader>(renderer, L"PixelShader.cso");
    vertex_shader = std::make_unique<VertexShader>(renderer, L"VertexShader.cso");

    vertex_buffer = std::make_unique<VertexBuffer>(renderer, std::vector<Vertex>
    {
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

void Cube::Render(Renderer& renderer)
{
    pixel_shader->Bind(renderer);
    vertex_shader->Bind(renderer);
    vertex_buffer->Bind(renderer);
    index_buffer->Bind(renderer);
    texture->Bind(renderer);
    texture_sampler->Bind(renderer);

    renderer.SetModelMatrix(transform);
    renderer.GetContext()->DrawIndexed(index_buffer->GetIndexCount(), 0u, 0u);
}

void Cube::SetPos(DirectX::XMFLOAT3 pos)
{
    transform = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
    renderer_->SetModelMatrix(transform);
    pos_ = pos;
}
