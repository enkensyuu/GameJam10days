#pragma once
#include "DxLib.h"
#include "Player.h"
class System
{
private:
	Player* player_ = nullptr;

	int HP_X = 200;
	int HP_Y = 48;

	int HP_;
	int BUF[3];
	int DEBUF[3];

	//ƒQ[ƒ€ŽžŠÔ
	float gameTimer;
	int gameCount;

	int AnimetionTimer = 8;
	int AnimetionCount = 0;
public:

	void Initialize();
	void Update(int HP);
	void Draw(int X_, int Y_, int HP);

	int Getcount();

	float GetgameTimer();

	void Reset();
};