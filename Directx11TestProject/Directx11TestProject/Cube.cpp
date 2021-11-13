#include "Cube.h"
#include <sstream>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

Cube::Cube(Renderer& renderer, float angle, float x, float y, float z)
{
	struct Vertex
	{
		struct
		{
			float x;
			float y;
			float z;
		} pos;
	};

	const Vertex vertices[] =
		//const /*std::vector<*/Vertex/*>*/ vertices[] =
		//const std::vector<Vertex> vertices =
	{
		{-1.0, -1.0f, -1.0f },
		{1.0f, -1.0f, -1.0f},
		{-1.0f, 1.0f, -1.0f},
		{1.0f, 1.0f, -1.0f},
		{-1.0f, -1.0f, 1.0f},
		{1.0f, -1.0f, 1.0f},
		{-1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f},
	};

	//vertex_buffer.Init(renderer.GetDevice().Get(), vertices, 0u);
	//vertex_buffer.Bind(renderer.GetContext().Get(), 0u, 1u);

	D3D11_BUFFER_DESC bd = {};
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.CPUAccessFlags = 0u;
	bd.MiscFlags = 0u;
	bd.ByteWidth = sizeof(Vertex) * ARRAYSIZE(vertices);
	bd.StructureByteStride = sizeof(Vertex);
	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem = vertices/*.data()*/;
	renderer.GetDevice()->CreateBuffer(&bd, &sd, &vertex_buffer_old);
	stride = sizeof(Vertex);
	offset = 0u;


	// index buffer
	const std::vector<unsigned short> indices =
	{
		0,2,1, 2,3,1,
		1,3,5, 3,7,5,
		2,6,3, 3,6,7,
		4,5,7, 4,7,6,
		0,4,2, 2,4,6,
		0,1,4, 1,5,4
	};

	index_buffer.Init(renderer.GetDevice(), indices);


	// constant buffer for transformation matrix
	struct ConstantBuffer
	{
		dx::XMMATRIX transform;
	};

	const ConstantBuffer const_buffer =
	{
		{
			dx::XMMatrixTranspose(
				dx::XMMatrixRotationZ(angle) *
				dx::XMMatrixRotationX(angle) *
				dx::XMMatrixTranslation(x, y, z + 4.0f) *
				renderer.GetCamera() * renderer.GetProjection() *
				dx::XMMatrixPerspectiveLH(1.0f, 1.0f, 0.5f, 60.0f) // 10
			)
		}
	};

	constant_buffer.Init(renderer.GetDevice(), const_buffer.transform);
	renderer.SetTransformMatrix(const_buffer.transform);


	struct ConstantBuffer2
	{
		struct
		{
			float r;
			float g;
			float b;
			float a;
		} face_colours[6];
	};
	struct ConstantBuffer2 cb2 =
	{
		{
			{0.0f, 0.5f, 1.0f},
			{0.2f, 0.2f, 0.7f},
			{0.1f, 0.8f, 0.5f},
			{0.5f, 1.0f, 0.2f},
			{0.4f, 0.3f, 0.8f},
			{0.8f, 0.9f, 0.3f},
		}
	};

	D3D11_BUFFER_DESC cbd2;
	cbd2.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd2.Usage = D3D11_USAGE_DYNAMIC;
	cbd2.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd2.MiscFlags = 0u;
	cbd2.ByteWidth = sizeof(cb2);
	cbd2.StructureByteStride = 0u;

	D3D11_SUBRESOURCE_DATA csd2 = {};
	csd2.pSysMem = &cb2;
	renderer.GetDevice()->CreateBuffer(&cbd2, &csd2, &constant_buffer2);


	pixel_shader.Create(renderer.GetDevice());

	vertex_shader.Create(renderer.GetDevice());

	// input (vertex) layout (2d position only)
	const D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	renderer.GetDevice()->CreateInputLayout(
		ied, (UINT)std::size(ied),
		vertex_shader.GetBlob()->GetBufferPointer(),
		vertex_shader.GetBlob()->GetBufferSize(),
		&input_layout
	);


	Binds(renderer);
	renderer.GetContext()->DrawIndexed(index_buffer.GetBufferSize(), 0u, 0u);
}

void Cube::Update() {}

void Cube::Render(Renderer& renderer)
{
	// Transformation matrix here??

	Binds(renderer);
	renderer.GetContext()->DrawIndexed(index_buffer.GetBufferSize(), 0u, 0u);
}

/// PRIVATE FUNCTIONS
void Cube::Binds(Renderer& renderer)
{
	renderer.GetContext()->IASetVertexBuffers(0u, 1u, vertex_buffer_old.GetAddressOf(), &stride, &offset);

	index_buffer.Bind(renderer.GetContext(), 0u);

	constant_buffer.Bind(renderer.GetContext());

	renderer.GetContext()->PSSetConstantBuffers(0u, 1u, constant_buffer2.GetAddressOf());

	pixel_shader.Bind(renderer.GetContext());

	vertex_shader.Bind(renderer.GetContext());
	//renderer.GetContext()->VSSetShader(vertex_shader.Get(), nullptr, 0u);

	renderer.GetContext()->IASetInputLayout(input_layout.Get());

	renderer.GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

