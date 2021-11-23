#pragma once
#include "Cube.h"

class Projectile
{
public:
	Projectile(Renderer& renderer, const std::wstring& filepath, DirectX::XMFLOAT3 size, DirectX::XMFLOAT3 pos, float rot = 0);
	
	void Update(float dt);
	void Render(Renderer& renderer);
	
	void Move(bool moving);
	bool isMoving() { return moving_; };

	void Destroy();
	bool IsDestroyed() { return destroyed_; };

	std::unique_ptr<Cube>& GetCube() { return projectile; };

private:
	std::unique_ptr<Cube> projectile;
	bool moving_ = false;
	bool destroyed_ = false;
};
