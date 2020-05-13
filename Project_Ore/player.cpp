#include "DxLib.h"
#include "main.h"
#include "KeyCheck.h"
#include "player.h"
#include "stage.h"

CHARACTER player;

XY blockPos;

XY playerPosHit;				//足元の座標
XY playerPosHitUp;
XY playerPosHitDown;

XY_F velocity0;			// プレイヤーの初速度格納領域
XY_F velocity;			// プレイヤーの速度格納領域
bool runFlag;			// 実行フラグ
float ptime;			// プレイヤーの経過時間格納領域

void PlayerSystemInit(void)
{
	runFlag = false;

	// 等速直線運動
	velocity0.x = 0.0f;	// [m/s]
	velocity.x = velocity0.x;

	velocity0.y = 75.0f;	// [m/s]
	velocity.y = velocity0.x;
}

void PlayerGameInit(void)
{
	player.pos.x = { (PLAYER_SIZE_X) };
	player.pos.y = { (SCREEN_SIZE_Y - PLAYER_SIZE_Y) / 2 };
	player.velocity = { 0.0f , 0 };

	player.runFlag = false;						//キャラクタの状態（走っているか？）
	player.shotFlag = false;					//キャラクタの状態（弾撃っているか？）
	player.damageFlag = false;					//キャラクタの状態（ダメージ受けているか？）
	
}

bool PlayerHitCheck(void)
{
	return true;
}

void PlayerControl(void)
{
	XY playerPosCopy = player.pos;
	XY playerPosOffset = playerPosCopy;

	playerPosHit = playerPosCopy;
	playerPosHitUp = player.pos;
	playerPosHitDown = player.pos;

	player.imgLockCnt++;

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

	player.pos.x += velocity.x * FRAME_TIME;

	// 実行
	if (runFlag)
	{
		//ジャンプ--------------------------------------------------------------------------------------------
		//速度の計算
		velocity.y -= G * (FRAME_TIME * 1.5);

		//距離の計算
		player.pos.y -= velocity.y * (FRAME_TIME / 1.5);

		if (player.pos.y > 300)
		{
			runFlag = false;
			velocity.y = velocity0.y;
			player.pos.y = 300;
		}
	}

	//移動
	if (keyNew[KEY_ID_LEFT]) player.pos.x -= 4;
	if (keyNew[KEY_ID_RIGHT]) player.pos.x += 4;

	//スクロール
	/*if (playerPosCopy.x - mapPos.x <= SCROLL_X_MIN)
	{
		if (player.velocity.x < -VELOCITY_X_MAX)player.velocity.x = -VELOCITY_X_MAX;
		mapPos.x += player.velocity.x;
	}*/

	//頭上にブロックがあるかをチェック
	playerPosHit.y = playerPosCopy.y - player.hitPosS.x;
	playerPosHitUp = playerPosHit;
	playerPosHitUp.x -= player.hitPosS.x;
	playerPosHitDown = playerPosHit;
	playerPosHitDown.x += player.hitPosE.x;
	//ブロックのぎりぎりまで顔が近づく
	if (!IsPass(playerPosHit)
		|| !IsPass(playerPosHitUp)
		|| !IsPass(playerPosHitDown))
	{
		player.pos.y = playerPosCopy.y;
		blockPos = MapIndexToPos(MapPosToIndex(playerPosHit));
		blockPos.y = blockPos.y + CHIP_SIZE_Y;
		playerPosCopy.y = blockPos.y + player.hitPosS.y;
		player.velocity.y = -1 * player.velocity.y;
	}

	//足元にブロックがあるか？
	playerPosHit.y = playerPosCopy.y + player.hitPosE.y;
	playerPosHitUp = playerPosHit;
	playerPosHitUp.x -= player.hitPosS.x;
	playerPosHitDown = playerPosHit;
	playerPosHitDown.x += player.hitPosE.x;

	//初期化
	playerPosCopy = player.pos;
	playerPosHit = playerPosCopy;

	//横移動の当たり判定---------------------------------------------------------------------------------------------
	//当たり判定
	if (player.velocity.x < 0)
	{
		playerPosCopy.x += player.velocity.x;
		playerPosHit.x = playerPosCopy.x - player.hitPosE.x;

		playerPosHitUp = playerPosHit;
		playerPosHitUp.y -= player.hitPosS.y;

		playerPosHitDown = playerPosHit;
		playerPosHitDown.y += player.hitPosE.y - 1;

		//スクロール
		if (playerPosCopy.x - mapPos.x <= SCROLL_X_MIN)
		{
			if (player.velocity.x < -VELOCITY_X_MAX)player.velocity.x = -VELOCITY_X_MAX;
			mapPos.x += player.velocity.x;
		}
	}

	if (playerPosCopy.x - mapPos.x >= SCROLL_X_MAX)
	{
		if (player.velocity.x > VELOCITY_X_MAX)player.velocity.x = VELOCITY_X_MAX;
		mapPos.x += player.velocity.x;

		//スクロール制限　右
		if (player.pos.x - mapPos.x > 200)
		{
			mapPos.x += 4;
			/*if (player.pos.x > 999)player.velocity.x = 0;*/

			//スクロール制限　左
			if (player.pos.x - mapPos.x < 150)
			{
				mapPos.x -= 4;
				/*if (500 - player.pos.x > 600)player.velocity.x = 0;*/
			}
		}
		
		if (mapPos.x < 0)
		{
			mapPos.x = 0;
		}
		if (mapPos.x > (CHIP_SIZE_X * MAP_X) - SCREEN_SIZE_X)
		{
			mapPos.x = (CHIP_SIZE_X * MAP_X) - SCREEN_SIZE_X;
		}

		//// 壁との当たり判定
		//if (IsPass(playerPosHit)
		//	&& IsPass(playerPosHitUp)
		//	&& IsPass(playerPosHitDown))
		//{
		//	player.pos.x = playerPosCopy.x;
		//}
		//else
		//{
		//	player.velocity.x = 0;
		//}

	}
	/*if (CheckHitKey(KEY_INPUT_UP)) playerPos.y -= 4;
	if (CheckHitKey(KEY_INPUT_DOWN)) playerPos.y += 4;*/


}

void PlayerDraw(void)
{
	DrawCircle((-mapPos.x + player.pos.x), (-mapPos.y + player.pos.y) , PLAYER_SIZE_X, GetColor(255, 255, 255), true);
	DrawFormatString(0, 32, GetColor(255, 255, 255), "playerPos : (%d , %d)", player.pos);
	DrawFormatString(0, 50, GetColor(255, 255, 255), "mapPos: (%d , %d)", mapPos);
}