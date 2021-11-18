#include "Collision.h"

bool Collision::CollisionBox(DirectX::XMFLOAT3 camPos, DirectX::XMFLOAT3 cubePos)
{
	//check the X axis
	if (abs(camPos.x - cubePos.x) < camSize_.x + cubeSize_.x)
	{
		//check the Y axis
		if (abs(camPos.y - cubePos.y) < camSize_.y + cubeSize_.y)
		{
			//check the Z axis
			if (abs(camPos.z - cubePos.z) < camSize_.z + cubeSize_.z)
			{
				return true;
			}
		}
	}

	return false;

	/*if(pos.x + width >= cubePos.x - x_size && pos.x - width <= cubePos.x + x_size) &&
		(pos.y + height >= cubePos.y - y_size && pos.y - height <= cubePos.y + y_size) &&
		(pos.z + depth >= cubePos.z - z_size && pos.z - depth <= cubePos.z + z_size);
	{
		return true;
	}*/

	//return false;
}
