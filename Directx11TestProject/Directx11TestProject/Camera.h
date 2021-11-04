#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>
using namespace DirectX;

class Camera
{
public:
	Camera() = default;
	~Camera() = default;

	void init();
	void update();
	void translate();
	void rotate();

private:
    XMMATRIX camera_view;
	XMMATRIX camera_projection;
	XMMATRIX camera_rotation_matrix;
	XMMATRIX rotation;
	XMMATRIX scale;
	XMMATRIX translation;

	XMVECTOR camera_position;
	XMVECTOR camera_target;
	XMVECTOR camera_up;

	XMVECTOR default_forward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	XMVECTOR default_right = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR camera_forward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	XMVECTOR camera_right = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

	float move_left_right = 0.0f;
	float move_back_forward = 0.0f;
	float camera_yaw = 0.0f;
	float camera_pitch = 0.0f;
};