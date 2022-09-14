#include "Enemy2.h"
#include <time.h>

void Enemy2::Initialize(int Height, int Width)
{
	//パラメーター
	translation.x = Width / 2;
	translation.y = -16;
	translation.z = 20;
	radius = 8;
	//生存フラグ
	aliveFlag = 0;
	//向きフラグ
	seeFlag = 0; //0が右,1が左
	//行動カウンタ
	moveTimer = 100;
	//リスポンタイマー
	responTimer = 200;
	//減速するまでの時間
	defSpeedTimer = 150;
	//攻撃し始めるタイマー
	attackTimer = 100;
	//速度
	speed = 1.5f;
	bullet->Initialize();
	//体力
	HP = 25;
}

void Enemy2::Update(int Height, int Width, float playerX, float playerY, int playerRadius, int playerFlag, int hp)
{
	bullet->Oncollision(playerX, playerY, playerRadius, playerFlag, hp);
	srand(time(nullptr));
	//リスポーン
	if (aliveFlag != 1)
	{
		Respon();
	}
	else if (aliveFlag == 1)
	{
		bullet->Update();
		switch (phase_)
		{
		case Phase2::Move:
		default:
			Move(Height, Width);
			break;
		case Phase2::Attack:
			Attack(Height, Width);
			break;
		case Phase2::Attack2:
			Attack2(Height, Width, playerX, playerY);
			break;
		case Phase2::Leave:
			Leave(Height, Width);
			break;
		}
	}


}

void Enemy2::Draw(int graphHandle, int bulletHandle)
{
	if (aliveFlag == 0)
	{
		DrawGraph(translation.x - radius, translation.y - radius, graphHandle, true);
	}
	else if (aliveFlag == 1)
	{
		if (seeFlag == 0)
		{
			DrawTurnGraph(translation.x - radius, translation.y - radius, graphHandle, true);
		}
		else if (seeFlag == 1)
		{
			DrawGraph(translation.x - radius, translation.y - radius, graphHandle, true);
		}
	}
	bullet->Draw(bulletHandle);
	/*DrawFormatString(0, 60, color, "敵2体目の情報");
	DrawFormatString(0, 75, color, "リスタイマー[%f]減速タイマー[%f]攻撃タイマー[%f]", responTimer, defSpeedTimer, attackTimer);
	DrawFormatString(0, 90, color, "フラグ[%d]", aliveFlag);
	DrawFormatString(0, 105, color, "座標[%f][%f][%f]", translation.x, translation.y, translation.z);
	DrawFormatString(0, 120, color, "フェーズ[%d]", phase_);*/
}

void Enemy2::Respon()
{
	if (responTimer > 0.0f)
	{
		responTimer -= 0.5f;
	}
	if (responTimer <= 0.0f)
	{
		responTimer = 0.0f;	//リスポンタイマーの初期化
		if (translation.y <= 115.0f)
		{
			radius += 0.01f;
			translation.y += 0.8f;
		}
		else if (translation.y >= 115.0f && translation.z != 0.0f)
		{
			if (radius != 16)
			{
				radius += 0.5f;
			}
			translation.z -= 0.5f;
		}
		if (translation.y >= 38.0f && translation.z == 0.0f)
		{

			aliveFlag = 1;	//生存フラグの変化
		}
	}

}

void Enemy2::Move(int Height, int Width)
{
	//次の行動に移るまで
	if (attackTimer != 0.0f)
	{
		attackTimer -= 0.8f;
	}
	if (attackTimer <= 0.0f)
	{
		phase_ = Phase2::Attack;
		attackTimer = 100.0f;
	}

	translation.x += speed;
	if (translation.x + radius > Width)
	{
		speed = -speed;
	}
	else if (translation.x - radius < Width / 3)
	{
		speed = -speed;
	}
}

void Enemy2::Attack(int Height, int Width)
{
	//次の行動に移るまで
	if (defSpeedTimer != 0.0f)
	{
		defSpeedTimer -= 0.8f;
	}
	if (defSpeedTimer <= 0.0f)
	{
		phase_ = Phase2::Attack2;
	}
	bullet->Fire(translation.x, translation.y);
	translation.x -= 0.1f;
}

void Enemy2::Attack2(int Height, int Width, float x, float y)
{
	if (moveTimer != 0.0f)
	{
		translation.x = x;
		moveTimer -= 1.0f;
	}
	else if (moveTimer <= 0.0f)
	{
		translation.y += 8.0f;
		if (translation.y > Height)
		{
			phase_ = Phase2::Leave;
			translation.y = 96;
			moveTimer = 100.0f;
		}
	}

	DrawFormatString(0, 50, GetColor(255, 255, 255), "座標:[%f][%f]\nタイマー:[%f]\n", translation.x, translation.y, moveTimer);

}

void Enemy2::Leave(int Height, int Width)
{
	//次の行動に移るまで
	if (defSpeedTimer != 0.0f)
	{
		defSpeedTimer -= 1.0f;
	}

	if (defSpeedTimer <= 0.0f)
	{
		phase_ = Phase2::Move;
		defSpeedTimer = 150.0f;
	}
}