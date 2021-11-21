#include "Camera.h"

Camera::Camera(Renderer& renderer)
{
	renderer_ = &renderer;
}

void Camera::Update(Window& window, float deltatime)
{
	//float speed = 2.0f;
	//if (window.keyboard.KeyIsPressed(Keycodes::W)) //FORWARDS TRANSLATION
	//{
	//	position_.z += speed * deltatime;
	//}
	//if (window.keyboard.KeyIsPressed(Keycodes::S)) //BACKWARDS TRANSLATION
	//{
	//	position_.z -= speed * deltatime;
	//}
	//if (window.keyboard.KeyIsPressed(Keycodes::W) && window.keyboard.KeyIsPressed(Keycodes::SHIFT)) //SPRINT
	//{
	//	float multiplier = 1.15f;
	//	position_.z += speed * multiplier * deltatime;
	//}

	//if (window.keyboard.KeyIsPressed(Keycodes::A)) //LEFT ROTATION
	//{
	//	rotation_ -= speed * deltatime;
	//}
	//if (window.keyboard.KeyIsPressed(Keycodes::D)) //RIGHT ROTATION
	//{
	//	rotation_ += speed * deltatime;
	//}


	//float forwards = static_cast<float>(window.keyboard.KeyIsPressed('W'));
	//float backwards = static_cast<float>(window.keyboard.KeyIsPressed('S'));

	if (window.keyboard.KeyIsPressed(Keycodes::W)) //FORWARDS TRANSLATION
	{

	}

	float forwardsBackwards = static_cast<float>(window.keyboard.KeyIsPressed('W')) - static_cast<float>(window.keyboard.KeyIsPressed('S'));
	float leftRight = static_cast<float>(window.keyboard.KeyIsPressed('A')) - static_cast<float>(window.keyboard.KeyIsPressed('D'));

	float relativeX = leftRight * std::cosf(rotation_) - forwardsBackwards * std::sinf(rotation_);
	float relativeY = leftRight * std::sinf(rotation_) + forwardsBackwards * std::cosf(rotation_);
	float inputCamera = static_cast<float>(window.keyboard.KeyIsPressed('E')) - static_cast<float>(window.keyboard.KeyIsPressed('Q'));

	float speed = 2.0f;
	position_.x += relativeX * speed * deltatime;
	position_.z += relativeY * speed * deltatime;
	rotation_ += inputCamera * speed/2.0f * deltatime;

	DirectX::XMMATRIX view = DirectX::XMMatrixIdentity();
	view *= DirectX::XMMatrixTranslation(position_.x, position_.y, position_.z) * DirectX::XMMatrixRotationY(rotation_);
	renderer_->SetViewMatrix(view);
}


//void Camera::Translate(XMFLOAT3 pos)
//{
//	position_ = pos;
//	view_ *= XMMatrixTranslation(pos.x, pos.y, pos.z);
//	renderer_->SetViewMatrix(view_);
//}
//
//void Camera::Rotate(float rot)
//{
//	rotation_ = rot;
//	view_ *= XMMatrixRotationY(rot);
//	renderer_->SetViewMatrix(view_);
//}

void Camera::SetView(XMFLOAT3 pos, float rot)
{
	position_ = pos;
	rotation_ = rot;
	DirectX::XMMATRIX view = XMMatrixTranslation(pos.x, pos.y, pos.z) * XMMatrixRotationY(rot);
	renderer_->SetViewMatrix(view);
}