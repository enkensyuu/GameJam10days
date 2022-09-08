#include "Player.h"

void Player::Initialize()
{
	translation.x = 100;
	translation.y = 660;
}

void Player::Update(char* keys, char* oldkeys)
{
	X = VGet(translation.x, translation.y, translation.z);

	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (key & PAD_INPUT_RIGHT || keys[KEY_INPUT_RIGHT] == 1)
	{
		translation.x += move;
	}
	if (keys[KEY_INPUT_LEFT] == 1 || key & PAD_INPUT_LEFT)
	{
		translation.x -= move;
	}
	Dodge(keys, oldkeys);
	Jamp(keys, oldkeys);

}

void Player::Draw()
{

	DrawBox(translation.x + radius, translation.y + radius, translation.x - radius, translation.y - radius, GetColor(255, 255, 255), true);
	DrawFormatString(100, 0, GetColor(255, 255, 255), "À•W:%f", translation.z);
	if (dflag == true)
	{
		DrawCircle(100, 100, 10, GetColor(255, 255, 255), true);
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
	if (keys[KEY_INPUT_UP] && jflag == false || key & PAD_INPUT_1 && jflag == false)
	{
		jflag = true;
		y_prev = translation.y;
		translation.y = translation.y - jampChange;
	}
}

void Player::Dodge(char* keys, char* oldkeys)
{
	int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (keys[KEY_INPUT_C] == 1 && dflag == false || key & PAD_INPUT_4 && dflag == false)
	{
		dflag = true;
	}
	if (key & PAD_INPUT_4 && dflag == true)
	{
		dflag = false;
		translation.z = 0;
		move = 5;
	}
	if (dflag == true && translation.z < 32)
	{
		translation.z += radius;
		move = 0;
	}
}

int Player::Gettrans() { return translation.x, translation.y, translation.z; }