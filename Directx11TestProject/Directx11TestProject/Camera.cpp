#include "Camera.h"

void Camera::init()
{
	//Camera information
	camera_position = XMVectorSet(0.0f, 5.0f, -8.0f, 0.0f);
	camera_target = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	camera_up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	//Set the View matrix
	camera_view = XMMatrixLookAtLH(camera_position, camera_target, camera_up);

	//Set the Projection matrix
	camera_projection = XMMatrixPerspectiveFovLH(0.4f * 3.14f, 800 / 600, 1.0f, 1000.0f);
}

void Camera::update()
{
	camera_rotation_matrix = XMMatrixRotationRollPitchYaw(camera_pitch, camera_yaw, 0);
	camera_target = XMVector3TransformCoord(default_forward, camera_rotation_matrix);
	camera_target = XMVector3Normalize(camera_target);

	XMMATRIX RotateYTempMatrix;
	RotateYTempMatrix = XMMatrixRotationY(camera_yaw);

	camera_right = XMVector3TransformCoord(default_right, RotateYTempMatrix);
	camera_up = XMVector3TransformCoord(camera_up, RotateYTempMatrix);
	camera_forward = XMVector3TransformCoord(default_forward, RotateYTempMatrix);

	camera_position += move_left_right * camera_right;
	camera_position += move_back_forward * camera_forward;

	move_left_right = 0.0f;
	move_back_forward = 0.0f;

	camera_target = camera_position + camera_target;

	camera_view = XMMatrixLookAtLH(camera_position, camera_target, camera_up);
}

void Camera::translate()
{

}

void Camera::rotate()
{

}
