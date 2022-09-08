#pragma once
#include "DxLib.h"
#include "math.h"
#include "vector"

#include"PlayerBullet.h"
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
	void Update(char* keys, char* oldkeys);

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

	int Gettrans();

private:
	VECTOR X;

	VECTOR translation;

	/*int X = 100;
	int Y = 660;
	int Z = 0;*/

	float radius = 20.0f;
	float move = 5;
	float GetPlayertrans_ = 100.0f;

	int jflag = false;
	int y_temp = 0;
	int y_prev = 0;
	int jampChange = 25;

	int dflag = false;


};
