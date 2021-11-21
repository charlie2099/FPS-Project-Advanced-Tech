#include "Camera.h"

Camera::Camera(Renderer& renderer)
{
	renderer_ = &renderer;
}

void Camera::Update(Window& window, float deltatime)
{
	auto speed = 2.0f;

	if (window.keyboard.KeyIsPressed(Keycodes::W)) //FORWARDS TRANSLATION
	{
		position_.z += speed * deltatime;
		//view_ = XMMatrixTranslation(position_.x, position_.y, position_.z) * XMMatrixRotationY(rotation_);
		//Translate({ 0.0f, 0.0f, speed * deltatime });
	}
	if (window.keyboard.KeyIsPressed(Keycodes::S)) //BACKWARDS TRANSLATION
	{
		position_.z -= speed * deltatime;
		//view_ = XMMatrixTranslation(position_.x, position_.y, position_.z) * XMMatrixRotationY(rotation_);
		//Translate({ 0.0f, 0.0f, -speed * deltatime });
	}
	if (window.keyboard.KeyIsPressed(Keycodes::W) && window.keyboard.KeyIsPressed(Keycodes::SHIFT)) //SPRINT
	{
		position_.z += (speed*1.15f) * deltatime;
		//view_ = XMMatrixTranslation(position_.x, position_.y, position_.z);
		//Translate({ 0, 0, speed * 1.15f * deltatime });
	}
	if (window.keyboard.KeyIsPressed(Keycodes::A)) //LEFT ROTATION
	{
		rotation_ -= speed * deltatime;
		//position_.x += speed * deltatime;
		//view_ = XMMatrixTranslation(position_.x, position_.y, position_.z) * XMMatrixRotationY(rotation_);
		//Rotate(-speed * deltatime);
	}
	if (window.keyboard.KeyIsPressed(Keycodes::D)) //RIGHT ROTATION
	{
		rotation_ += speed * deltatime;
		//position_.x -= speed * deltatime;
		//view_ = XMMatrixTranslation(position_.x, position_.y, position_.z) * XMMatrixRotationY(rotation_);
		//Rotate(speed * deltatime);
	}

	view_ = DirectX::XMMatrixTranslation(position_.x, position_.y, position_.z) * DirectX::XMMatrixRotationY(rotation_);
	//view_ *= DirectX::XMMatrixRotationY(rotation_);
	renderer_->SetViewMatrix(view_);
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
	view_ = XMMatrixTranslation(pos.x, pos.y, pos.z) * XMMatrixRotationY(rot);
	renderer_->SetViewMatrix(view_);
}