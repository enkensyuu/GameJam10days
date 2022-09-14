#pragma once
#include "DxLib.h"
#include "math.h"
#include "Map.h"
#include "vector"



class Player
{
public:
	///<summary>
	///初期化
	///</summary>
	///<param name="model">モデル</param>
	///<param name="textureHandle">テクスチャハンドル</param>
	void Initialize();

	///<summary>
	///更新
	///</summary>
	void Update(char* keys, char* oldkeys, float gameTimer, int Count, int scrollX);

	///<summary>
	///描画
	///</summary>
	void Draw();

	///<summary>
	///ジャンプ
	///</summary>
	void Jamp(char* keys, char* oldkeys);

	///<summary>
	///回避
	///</summary>
	void Dodge(char* keys, char* oldkeys);

	/// <summary>
	/// 攻撃
	/// </summary>
	void Attack(char* keys, char* oldkeys);

	void Collision(int enemyFlag, float enemyX, float enemyY, float enemyradius);

	void Oncollision(float enemyX, float enemyY, int enemyRadius, int enemyFlag, float enemy2X, float enemy2Y, int enemy2Radius, int enemy2Flag,
		int HP, int HP2);
public:
	int Gettrans_X();

	int Gettrans_Y();

	int GetHP();

	int GetHP_X();

	int GetBuffFlag();

	int GetDeBuffFlag();

	int GetFlag();

	void Reset();

	float GetRadius();

	void score_();
	//void SetBullet() {
	//	bullet_->Update();
	//}

	VECTOR X;

	Map* map = new Map();
private:

	VECTOR translation;

	//プレイヤー
	float Playerradius = 32.0f;
	float move = 5;
	float GetPlayertrans_ = 100.0f;

	int dodge_timer = 5;
	int	dodge_interval = 120;

	int Bullet_radius = 16;
	int aliveFlag = 1;
	//--------------------

	//ジャンプ---------------------
	bool jflag = false;
	float y_temp = 0;
	float y_prev = 0;
	int jampChange = 25;


	bool dflag = false;
	//----------------------------
	//バフデバフ
	float Attack_level = 1.0f;
	float Attack_save = 0.0f;
	int bufflag = false;
	int debufflag = false;

	int bufTimer = 30;
	int debufTimer = 30;
	//弾---------------------------
	bool Rflag = true;
	bool Lflag = false;
	bool Uflag = false;

	float Bulletmove_X = 0;
	float Bulletmove_Y = 0;

	static const int BulletNum = 50;

	int shot_Right_X[BulletNum];
	int shot_Right_Y[BulletNum];
	int shot_Left_X[BulletNum];
	int shot_Left_Y[BulletNum];
	int shot_Up_X[BulletNum];
	int shot_Up_Y[BulletNum];

	int isShot_Right[BulletNum];
	int isShot_Left[BulletNum];
	int isShot_Up[BulletNum];

	int bulletCooltime = 0;
	//---------------------------


	int memory_left_Y;

	int HP_X = 200;
	int HP_Y = 48;

	int HP_;
	int BUF[3];
	int DEBUF[3];

	//タイマー
	float responTimer = 25.0f;

	// ゲームループで使う変数の宣言
	int graphHandle[10] = {};

	int score = 0;
	int num = 0;
	int eachnum[7] = {};
	int posX = 800;

	int score_notation;

	int player_[2];
	int AnimetionTimer = 8;
	int AnimetionCount = 1;
	int player_jump;

	int Bullet_;
	int Bullet_SE;
};