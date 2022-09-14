#include "Player.h"
#define PI 3.14f

void Player::Initialize()
{
	translation.x = 100;
	translation.y = 660;
	translation.z = 0.0f;

	score = 0;

	LoadDivGraph("score_num.png", 10, 10, 1, 64, 64, graphHandle);

	score_notation = LoadGraph("score.png", true);
	LoadDivGraph("Player.png", 3, 3, 1, 64, 64, player_);
	player_jump = LoadGraph("Playerjump.png", true);
	Bullet_ = LoadGraph("Bullet.png", true);

	Bullet_SE = LoadSoundMem("拳銃を撃つ.mp3");
	ChangeVolumeSoundMem(255 * 25 / 100, Bullet_SE);
}

void Player::Update(char* keys, char* oldkeys, float gameTimer, int Count, int scrollX)
{
	if (scrollX != 7680)
	{
		translation.x -= 0.5f;
	}

	X = VGet(translation.x, translation.y, translation.z);

	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (keys[KEY_INPUT_RIGHT] == 1 || key & PAD_INPUT_RIGHT)
	{
		Uflag = false;
		Lflag = false;
		Rflag = true;
		translation.x += move;

	}
	if (keys[KEY_INPUT_LEFT] == 1 || key & PAD_INPUT_LEFT)
	{
		Uflag = false;
		Rflag = false;
		Lflag = true;
		translation.x -= move;
	}
	if (keys[KEY_INPUT_UP] == 1 || key & PAD_INPUT_UP)
	{
		Rflag = false;
		Lflag = false;
		Uflag = true;
	}

	if (gameTimer >= 1)
	{
		Count += 1;
		HP_X -= 5;
	}
	if (Count >= 1)
	{
		//プレイヤーが出来次第進める
		if (HP_X > 92.5) {
			bufflag = false;
			debufflag = true;
			Attack_level = 2.0f;
			if (debufflag == true) {
				Attack_level = 2.0f;
			}
		}
		if (HP_X < 92.5)
		{
			debufflag = false;
			bufflag = true;
			Attack_level = 2.0f;
			if (bufflag == true) {
				//バフ
				Attack_level = 3.0f;
			}
		}
	}
	Jamp(keys, oldkeys);
	Attack(keys, oldkeys);

}

void Player::Draw()
{

	if (Rflag == true)
	{
		DrawGraph(translation.x + 32, translation.y, player_[AnimetionCount], true);
	}
	if (Lflag == true)
	{
		DrawTurnGraph(translation.x - 32, translation.y, player_[AnimetionCount], true);
	}
	if (Uflag == true)
	{
		DrawGraph(translation.x, translation.y, player_jump, true);
	}

	DrawBox(15, 15, HP_X, HP_Y, GetColor(0, 255, 0), true);//HPバー

	if (HP_X > 200)
	{
		HP_X = 200;
	}
	if (Rflag == true || Lflag == true || Uflag == true)
	{
		for (int i = 0; i < BulletNum; i++)
		{
			if (isShot_Right[i] == 1)
			{
				shot_Right_X[i] += 20;
				DrawGraph((int)(shot_Right_X[i] + Bullet_radius), (int)(shot_Right_Y[i] + 16), Bullet_, true);
			}
			if (shot_Right_X[i] > 1280)
			{
				isShot_Right[i] = 0;
			}
		}
	}

	if (Lflag == true || Rflag == true || Uflag == true)
	{
		for (int i = 0; i < BulletNum; i++)
		{
			if (isShot_Left[i] == 1)
			{
				shot_Left_X[i] -= 20;
				DrawTurnGraph((int)(shot_Left_X[i] + Bullet_radius), (int)(shot_Left_Y[i] + 16), Bullet_, true);
			}
			if (shot_Left_X[i] < 0)
			{
				isShot_Left[i] = 0;
			}
		}
	}

	if (Uflag == true || Rflag == true || Lflag == true)
	{
		for (int i = 0; i < BulletNum; i++)
		{
			if (isShot_Up[i] == 1)
			{
				shot_Up_Y[i] -= 20;
				DrawRotaGraph(shot_Up_X[i] + 32, (int)(shot_Up_Y[i] + Bullet_radius), 1.0f, PI / 180 * -90, Bullet_, TRUE);
			}
			if (shot_Up_Y[i] < 0)
			{
				isShot_Up[i] = 0;
			}
		}
	}

	for (int i = 0; i < 7; i++)
	{
		DrawGraph(posX + 32 * i, 0, graphHandle[eachnum[i]], true);
	}
	DrawGraph(550, 0, score_notation, true);
}

