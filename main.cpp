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
	int floor = LoadGraph("floor.png");
	int second = LoadGraph("second.png");
	int pillar = LoadGraph("pillar.png");

	int enemy[6]; LoadDivGraph("enemy.png", 6, 6, 1, 64, 64, enemy, FALSE);
	int enemy2[3]; LoadDivGraph("enemy2.png", 3, 3, 1, 64, 64, enemy2, FALSE);

	int enemyBullet[4]; LoadDivGraph("enemy2_bullet.png", 4, 4, 1, 32, 32, enemyBullet, FALSE);

	int map = LoadGraph("map.png");
	int title = LoadGraph("TITLE.png");
	int manual = LoadGraph("manual.png");
	int manual2 = LoadGraph("taitle2.png");
	int manual3 = LoadGraph("taitle3.png");
	int gameclear = LoadGraph("gameclear.png");
	int gameover = LoadGraph("gameover.png");
	int Camel[3];
	LoadDivGraph("dron.png", 3, 3, 1, 64, 64, Camel);
	int Title_BGM;
	Title_BGM = LoadSoundMem("決戦へ_2.mp3");
	ChangeVolumeSoundMem(255 * 30 / 100, Title_BGM);
	int Game_BGM = LoadSoundMem("MusMus-BGM-122.mp3");
	ChangeVolumeSoundMem(255 * 20 / 100, Game_BGM);
	int Over_BGM = LoadSoundMem("ゲームオーバー.mp3");
	ChangeVolumeSoundMem(255 * 30 / 100, Over_BGM);
	int Clear_BGM = LoadSoundMem("レトロなゲームクリア音.mp3");
	ChangeVolumeSoundMem(255 * 30 / 100, Clear_BGM);
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

	int timer = 60;
	int timerFlag = 0;

	int HP;
	int MAP;

	int enemyAnimation[3] = { 100,100 ,100 };
	int enemyCount[3] = { 0 ,0,0 };

	int AnimetionTimer = 8;
	int AnimetionCount = 1;
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
			system_->Initialize();

			map_->Initialize();

			player_->Initialize();

			enemy_->Initialize();

			enemy2_->Initialize(WIN_HEIGHT, WIN_WIDTH);

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
				timer = 60;

				if (CheckSoundMem(Title_BGM) == 1) {
					StopSoundMem(Title_BGM);
				}
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
				timerFlag = 0;
				timer = 65;
				Scene = 2;
			}

			break;
		case 2://操作説明その２
			timer--;
			if (timer < 0) {
				timerFlag = 1;
			}

			if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0 && timerFlag == 1 ||
				key & PAD_INPUT_1 && timerFlag == 1)
			{

				Scene = 6;
				timerFlag = 0;
				timer = 60;

			}
			break;

		case 3://ゲーム
			map_->Update();

#pragma region アニメーション管理
			//--------------敵1-----------------//
			if (enemyAnimation[0] > 0)
			{
				enemyAnimation[0] -= 10;
			}
			if (enemyAnimation[0] <= 0 && enemyCount[0] < 6)
			{
				enemyCount[0] += 1;
				enemyAnimation[0] = 100;
				if (enemyCount[0] > 5)
				{
					enemyCount[0] = 0;
				}
			}
			//---------------敵2----------------//
			if (enemyAnimation[1] > 0)
			{
				enemyAnimation[1] -= 10;
			}
			if (enemyAnimation[1] <= 0 && enemyCount[1] < 3)
			{
				enemyCount[1] += 1;
				enemyAnimation[1] = 100;
				if (enemyCount[1] > 2)
				{
					enemyCount[1] = 0;
				}
			}
			//---------------敵弾-----------------//
			if (enemyAnimation[2] > 0)
			{
				enemyAnimation[2] -= 10;
			}
			if (enemyAnimation[2] <= 0 && enemyCount[2] < 3)
			{
				enemyCount[2] += 1;
				enemyAnimation[2] = 100;
				if (enemyCount[2] > 2)
				{
					enemyCount[2] = 0;
				}
			}
