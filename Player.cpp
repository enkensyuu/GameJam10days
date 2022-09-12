#include "Player.h"

void Player::Initialize()
{
	translation.x = 100;
	translation.y = 660;
	translation.z = 0.0f;
}

void Player::Update(char* keys, char* oldkeys, float gameTimer, int Count, int scrollX)
{

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
		//ƒvƒŒƒCƒ„[‚ªo—ˆŸ‘æi‚ß‚é
		if (HP_X > 92.5) {
			bufflag = false;
			debufflag = true;
			Attack_level = 1.0f;
			if (debufflag == true) {
				Attack_level = 0.5f;
			}
		}
		if (HP_X < 92.5)
		{
			debufflag = false;
			bufflag = true;
			Attack_level = 1.0f;
			if (bufflag == true) {
				//ƒoƒt
				Attack_level = 2.0f;
			}
		}
	}
	DrawFormatString(100, 60, GetColor(255, 255, 255), "taima-:%f", gameTimer);
	DrawFormatString(100, 90, GetColor(255, 255, 255), "Attack_level:%f", Attack_level);
	DrawFormatString(100, 120, GetColor(255, 255, 255), "Attack_level:%f", Attack_level);
	Dodge(keys, oldkeys);
	Jamp(keys, oldkeys);
	Attack(keys, oldkeys);

}

void Player::Draw()
{
	DrawBox((int)(translation.x + Playerradius), (int)(translation.y + Playerradius), (int)(translation.x - Playerradius), (int)(translation.y - Playerradius), GetColor(255, 255, 255), true);

	DrawBox(15, 15, HP_X, HP_Y, GetColor(0, 255, 0), true);//HPƒo[


	if (Rflag == true || Lflag == true || Uflag == true)
	{
		for (int i = 0; i < BulletNum; i++)
		{
			if (isShot_Right[i] == 1)
			{
				shot_Right_X[i] += 20;
				DrawCircle((int)(shot_Right_X[i] + Bullet_radius), shot_Right_Y[i], Bullet_radius, GetColor(255, 0, 0), true);
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
				DrawCircle((int)(shot_Left_X[i] + Bullet_radius), shot_Left_Y[i], Bullet_radius, GetColor(255, 0, 0), true);
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
				DrawCircle(shot_Up_X[i], (int)(shot_Up_Y[i] + Bullet_radius), Bullet_radius, GetColor(255, 0, 0), true);
			}
			if (shot_Up_Y[i] < 0)
			{
				isShot_Up[i] = 0;
			}
		}
	}
}