void Player::Jamp(char* keys, char* oldkeys)
{
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	if (jflag == true) {
		y_temp = translation.y;
		translation.y += (translation.y - y_prev) + 1;
		y_prev = y_temp;
		//のちに変更----
		if (translation.y == 660) {
			jflag = false;
		}
		//--------------
	}
	if (keys[KEY_INPUT_UP] && jflag == false || key & PAD_INPUT_2 && jflag == false)
	{
		jflag = true;
		y_prev = translation.y;
		translation.y = translation.y - jampChange;
	}
}

void Player::Attack(char* keys, char* oldkeys)
{
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	if (keys[KEY_INPUT_SPACE] == 1 && bulletCooltime == 0 && Rflag == true ||
		key & PAD_INPUT_1 && bulletCooltime == 0 && Rflag == true)
	{
		PlaySoundMem(Bullet_SE, DX_PLAYTYPE_BACK);

		for (int i = 0; i < BulletNum; i++) {
			Bulletmove_X = translation.x;
			Bulletmove_Y = translation.y;
			if (isShot_Right[i] == 0)
			{
				isShot_Right[i] = 1;
				shot_Right_X[i] = Bulletmove_X;
				shot_Right_Y[i] = Bulletmove_Y;
				bulletCooltime = 10;
				break;
			}
		}
	}

	if (keys[KEY_INPUT_SPACE] == 1 && bulletCooltime == 0 && Lflag == true ||
		key & PAD_INPUT_1 && bulletCooltime == 0 && Lflag == true)
	{
		PlaySoundMem(Bullet_SE, DX_PLAYTYPE_BACK);
		for (int i = 0; i < BulletNum; i++) {
			Bulletmove_X = translation.x;
			Bulletmove_Y = translation.y;
			if (isShot_Left[i] == 0)
			{
				isShot_Left[i] = 1;
				shot_Left_X[i] = Bulletmove_X;
				shot_Left_Y[i] = Bulletmove_Y;
				bulletCooltime = 10;
				break;
			}
		}
	}
	if (keys[KEY_INPUT_SPACE] == 1 && bulletCooltime == 0 && Uflag == true ||
		key & PAD_INPUT_1 && bulletCooltime == 0 && Uflag == true)
	{
		PlaySoundMem(Bullet_SE, DX_PLAYTYPE_BACK);
		for (int i = 0; i < BulletNum; i++) {
			Bulletmove_X = translation.x;
			Bulletmove_Y = translation.y;
			if (isShot_Up[i] == 0)
			{
				isShot_Up[i] = 1;
				shot_Up_X[i] = Bulletmove_X;
				shot_Up_Y[i] = Bulletmove_Y;
				bulletCooltime = 10;
				break;
			}
		}
	}
	if (bulletCooltime > 0)
	{
		bulletCooltime--;
	}
}

void Player::Collision(int enemyFlag, float enemyX, float enemyY, float enemyradius)
{
	//プレイヤーと敵

	if (aliveFlag == 1 && enemyFlag == 1)
	{
		float a = (translation.x - enemyX) * (translation.x - enemyX);
		float b = (translation.y - enemyY) * (translation.y - enemyY);
		float c = (Playerradius + enemyradius) * (Playerradius + enemyradius);
		if (c >= a + b)
		{
			HP_X -= 20;
			aliveFlag = 2;

		}
	}
	//リスポン処理
	if (aliveFlag == 2)
	{
		responTimer -= 0.5f;
		if (responTimer <= 0.0f)
		{
			responTimer = 25.0f;
			aliveFlag = 1;
		}
	}
}

