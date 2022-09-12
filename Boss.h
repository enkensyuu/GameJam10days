#pragma once

class Boss
{
public:
	void Initialize();

	void Attack(int x);

	void Draw();

private:
	int BossX;
	int BossY;
	int BossR;

	int BossMoveFlag;

	int BossLiveFlag;

	int BossJudge;

	int ransu;

	int BossSpeeg = 7;


};