#pragma endregion


			system_->Update(player_->GetHP_X());

			player_->Update(keys, oldkeys, system_->GetgameTimer(), system_->Getcount(), map_->ScrollX);

			player_->Collision(enemy_->GetFlag(), enemy_->GetTranslation().x, enemy_->GetTranslation().y, enemy_->GetRadius());

			player_->Oncollision(enemy_->GetTranslation().x, enemy_->GetTranslation().y, enemy_->GetRadius(), enemy_->GetFlag(),
				enemy2_->translation.x, enemy2_->translation.y, enemy2_->radius, enemy2_->aliveFlag, enemy_->GetHP(), enemy2_->HP,WIN_WIDTH);
			enemy_->Update(player_->Gettrans_X(), player_->Gettrans_Y(), WIN_HEIGHT, WIN_WIDTH);

			enemy2_->Update(WIN_HEIGHT, WIN_WIDTH, player_->Gettrans_X(), player_->Gettrans_Y(), player_->GetRadius(), player_->GetFlag(), player_->GetHP_X());

			// 描画処理
			map_->Draw(floor, second, pillar);
			player_->Draw();
			enemy_->Draw(enemy[enemyCount[0]]);
			enemy2_->Draw(enemy2[enemyCount[1]], enemyBullet[enemyCount[2]]);

			HP = player_->GetHP_X();
			if (HP <= 10)
			{
				Scene = 5;
				if (CheckSoundMem(Game_BGM) == 1) {
					StopSoundMem(Game_BGM);
				}
			}
			MAP = map_->GetScrollX();
			if (MAP == 7680)
			{
				Scene = 4;
				if (CheckSoundMem(Game_BGM) == 1) {
					StopSoundMem(Game_BGM);
				}
			}
			break;


		case 4://ゲームクリア
			timer--;
			if (timer < 0) {
				timerFlag = 1;
			}
			if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0 && timerFlag == 1 ||
				key & PAD_INPUT_1 && timerFlag == 1)
			{
				Scene = 0;
				timerFlag = 0;
				timer = 120;
				StopSoundMem(Clear_BGM);
			}

			break;

		case 5://ゲームオーバー
			timer--;
			if (timer < 0) {
				timerFlag = 1;
			}

			if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0 && timerFlag == 1 ||
				key & PAD_INPUT_1 && timerFlag == 1)
			{
				Scene = 0;
				timerFlag = 0;
				timer = 120;
				StopSoundMem(Over_BGM);
			}
			break;
		case 6:
			timer--;
			if (timer < 0) {
				timerFlag = 1;
			}

			if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0 && timerFlag == 1 ||
				key & PAD_INPUT_1 && timerFlag == 1)
			{

				Scene = 3;
				timerFlag = 0;
				timer = 60;

			}
			break;
		}

		// 描画処理
		switch (Scene)
		{
		case 0://タイトル

			if (CheckSoundMem(Title_BGM) == 0) {
				PlaySoundMem(Title_BGM, DX_PLAYTYPE_BACK, true);
			}

			DrawGraph(0, 0, title, true);
			break;

		case 1://操作説明


			DrawGraph(0, 0, manual, true);
			break;

		case 2://操作説明その２
			DrawGraph(0, 0, manual2, true);
			break;
		case 3://ゲーム
			if (CheckSoundMem(Game_BGM) == 0) {
				PlaySoundMem(Game_BGM, DX_PLAYTYPE_BACK, true);
			}
			if (AnimetionTimer >= 0)
			{
				AnimetionTimer--;
			}
			if (AnimetionTimer <= 0)
			{
				AnimetionTimer = 8;
				AnimetionCount += 1;
				if (AnimetionCount > 2)
				{
					AnimetionCount = 0;
				}
			}

			player_->Draw();
			system_->Draw(player_->Gettrans_X(), player_->Gettrans_Y(), player_->GetHP_X());
			DrawGraph(79, 680, Camel[AnimetionCount], true);



			break;

		case 4://ゲームクリア
			DrawGraph(0, 0, gameclear, true);
			for (int i = 0; i < 7; i++)
			{
				DrawGraph(player_->posX + 32 * i, 0, player_->graphHandle[player_->eachnum[i]], true);
			}
			DrawGraph(550, 0, player_->score_notation, true);
			if (CheckSoundMem(Clear_BGM) == 0) {
				PlaySoundMem(Clear_BGM, DX_PLAYTYPE_BACK, true);
			}
			break;

		case 5://ゲームオーバー
			if (CheckSoundMem(Over_BGM) == 0) {
				PlaySoundMem(Over_BGM, DX_PLAYTYPE_BACK, true);
			}
			DrawGraph(0, 0, gameover, true);
			break;
		case 6:// 操作説明3
			DrawGraph(0, 0, manual3, true);
			break;
		}

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