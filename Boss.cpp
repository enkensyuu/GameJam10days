#include"Boss.h"
#include<stdlib.h>
#include<time.h>

void Boss::Initialize()
{
	BossX = 1024;
	BossY = 448;
	BossR = 256;

	BossMoveFlag = false;

	BossLiveFlag = true;

	ransu = true;
}

void Boss::Attack(int x)
{
	if (x >= 7680)
	{
		if (BossLiveFlag == true)
		{
			BossMoveFlag = true;
		}
	}
	if (BossMoveFlag == true)
	{
		if (ransu == true)
		{
			srand(time(nullptr));
			BossJudge = rand() % 3;
		}
	}

	if (BossJudge == 0)
	{
		ransu = false;

	}
}

void Boss::Draw()
{
}
