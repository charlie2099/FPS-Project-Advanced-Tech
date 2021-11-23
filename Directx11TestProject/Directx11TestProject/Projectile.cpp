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
	if (!destroyed_)
	{
		projectile->Render(renderer);
	}
}

void Projectile::Move(bool moving)
{
	moving_ = moving;
}

void Projectile::Destroy()
{
	destroyed_ = true;
}