void Player::Oncollision(float enemyX, float enemyY, int enemyRadius, int enemyFlag, float enemy2X, float enemy2Y, int enemy2Radius, int enemy2Flag,
	int HP, int HP2,int width)
{
	//敵1とプレイヤー弾
	for (int i = 0; i < 6; i++)
	{
		for (int f = 0; f < 50; f++)
		{
			if (enemyFlag == 1 && isShot_Right[f] == 1)
			{
				float a = (enemyX - shot_Right_X[f]) * (enemyX - shot_Right_X[f]);
				float b = (enemyY - shot_Right_Y[f]) * (enemyY - shot_Right_Y[f]);
				float c = (enemyRadius + Bullet_radius/*←弾半径*/) * (enemyRadius + Bullet_radius/*←弾半径*/);
				if (c >= a + b)
				{
					enemyFlag = 2;
					score_();
					HP -= Attack_level;
					if (translation.x > width / width && translation.x < width)
					{
						HP_X += 5;
					}
					isShot_Right[f] = 0;
				}
			}

		}
	}

	//敵2とプレーヤー弾
	for (int i = 0; i < 50; i++)
	{
		if (enemy2Flag == 1 && isShot_Up[i] == 1)
		{
			float a = (enemy2X - shot_Up_X[i]) * (enemy2X - shot_Up_X[i]);
			float b = (enemy2Y - shot_Up_Y[i]) * (enemy2Y - shot_Up_Y[i]);
			float c = (enemy2Radius + Bullet_radius/*←弾半径*/) * (enemy2Radius + Bullet_radius/*←弾半径*/);
			if (c >= a + b)
			{
				enemy2Flag = 2;
				score_();
				HP2 -= Attack_level;
				if (translation.x > width / width && translation.x < width)
				{
					HP_X += 5;
				}
				isShot_Up[i] = 0;
			}
		}

	}

	//敵1とプレイヤー弾
	for (int i = 0; i < 6; i++)
	{
		for (int f = 0; f < 50; f++)
		{
			if (enemyFlag == 1 && isShot_Left[f] == 1)
			{
				float a = (enemyX - shot_Left_X[f]) * (enemyX - shot_Left_X[f]);
				float b = (enemyY - shot_Left_Y[f]) * (enemyY - shot_Left_Y[f]);
				float c = (enemyRadius + Bullet_radius/*←弾半径*/) * (enemyRadius + Bullet_radius/*←弾半径*/);
				if (c >= a + b)
				{
					enemyFlag = 2;
					score_();
					HP -= Attack_level;
					if (translation.x > width / width && translation.x < width)
					{
						HP_X += 5;
					}
					isShot_Left[f] = 0;
				}
			}
		}
	}
}

int Player::Gettrans_X() { return translation.x; }

int Player::Gettrans_Y() { return translation.y; }

int Player::GetHP_X() { return HP_X; }

int Player::GetHP() { return HP_; }

int Player::GetFlag() { return aliveFlag; }

int Player::GetBuffFlag() { return bufflag; }

int Player::GetDeBuffFlag() { return debufflag; }

float Player::GetRadius() { return Playerradius; }

void Player::score_()
{
	if (bufflag == false)
	{
		score += 100;
	}
	else if (bufflag == true)
	{
		score += 200;
	}
	num = score;


	eachnum[0] = num / 1000000;
	num = num % 1000000;

	eachnum[1] = num / 100000;
	num = num % 100000;

	eachnum[2] = num / 10000;
	num = num % 10000;

	eachnum[3] = num / 1000;
	num = num % 1000;

	eachnum[4] = num / 100;
	num = num % 100;

	eachnum[5] = num / 10;
	num = num % 10;

	eachnum[6] = num;
}

void Player::Reset()
{
	translation.x = 100;
	translation.y = 660;
	translation.z = 0.0f;

	dodge_timer = 0;
	dodge_interval = 0;
	//ジャンプ---------------------
	jflag = false;
	y_temp = 0;
	y_prev = 0;
	jampChange = 25;

	dflag = false;
	//----------------------------
	//バフデバフ
	Attack_level = 1.0f;
	Attack_save = 0.0f;
	bufflag = false;
	debufflag = false;

	bufTimer = 30;
	debufTimer = 30;
	//弾---------------------------
	Rflag = true;
	Lflag = false;
	Uflag = false;

	Bulletmove_X = 0;
	Bulletmove_Y = 0;

	bulletCooltime = 0;

	HP_X = 200;

	//タイマー
	responTimer = 25.0f;

	// ゲームループで使う変数の宣言
	graphHandle[10] = {};

	score = 0;
	num = 0;
	posX = 800;

	AnimetionTimer = 8;
	AnimetionCount = 1;
}