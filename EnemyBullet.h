#pragma once
#include "DxLib.h"
#include <math.h>

class EnemyBullet
{
public:
	//パラメータ
	float translationX;
	float translationY;
	//半径
	float radius;
	//生存フラグ
	int fireFlag;
	//速度
	float speed;
	//攻撃タイマー
	float attackTimer;
	//重力
	float yAdd;

	void Initialize();
	void Update();
	void Fire(float x, float y);
	void Draw();

	void Oncollision(float playerX, float playerY, int playerRadius, int playerFlag, int hp);
};