#pragma once
#include "Renderer.h"
using namespace DirectX;

class Camera
{
public:
	Camera(Renderer& renderer);

	void Translate();
	void Rotate();
	//void Update();

	// Setters
	void SetView(XMFLOAT3 pos, float rot = 0.0f);
	void SetPosition(XMFLOAT3 pos);
	void SetRotation(float rot);

	// Getters
	XMMATRIX GetView() { return view_; };
	XMFLOAT3 GetPosition() { return position_; };
	float GetRotation() { return rotation_; };

private:
	Renderer* renderer_ = nullptr;
	XMMATRIX  view_;
	XMFLOAT3  position_ { 0.0f, 0.0f, 0.0f };
	float     rotation_ = 0.0f;
};