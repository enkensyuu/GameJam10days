#include "Enemy.h"
#include "Player.h"

void Enemy::Initialize()
{
	//座標
	//パラメーター
	translation.x = 0;
	translation.y = 0;
	translation.z = 0;
	//生存フラグ
	aliveFlag = 0;
	//移動フラグ
	moveFlag = 0;
	//リスポンタイマー
	responTimer = 50.0f;
	//移動タイマー
	moveTimer = 100.0f;

	//体力
	HP = 200;

	radius = 32;
	//重力
	yAdd = 0.0f;

}

void Enemy::Update(float x, float y, int Height, int Width)
{
	if (aliveFlag != 1)
	{
		Respon(x, y, Height, Width);
	}
	else if (aliveFlag == 1)
	{
		switch (moveFlag)
		{
		case 0:
			Move(x, y);
			if (translation.x <= 900 && moveFlag != 1)
			{
				moveFlag = 1;
			}
			break;
		case 1:
			if (moveTimer != 0)
			{
				moveTimer -= 0.5f;
			}
			if (moveTimer <= 0.0f)
			{
				moveTimer = 100.0f;
				moveFlag = 2;
			}
			break;
		case 2: //攻撃
			Attack(x, y);
			if (moveTimer != 0)
			{
				moveTimer -= 0.5f;
			}
			if (moveTimer <= 0.0f)
			{
				moveTimer = 20.0f;
				moveFlag = 3;
			}
			break;
		case 3: //後退
			Leave(x, y);
			if (moveTimer != 0)
			{
				moveTimer -= 0.5f;
			}
			if (moveTimer <= 0.0f)
			{
				moveTimer = 200.0f;
				moveFlag = 2;
			}
			break;
		}

	}
	DrawFormatString(0, 15, GetColor(255, 255, 255), "フラグ:%d", moveFlag);
}

void Enemy::Draw()
{
	int color = GetColor(255, 255, 0);

	if (aliveFlag == 1)
	{
		DrawCircle(translation.x, translation.y, radius, color, TRUE);
	}

	DrawFormatString(600, 0, color, "座標[%d]", aliveFlag);


	DrawFormatString(0, 30, color, "タイマー[%f]", responTimer);
}

void Enemy::Respon(float X, float Y, int Height, int Width)
{
	if (responTimer != 0.0f && aliveFlag != 1)
	{
		responTimer -= 0.5f;
	}
	if (responTimer <= 0.0f && aliveFlag != 1)
	{
		responTimer = 50.0f;
		translation.x = Width;
		translation.y = 690;
		aliveFlag = 1;	//生存フラグ変化
	}
}

void Enemy::Move(float x, float y)
{
	translation.x -= 1.5f;
}

void Enemy::Attack(float x, float y)
{
	if (x < translation.x - radius)
	{
		translation.x += -2.0f;
	}
	else if (x > translation.x + radius)
	{
		translation.x += 2.0f;
	}
}

void Enemy::Leave(float x, float y)
{
	if (x < translation.x - radius)
	{
		translation.x += 2.8f;
	}
	else if (x > translation.x + radius)
	{
		translation.x += -2.8f;
	}
}