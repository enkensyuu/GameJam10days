#pragma once
#include "DxLib.h"

class TitleScene
{
public://メンバ関数

	/// <summary>
	/// コンストクラタ
	/// </summary>
	TitleScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TitleScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	int GetChangeFlag() { return changeFlag_; }
private:

	int changeFlag_ = false;

};