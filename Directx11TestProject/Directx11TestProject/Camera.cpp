#include "Camera.h"

Camera::Camera(Renderer& renderer)
{
	renderer_ = &renderer;
}

void Camera::Update(Window& window, float deltatime)
{
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

bool Camera::CollidesWith(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 size)
{
	//abs returns the absolute value
	//check the X axis
	if (abs(pos.x - position_.x) < size.x + 1.0f)
	{
		//check the Y axis
		if (abs(pos.y - position_.y) < size.y + 1.0f)
		{
			//check the Z axis
			if (abs(pos.z - position_.z) < size.z + 1.0f)
			{
				return true;
			}
		}
	}
	return false;
}

bool Camera::CollidesWith(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT2 size)
{
	//abs returns the absolute value
	//check the X axis
	if (abs(pos.x - position_.x) < size.x + 1.0f)
	{
		//check the Y axis
		if (abs(pos.y - position_.y) < size.y + 1.0f)
		{
			//check the Z axis
			if (abs(pos.z - position_.z) < 0.25f + 1.0f)
			{
				return true;
			}
		}
	}
	return false;
}