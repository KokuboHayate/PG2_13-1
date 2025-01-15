#include <Novice.h>
#include <math.h>
#include "Enemy.h"

const char kWindowTitle[] = "GC1A_06_コクボ_ハヤテ_Title";

int Enemy::isAlive;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	//敵
	Enemy* enemyA = new Enemy({250.0f,150.0f});
	Enemy* enemyB = new Enemy({500.0f,450.0f});

	//プレイヤー
	struct Player
	{
		Vector2 pos;
		int speed;
		float radius;
	};
	Player player = {
		{640.0f,500.0f},
		10,
		40.0f
	};

	//弾
	struct Shot
	{
		Vector2 pos;
		int speed;
		float radius;
		bool isAlive;
	};
	Shot shot[10];
	for (int i = 0; i < 10; i++) {
		shot[i] = {
			{-10.0f,-10.0f},
			8,
			15.0f,
			false
		};
	}

	//当たり判定用
	float distanceX = 0.0f;
	float distanceY = 0.0f;
	float distance = 0.0f;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		///キー入力///
		if (keys[DIK_W]) {
			player.pos.y -= player.speed;
		}
		if (keys[DIK_S]) {
			player.pos.y += player.speed;
		}
		if (keys[DIK_A]) {
			player.pos.x -= player.speed;
		}
		if (keys[DIK_D]) {
			player.pos.x += player.speed;
		}
		if (Enemy::isAlive == false) {
			if (keys[DIK_R]) {
				Enemy::isAlive = true;
			}
		}
		if (preKeys[DIK_SPACE] == 0 && keys[DIK_SPACE] != 0) {
			for (int i = 0; i < 10; i++) {
				if (shot[i].isAlive == false) {
					shot[i].pos.x = player.pos.x;
					shot[i].pos.y = player.pos.y;
					shot[i].isAlive = true;
					break;
				}
			}
		}
		//////////////
		
		///オブジェクトの動き///
		enemyA->Move();
		enemyB->Move();

		for (int i = 0; i < 10; i++) {
			if (shot[i].isAlive) {
				shot[i].pos.y -= shot[i].speed;
				if (shot[i].pos.y < -shot[i].radius) {
					shot[i].pos = { -10.0f,-10.0f };
					shot[i].isAlive = false;
				}
			}
		}
		/////////////////////////

		///当たり判定///
		for (int i = 0; i < 10; i++) {
			if (shot[i].isAlive) {
				if (enemyA->isAlive) {
					distanceX = shot[i].pos.x - enemyA->pos_.x;
					distanceY = shot[i].pos.y - enemyA->pos_.y;
					distance = sqrtf(distanceX * distanceX + distanceY * distanceY);
					if (distance <= shot[i].radius + enemyA->radius_) {
						enemyA->isAlive = false;
					}
				}
				if (enemyB->isAlive) {
					distanceX = shot[i].pos.x - enemyB->pos_.x;
					distanceY = shot[i].pos.y - enemyB->pos_.y;
					distance = sqrtf(distanceX * distanceX + distanceY * distanceY);
					if (distance <= shot[i].radius + enemyB->radius_) {
						enemyB->isAlive = false;
					}
				}
			}
		}
		////////////////


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		//敵
		enemyA->Draw();
		enemyB->Draw();

		//自機
		Novice::DrawEllipse(static_cast<int>(player.pos.x), static_cast<int>(player.pos.y),
			static_cast<int>(player.radius), static_cast<int>(player.radius), 0.0f, GREEN, kFillModeSolid);

		//弾
		for (int i = 0; i < 10; i++) {
			if (shot[i].isAlive) {
				Novice::DrawEllipse(static_cast<int>(shot[i].pos.x), static_cast<int>(shot[i].pos.y),
					static_cast<int>(shot[i].radius), static_cast<int>(shot[i].radius), 0.0f, WHITE, kFillModeSolid);
			}
		}

		//操作説明
		Novice::ScreenPrintf(0, 0, "enemyA isAlive = %d", enemyA->isAlive);
		Novice::ScreenPrintf(0, 20, "enemyB isAlive = %d", enemyB->isAlive);
		Novice::ScreenPrintf(0, 40, "WASD : player Move");
		Novice::ScreenPrintf(0, 60, "shot : SPACE");
		Novice::ScreenPrintf(0, 80, "enemy respawn : R");

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
