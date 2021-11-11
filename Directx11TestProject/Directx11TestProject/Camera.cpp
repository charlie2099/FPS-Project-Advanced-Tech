#include "Camera.h"
#include "MathCode.h"
#include <chrono>

namespace dx = DirectX;

Camera::Camera() noexcept
{
	Reset();
}

DirectX::XMMATRIX Camera::GetMatrix() const noexcept
{
	using namespace dx;

	const dx::XMVECTOR forwardBaseVector = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	// apply the camera rotations to a base vector
	const auto lookVector = XMVector3Transform(forwardBaseVector,
		XMMatrixRotationRollPitchYaw(pitch, yaw, 0.0f)
	);
	// generate camera transform (applied to all objects to arrange them relative
	// to camera position/orientation in world) from cam position and direction
	// camera "top" always faces towards +Y (cannot do a barrel roll)
	const auto camPosition = XMLoadFloat3(&pos);
	const auto camTarget = camPosition + lookVector;
	return XMMatrixLookAtLH(camPosition, camTarget, XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
}

void Camera::Reset() noexcept
{
	pos = { 0.0f,0.0f,0.0f }; // 0.0f,0.0f,-18.0f
	pitch = 0.0f; //0.0f //-1.5
	yaw = 0.0f; //0.0f
}

void Camera::Rotate(float dx, float dy) noexcept
{
	yaw = wrap_angle(yaw + dx * rotationSpeed);
	pitch = std::clamp(pitch + dy * rotationSpeed, 0.995f * -PI / 2.0f, 0.995f * PI / 2.0f);
}

void Camera::Translate(DirectX::XMFLOAT3 translation) noexcept
{
	dx::XMStoreFloat3(&translation, dx::XMVector3Transform(
		dx::XMLoadFloat3(&translation),
		dx::XMMatrixRotationRollPitchYaw(pitch, yaw, 0.0f) *
		dx::XMMatrixScaling(travelSpeed, travelSpeed, travelSpeed)
	));
	pos = {
		pos.x + translation.x,
		pos.y + translation.y,
		pos.z + translation.z
	};
}






//void Camera::init()
//{
//	//Camera information
//	camera_position = XMVectorSet(0.0f, 5.0f, -8.0f, 0.0f);
//	camera_target = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
//	camera_up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
//
//	//Set the View matrix
//	camera_view = XMMatrixLookAtLH(camera_position, camera_target, camera_up);
//
//	//Set the Projection matrix
//	camera_projection = XMMatrixPerspectiveFovLH(0.4f * 3.14f, 800 / 600, 1.0f, 1000.0f);
//}
//
//void Camera::update()
//{
//	camera_rotation_matrix = XMMatrixRotationRollPitchYaw(camera_pitch, camera_yaw, 0);
//	camera_target = XMVector3TransformCoord(default_forward, camera_rotation_matrix);
//	camera_target = XMVector3Normalize(camera_target);
//
//	XMMATRIX RotateYTempMatrix;
//	RotateYTempMatrix = XMMatrixRotationY(camera_yaw);
//
//	camera_right = XMVector3TransformCoord(default_right, RotateYTempMatrix);
//	camera_up = XMVector3TransformCoord(camera_up, RotateYTempMatrix);
//	camera_forward = XMVector3TransformCoord(default_forward, RotateYTempMatrix);
//
//	camera_position += move_left_right * camera_right;
//	camera_position += move_back_forward * camera_forward;
//
//	move_left_right = 0.0f;
//	move_back_forward = 0.0f;
//
//	camera_target = camera_position + camera_target;
//
//	camera_view = XMMatrixLookAtLH(camera_position, camera_target, camera_up);
//}
//
//void Camera::translate()
//{
//
//}
//
//void Camera::rotate()
//{
//
//}
