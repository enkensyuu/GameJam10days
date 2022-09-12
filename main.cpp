#include "DxLib.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemy2.h"
#include "System.h"
#include "Map.h"

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "";

// ウィンドウ横幅
const int WIN_WIDTH = 1280;

// ウィンドウ縦幅
const int WIN_HEIGHT = 768;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) {
	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);

	// ウィンドウサイズを手動では変更させず、
	// かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// タイトルを変更
	SetMainWindowText(TITLE);

	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(1.0);

	// 画面の背景色を設定する
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 画像などのリソースデータの変数宣言と読み込み


	// ゲームループで使う変数の宣言
	int floor = LoadGraph("Resource/floor.png");
	int second = LoadGraph("Resource/second.png");
	int pillar = LoadGraph("Resource/pillar.png");

	// ゲームループで使う変数の宣言
	System* system_ = new System();
	system_->Initialize();
	Map* map_ = new Map();
	map_->Initialize();
	Player* player_ = new Player();
	player_->Initialize();
	Enemy* enemy_ = new Enemy();
	enemy_->Initialize();
	Enemy2* enemy2_ = new Enemy2();
	enemy2_->Initialize(WIN_HEIGHT, WIN_WIDTH);

	//シーン用変数
	int Scene = 0;

	int timer = 120;
	int timerFlag = 0;

	// 最新のキーボード情報用
	char keys[256] = { 0 };


	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = { 0 };

	// ゲームループ
	while (true) {
		// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
		for (int i = 0; i < 256; i++)
		{
			oldkeys[i] = keys[i];
		}
		// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys);

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		// 更新処理

		int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		switch (Scene)
		{
		case 0://タイトル
			timer--;
			if (timer < 0) {
				timerFlag = 1;
			}

			if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0 && timerFlag == 1 ||
				key & PAD_INPUT_1 && timerFlag == 1)
			{
				player_->Reset();

				Scene = 1;
				timerFlag = 0;
				timer = 120;
			}
			break;
		case 1://操作説明
			timer--;
			if (timer < 0) {
				timerFlag = 1;
			}

			if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0 && timerFlag == 1 ||
				key & PAD_INPUT_1 && timerFlag == 1)
			{
				player_->Reset();

				Scene = 2;
				timerFlag = 0;
				timer = 120;
			}
		
			break;

		case 2://ゲーム
			system_->Update(player_->GetHP_X());
			player_->Update(keys, oldkeys, system_->GetgameTimer(), system_->Getcount(), map_->ScrollX);
			player_->Collision(enemy_->GetFlag(), enemy_->GetTranslation().x, enemy_->GetTranslation().y, enemy_->GetRadius());
			player_->Oncollision(enemy_->GetTranslation().x, enemy_->GetTranslation().y, enemy_->GetRadius(), enemy_->GetFlag(), enemy2_->translation.x, enemy2_->translation.y, enemy2_->radius, enemy2_->aliveFlag, enemy_->GetHP(), enemy2_->HP);
			enemy_->Update(player_->Gettrans_X(), player_->Gettrans_Y(), WIN_HEIGHT, WIN_WIDTH);
			enemy2_->Update(WIN_HEIGHT, WIN_WIDTH, player_->Gettrans_X(), player_->Gettrans_Y(), player_->GetRadius(), player_->GetFlag(), player_->GetHP());
			map_->Update();
			// 描画処理
			map_->Draw(floor, second, pillar);
			player_->Draw();
			enemy_->Draw();
			enemy2_->Draw();

			break;


		case 3://ゲームクリア
			
			break;

		case 4://ゲームオーバー
			timer--;
			if (timer < 0) {
				timerFlag = 1;
			}

			if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0 && timerFlag == 1 ||
				key & PAD_INPUT_1 && timerFlag == 1)
			{
				player_->Reset();

				Scene = 0;
				timerFlag = 0;
				timer = 120;
			}
			break;
		}

		// 描画処理
		switch (Scene)
		{
		case 0://タイトル
			DrawBox(0, 0, 1280, 720, GetColor(255, 255, 0), true);
			break;

		case 1://操作説明
			DrawBox(0, 0, 1280, 720, GetColor(255, 0, 0), true);
			break;

		case 2://ゲーム
			player_->Draw();
			system_->Draw(player_->Gettrans_X(), player_->Gettrans_Y(), player_->GetHP_X());

			break;

		case 3://ゲームクリア

			break;

		case 4://ゲームオーバー
			DrawBox(0, 0, 1280, 720, GetColor(255, 0, 0), true);
			DrawFormatString(100, 120, GetColor(255, 255, 255), "Scene:%d", Scene);
			break;
		}

		// 描画処理

		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();

		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);

		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1) {
			break;
		}

		// ESCキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}