void Player::Jamp(char* keys, char* oldkeys)
{
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	if (jflag == true) {
		y_temp = translation.y;
		translation.y += (translation.y - y_prev) + 1;
		y_prev = y_temp;
		//‚Ì‚¿‚É•ÏX----
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

void Player::Dodge(char* keys, char* oldkeys)
{
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	if (keys[KEY_INPUT_C] == 1 && oldkeys[KEY_INPUT_C] == 0 && dflag == false ||
		key & PAD_INPUT_3 && dflag == false && dodge_timer == 0 && dodge_interval <= 0)
	{
		dflag = true;
		dodge_timer = 60;
		dodge_interval = 300;
	}

	if (dflag == true)
	{
		dodge_timer--;
	}
	if (dflag == true && translation.z < 32)
	{
		translation.z += Bullet_radius;
		move = 0;
	}

	if (dflag == true && dodge_timer <= 0)
	{
		translation.z = 0;
		move = 5;
		dodge_interval--;
	}
	if (dodge_interval <= 0)
	{
		dflag = false;
		dodge_timer = 0;
	}

	if (key & PAD_INPUT_3)
	{
		DrawFormatString(100, 190, GetColor(255, 255, 255), "”½‰");
	}
	DrawFormatString(100, 210, GetColor(255, 255, 255), "translation:%f", translation.z);
	DrawFormatString(100, 230, GetColor(255, 255, 255), "dodge_timer:%d", dodge_timer);
	DrawFormatString(100, 250, GetColor(255, 255, 255), "dodge_interval:%d", dodge_interval);
}

void Player::Attack(char* keys, char* oldkeys)
{
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (keys[KEY_INPUT_SPACE] == 1 && bulletCooltime == 0 && Rflag == true ||
		key & PAD_INPUT_1 && bulletCooltime == 0 && Rflag == true)
	{
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
		//ƒvƒŒƒCƒ„[‚Æ“G

		if (aliveFlag == 1 && enemyFlag == 1)
		{
			float a = (translation.x - enemyX) * (translation.x - enemyX);
			float b = (translation.y - enemyY) * (translation.y - enemyY);
			float c = (Playerradius + enemyradius) * (Playerradius + enemyradius);
			if (c >= a + b)
			{
				HP_ -= 1;
				aliveFlag = 2;

			}
		}
		//ƒŠƒXƒ|ƒ“ˆ—
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
		int HP, int HP2)
	{
		//“G1‚ÆƒvƒŒƒCƒ„[’e
		for (int i = 0; i < 6; i++)
		{
			for (int f = 0; f < 50; f++)
			{
				if (enemyFlag == 1 && isShot_Right[f] == 1)
				{
					float a = (enemyX - shot_Right_X[f]) * (enemyX - shot_Right_X[f]);
					float b = (enemyY - shot_Right_Y[f]) * (enemyY - shot_Right_Y[f]);
					float c = (enemyRadius + Bullet_radius/*©’e”¼Œa*/) * (enemyRadius + Bullet_radius/*©’e”¼Œa*/);
					if (c >= a + b)
					{
						HP -= 1;
						HP_ += 1;
						enemyFlag = 2;
						isShot_Right[f] = 0;
					}
				}
			}
		}

		//“G2‚ÆƒvƒŒ[ƒ„[’e
		for (int i = 0; i < 50; i++)
		{
			if (enemy2Flag == 1 && isShot_Up[i] == 1)
			{
				float a = (enemy2X - shot_Up_X[i]) * (enemy2X - shot_Up_X[i]);
				float b = (enemy2Y - shot_Up_Y[i]) * (enemy2Y - shot_Up_Y[i]);
				float c = (enemy2Radius + Bullet_radius/*©’e”¼Œa*/) * (enemy2Radius + Bullet_radius/*©’e”¼Œa*/);
				if (c >= a + b)
				{
					HP2 -= 1;
					HP_ += 1;
					enemy2Flag = 2;
					isShot_Up[i] = 0;
				}
			}
		}

		//“G1‚ÆƒvƒŒƒCƒ„[’e
		for (int i = 0; i < 6; i++)
		{
			for (int f = 0; f < 50; f++)
			{
				if (enemyFlag == 1 && isShot_Left[f] == 1)
				{
					float a = (enemyX - shot_Left_X[f]) * (enemyX - shot_Left_X[f]);
					float b = (enemyY - shot_Left_Y[f]) * (enemyY - shot_Left_Y[f]);
					float c = (enemyRadius + Bullet_radius/*©’e”¼Œa*/) * (enemyRadius + Bullet_radius/*©’e”¼Œa*/);
					if (c >= a + b)
					{
						HP -= 1;
						HP_ += 1;
						enemyFlag = 2;
						isShot_Left[f] = 0;
					}
				}
			}
		}


	}

	int Player::Gettrans_X() { return translation.x; }

	int Player::Gettrans_Y() { return translation.y; }

	int Player::GetHP_X() { return HP_X; }

	int Player::GetFlag_b() { return bufflag; }

	int Player::GetFlag_de() { return debufflag; }

	void Player::Reset()
	{
		translation.x = 100;
		translation.y = 660;
		translation.z = 0.0f;

		dodge_timer = 0;
		dodge_interval = 0;
		//ƒWƒƒƒ“ƒv---------------------
		jflag = false;
		y_temp = 0;
		y_prev = 0;
		jampChange = 25;

		dflag = false;
		//----------------------------
		//ƒoƒtƒfƒoƒt
		Attack_level = 1.0f;
		Attack_save = 0.0f;
		bufflag = false;
		debufflag = false;

		bufTimer = 30;
		debufTimer = 30;
		//’e---------------------------
		Rflag = true;
		Lflag = false;
		Uflag = false;

		Bulletmove_X = 0;
		Bulletmove_Y = 0;

		bulletCooltime = 0;

		HP_X = 200;
	}
