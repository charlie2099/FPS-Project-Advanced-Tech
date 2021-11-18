#pragma once
#include <DirectXMath.h>
#include <cmath>

class Collision
{
public:
	Collision() = default;

    bool CollisionBox(DirectX::XMFLOAT3 camPos, DirectX::XMFLOAT3 cubePos); // bounds1  bounds2

	// Setters
	void SetBounds(DirectX::XMFLOAT3 bounds)
	{
		bounds_ = bounds;
	};

	// Getters
	DirectX::XMFLOAT3 GetBounds() { return bounds_; };

private:
	DirectX::XMFLOAT3 bounds_;
	DirectX::XMFLOAT3 camSize_  { 1.0f, 1.0f, 1.0f };
	DirectX::XMFLOAT3 cubeSize_ { 1.0f, 1.0f, 1.0f };
};