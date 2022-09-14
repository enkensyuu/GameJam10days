#include "System.h"

void System::Initialize()
{
	gameTimer = 0.0f;
	gameCount = 0;

	HP_ = LoadGraph("HPUI.png");
	LoadDivGraph("Buf.png", 3, 3, 1, 32, 32, BUF);
	LoadDivGraph("DBuf.png", 3, 3, 1, 32, 32, DEBUF);
}

void System::Update(int HP)
{
	gameTimer += 0.05f;
	if (gameTimer >= 1.05)
	{
		gameTimer = 0.0f;
		gameCount += 1;
	}
	if (gameCount >= 1)
	{
		//プレイヤーが出来次第進める
		if (HP >= 92.5) {
			//デバフ

		}
		else
		{
			//バフ

		}

	}

	DrawFormatString(0, 200, GetColor(255, 255, 255), "%f", gameTimer);
}

void System::Draw(int X_, int Y_, int HP)
{
	DrawGraph(0, 0, HP_, true);

	if (gameCount >= 1)
	{
		if (HP > 92.5) {
			if (AnimetionTimer >= 0)
			{
				AnimetionTimer--;
			}
			if (AnimetionTimer <= 0)
			{
				AnimetionTimer = 8;
				AnimetionCount += 1;
				if (AnimetionCount > 2)
				{
					AnimetionCount = 0;
				}
			}
			//デバフ
			DrawGraph(X_ - 15, Y_ - 15, DEBUF[AnimetionCount], true);
		}

		if (HP < 92.5)
		{
			if (AnimetionTimer >= 0)
			{
				AnimetionTimer--;
			}
			if (AnimetionTimer <= 0)
			{
				AnimetionTimer = 8;
				AnimetionCount += 1;
				if (AnimetionCount > 2)
				{
					AnimetionCount = 0;
				}
			}
			//バフ
			DrawGraph(X_ - 15, Y_ - 15, BUF[AnimetionCount], true);
		}
	}
}

int System::Getcount()
{
	return gameCount;
}

float System::GetgameTimer()
{
	return gameTimer;
}

void System::Reset()
{
	gameTimer = 0.0f;
	gameCount = 0;

	HP_X = 200;
	HP_Y = 48;

	AnimetionCount = 0;
	AnimetionCount = 0;
}