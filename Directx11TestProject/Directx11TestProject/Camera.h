#pragma once
#include "Renderer.h"
#include "Window.h"
#include "Keycodes.h"
#include "Timer.h"
using namespace DirectX;

class Camera
{
public:
	Camera(Renderer& renderer);

	//void Translate(XMFLOAT3 pos);
	//void Rotate(float rot);
	void Update(Window& window, float deltatime/*Timer timer*/);

	void SetView(XMFLOAT3 pos, float rot = 0.0f);

	XMFLOAT3 GetPosition() { return position_; };
	float GetRotation() { return rotation_; };

	bool CollidesWith(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 size);
	bool CollidesWith(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT2 size);

private:
	Renderer* renderer_ = nullptr;
	XMFLOAT3  position_ { 0.0f, 0.0f, 0.0f };
	float     rotation_ = 0.0f;
};