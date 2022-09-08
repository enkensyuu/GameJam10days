#pragma once
#include "DxLib.h"
#include "math.h"

#include "Player.h"
class PlayerBullet
{
public:
	///<summary>
	///‰Šú‰»
	///</summary>
	void Initialize();

	///<summary>
	///XV
	///</summary>
	void Update(char* keys, char* oldkeys);

	///<summary>
	///•`‰æ
	///</summary>
	void Draw();


private:

	float radius = 10.0f;
	float Bullet_X = 100.0f;
	float Bullet_Y = 1000.0f;

	float move = 10;
};