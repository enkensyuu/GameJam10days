#pragma once
#include "DxLib.h"
#include "EnemyBullet.h"
#include <math.h>
enum class Phase2 {
	Move,	//移動
	Attack,	//攻撃
	Attack2,//攻撃2
	Leave	//離脱
};

class Enemy2
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(int Height, int Width);
	/// <summary>
	/// 更新
	/// </summary>
	void Update(int Height, int Width, float playerX, float playerY, int playerRadius, int playerFlag, int hp);
	/// <summary>
	/// 描画
	/// </summary>
	void Draw(int graphHandle, int bulletHandle);

	/// <summary>
	/// リスポン
	/// </summary>
	void Respon();

	void Move(int Height, int Width);
	void Attack(int Height, int Width);
	void Attack2(int Height, int Width, float x, float y);
	void Leave(int Height, int Width);
	//フェーズ
	Phase2 phase_ = Phase2::Move;
	EnemyBullet* bullet = new EnemyBullet();

	//速度
	float speed;
	//2番目の敵パラメーター
	VECTOR translation;
	float radius;

	//生存フラグ
	int aliveFlag;
	//向きフラグ
	int seeFlag;

	//行動タイマー
	int moveTimer;;
	//リスポンタイマー
	float responTimer;
	//減速し始めるタイマー
	float defSpeedTimer;
	//攻撃し始めるタイマー
	float attackTimer;

	int HP;
};