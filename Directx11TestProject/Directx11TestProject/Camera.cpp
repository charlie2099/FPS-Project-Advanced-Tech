#include "Camera.h"

Camera::Camera(Renderer& renderer)
{
	renderer_ = &renderer;
}

//void Camera::Update()
//{
//	auto view_matrix = renderer_->GetViewMatrix();
//	view_matrix *= XMMatrixTranslation(position_.x, position_.y, position_.z) * XMMatrixRotationY(rotation_);
//	renderer_->SetViewMatrix(view_matrix);
//}

void Camera::SetView(XMFLOAT3 pos, float rot)
{
	auto view_matrix = renderer_->GetViewMatrix();
	view_matrix = XMMatrixTranslation(pos.x, pos.y, pos.z) * XMMatrixRotationY(rot);
	renderer_->SetViewMatrix(view_matrix);
	view_ = view_matrix;
	position_ = pos;
	rotation_ = rot;
}

void Camera::SetPosition(XMFLOAT3 pos)
{
	//position_ = pos;


	position_ = pos;
	auto view_matrix = renderer_->GetViewMatrix();
	view_matrix *= XMMatrixTranslation(pos.x, pos.y, pos.z);
	renderer_->SetViewMatrix(view_matrix);
	view_ = view_matrix;
	
}

void Camera::SetRotation(float rot)
{
	auto view_matrix = renderer_->GetViewMatrix();
	view_matrix *= XMMatrixTranslation(0, 0, 0) * XMMatrixRotationY(rot);
	renderer_->SetViewMatrix(view_matrix);
	view_ = view_matrix;
	rotation_ = rot;
}