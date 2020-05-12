#include "DxLib.h"
#include "main.h"
#include "KeyCheck.h"
#include "player.h"

XY_F playerPos;			// プレイヤーの位置格納領域
XY_F velocity0;			// プレイヤーの初速度格納領域
XY_F velocity;			// プレイヤーの速度格納領域
POS mapPos;
bool runFlag;			// 実行フラグ
float ptime;			// プレイヤーの経過時間格納領域

void PlayerSystemInit(void)
{
	mapPos.x = 0;
	mapPos.y = 0;
	runFlag = false;

	// 等速直線運動
	velocity0.x = 0.0f;	// [m/s]
	velocity.x = velocity0.x;

	velocity0.y = 75.0f;	// [m/s]
	velocity.y = velocity0.x;
}

void PlayerGameInit(void)
{
	playerPos.x = (SCREEN_SIZE_X - PLAYER_SIZE_X) / 2;
	playerPos.y = (SCREEN_SIZE_Y - PLAYER_SIZE_Y) / 2;
	
}

bool PlayerHitCheck(void)
{
	return true;
}

void PlayerControl(void)
{
	// 等速直線運動
	if (CheckHitKey(KEY_INPUT_UP))
	{
		runFlag = true;
	}

	bool movedFlag = false;

	//キーを押しているとき
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		velocity.x += 1;
		movedFlag = true;
	}
	if (velocity.x > 10) velocity.x = 10;

	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		velocity.x -= 1;
		movedFlag = true;
	}
	if (velocity.x < -10) velocity.x = -10;

	//キーを押していないとき（速度の減速）
	if (!movedFlag)
	{
		if (velocity.x < 0)
		{
			velocity.x += 3;
		}
		else if (velocity.x > 0)
		{
			velocity.x -= 3;
		}

		//速度がほとんどない場合(誤差)は止める
		if (velocity.x > -2 && velocity.x < 2)
		{
			velocity.x = 0;
		}
	}

	playerPos.x += velocity.x * FRAME_TIME;

	// 実行
	if (runFlag)
	{
		//ジャンプ--------------------------------------------------------------------------------------------
		//速度の計算
		velocity.y -= G * (FRAME_TIME * 1.5);

		//距離の計算
		playerPos.y -= velocity.y * (FRAME_TIME / 1.5);

		if (playerPos.y > 300)
		{
			runFlag = false;
			velocity.y = velocity0.y;
			playerPos.y = 300;
		}
	}

	//移動
	if (CheckHitKey(KEY_INPUT_LEFT)) playerPos.x -= 4;
	if (CheckHitKey(KEY_INPUT_RIGHT)) playerPos.x += 4;
	/*if (CheckHitKey(KEY_INPUT_UP)) player1Pos.y -= 4;
	if (CheckHitKey(KEY_INPUT_DOWN)) player1Pos.y += 4;*/


}

void PlayerDraw(void)
{
	DrawCircle((-mapPos.x + playerPos.x), (-mapPos.y + playerPos.y) , PLAYER_SIZE_X, GetColor(255, 255, 255), true);
}