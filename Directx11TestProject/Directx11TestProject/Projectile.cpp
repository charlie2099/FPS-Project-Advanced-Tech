#include "Projectile.h"

Projectile::Projectile(Renderer& renderer, const std::wstring& filepath, DirectX::XMFLOAT3 size, DirectX::XMFLOAT3 pos, float rot)
{
	projectile = std::make_unique<Cube>(renderer, filepath, size, pos, rot);
}

void Projectile::Update(float dt)
{
	const float speed = 5.0f;
	projectile->SetPos({ projectile->GetPos().x + (float)sin(projectile->GetRot()) * speed * dt,
						 projectile->GetPos().y,
						 projectile->GetPos().z - (float)cos(projectile->GetRot()) * speed * dt });
	//bullets[i]->SetRotation(camera->GetRotation());
}

void Projectile::Render(Renderer& renderer)
{
	projectile->Render(renderer);
}

void Projectile::Move(bool moving)
{
	moving_ = moving;
}

void Projectile::Destroy()
{
	_destroyed = true;
}

bool Projectile::CollidesWith(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 size)
{
	//check the X axis
	if (abs(pos.x - projectile->GetPos().x) < size.x + projectile->GetSize().x)
	{
		//check the Y axis
		if (abs(pos.y - projectile->GetPos().y) < size.y + projectile->GetSize().y)
		{
			//check the Z axis
			if (abs(pos.z - projectile->GetPos().z) < size.z + projectile->GetSize().z)
			{
				return true;
			}
		}
	}
	return false;
}

bool Projectile::CollidesWith(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT2 size)
{
	//check the X axis
	if (abs(pos.x - projectile->GetPos().x) < size.x + projectile->GetSize().x)
	{
		//check the Y axis
		if (abs(pos.y - projectile->GetPos().y) < size.y + projectile->GetSize().y)
		{
			//check the Z axis
			if (abs(pos.z - projectile->GetPos().z) < 0.25f + projectile->GetSize().z)
			{
				return true;
			}
		}
	}
	return false;
}
