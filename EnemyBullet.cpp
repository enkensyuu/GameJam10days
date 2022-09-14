#include "EnemyBullet.h"

void EnemyBullet::Initialize()
{
	//パラメータ
	translationX = 0;
	translationY = 0;
	//フラグ
	fireFlag = 0;
	//重力
	yAdd = 0.0f;
	//攻撃タイマー
	attackTimer = 145.0f;
	//半径
	radius = 16.0f;
	//速度
	speed = 5.0f;
}

void EnemyBullet::Update()
{
	if (fireFlag == 1)
	{
		translationY += yAdd;
		yAdd += 0.2f;
		if (translationY >= 680.0f)
		{
			yAdd = 0.0f;
			translationX -= 5.0f;
			radius += 0.5f;
		}
		if (radius >= 64.0f)
		{
			radius = 16.0f;
			fireFlag = 0;
		}
	}
}

void EnemyBullet::Fire(float x, float y)
{
	if (fireFlag != 1)
	{
		attackTimer -= 0.5f;
		if (attackTimer <= 0 && fireFlag != 1)
		{
			translationX = x;
			translationX = x;
			translationY = y;
			yAdd = -8.0f;
			fireFlag = 1;
		}
	}
}

void EnemyBullet::Draw(int bulletHundle)
{
	if (fireFlag == 1)
	{
		DrawGraph(translationX - radius, translationY - radius, bulletHundle, TRUE);
	}
}

void EnemyBullet::Oncollision(float playerX, float playerY, int playerRadius, int playerFlag, int hp)
{
	//プレイヤーと敵弾

	if (playerFlag == 1 && fireFlag == 1)
	{
		float a = (playerX - translationX) * (playerX - translationX);
		float b = (playerY - translationY) * (playerY - translationY);
		float c = (playerRadius + radius) * (playerRadius + radius);
		if (c >= a + b)
		{
			hp -= 1;
			playerFlag = 2;
			radius = 16.0f;
			fireFlag = 0;
		}
	}

}