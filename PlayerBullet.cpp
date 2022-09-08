#include "PlayerBullet.h"

void PlayerBullet::Initialize()
{
	Bullet_X = 100.0f;
	Bullet_Y = 1000.0f;
}

void PlayerBullet::Update(char* keys, char* oldkeys)
{
	Bullet_X += move;
}

void PlayerBullet::Draw()
{
	DrawCircle(Bullet_X, Bullet_Y, radius, GetColor(255, 255, 0), true);
}