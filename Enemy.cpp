#include "Enemy.h"
#include "Player.h"

void Enemy::Initialize()
{
	//座標
	//パラメーター
	translation.x = 0;
	translation.y = 0;
	translation.z = 0;
	//向きフラグ
	seeFlag = 0; //0が左, 1が右
	//生存フラグ
	aliveFlag = 0;
	//ジャンプフラグ
	jumpFlag = 0;
	//隠れるフラグ
	hideFlag = 0;
	//移動フラグ
	moveFlag = 0;
	//隠れるタイマー
	hideTimer = 25.0f;
	//リスポンタイマー
	responTimer = 50.0f;
	//ジャンプタイマー
	jumpTimer = 75.0f;
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
		if (translation.x > x)
		{
			seeFlag = 1;
		}
		else if (translation.x < x)
		{
			seeFlag = 0;
		}
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
				moveTimer = 50.0f;
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
				moveTimer = 108.0f;
				moveFlag = 4;
			}
			break;
		case 4:
			//ジャンプ
			Attack2(x, y);
			if (moveTimer != 0)
			{
				moveTimer -= 0.5f;
			}
			if (moveTimer <= 0.0f)
			{
				moveTimer = 108.0f;
				moveFlag = 5;
			}
			break;
		case 5:
			Hide(x, y);
			break;
		}
	}
}

void Enemy::Draw(int graphHandle)
{
	if (aliveFlag == 1)
	{
		if (seeFlag == 0)
		{
			DrawGraph(translation.x - radius + radius, translation.y - radius, graphHandle, TRUE);
		}
		else if (seeFlag == 1)
		{
			DrawTurnGraph(translation.x - radius + radius, translation.y - radius, graphHandle, TRUE);
		}
	}
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
		translation.y = 680;
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
	if (translation.y != 680)
	{
		translation.y = 680;
	}
}

void Enemy::Attack2(float x, float y)
{
	//ジャンプ
	if (jumpTimer > 0.0f && jumpFlag == 0)
	{
		jumpTimer -= 3.0f;
	}

	if (jumpTimer <= 0.0f && jumpFlag == 0)
	{
		jumpFlag = 1;
		yAdd = -8.0f;
		translation.y += yAdd;
	}
	if (jumpFlag == 1 && translation.y < 680)
	{
		translation.y += yAdd;
		yAdd += 0.2f;
		if (translation.y >= 680)
		{
			yAdd = 0.0f;
			translation.y = 680;
			jumpFlag = 0;
			jumpTimer = 75.0f;
		}
	}
}

void Enemy::Hide(float x, float y)
{
	if (hideTimer > 0.0f && hideFlag == 0)
	{
		translation.y = 776;
		translation.x = x;
		hideTimer -= 3.0f;
	}
	else if (hideTimer <= 0.0f && hideFlag == 0)
	{
		hideFlag = 1;
		hideTimer = 25.0f;
	}

	if (hideFlag == 1 && translation.y > 680)
	{
		translation.y -= 1.0f;
	}
	if (translation.y <= 680)
	{
		hideFlag = 0;
		moveFlag = 2;
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