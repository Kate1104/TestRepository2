#include "DxLib.h"
#include "main.h"
#include "KeyCheck.h"
#include "player.h"
#include "stage.h"

CHARACTER player;
int plStopImage[2];
int plRunImage[2][4];
int plJumpImage[2];
int rightImage;

XY blockPos;

XY playerPosHit;				//足元の座標
XY playerPosHitUp;
XY playerPosHitDown;

XY_F velocity0;			// プレイヤーの初速度格納領域
XY_F velocity;			// プレイヤーの速度格納領域
float ptime;	// プレイヤーの経過時間格納領域


void PlayerSystemInit(void)
{
	plStopImage[NOMAL_INDEX] = LoadGraph("image/stop.png");
	plStopImage[SHOT_INDEX] = LoadGraph("image/stop_shot.png");

	plJumpImage[NOMAL_INDEX] = LoadGraph("image/jump.png");

	LoadDivGraph("image/run.png", 4, 4, 1
		, PLAYER_SIZE_X, PLAYER_SIZE_Y
		, plRunImage[NOMAL_INDEX]);

	LoadDivGraph("image/run_shot.png", 4, 4, 1
		, PLAYER_SIZE_X, PLAYER_SIZE_Y
		, plRunImage[SHOT_INDEX]);

	rightImage = LoadGraph("image/right.png");

	// 等速直線運動
	velocity0.x = 0.0f;	// [m/s]
	velocity.x = velocity0.x;

	velocity0.y = 75.0f;	// [m/s]
	velocity.y = velocity0.x;

	ptime = 0;
}

void PlayerGameInit(void)
{
	//構造体の初期化
	player.moveDir = DIR_RIGHT;					//向いている方向
	player.pos.x = { (PLAYER_SIZE_X) };
	player.pos.y = { (SCREEN_SIZE_Y - PLAYER_SIZE_Y) / 2 };
	player.size = { PLAYER_SIZE_X,PLAYER_SIZE_Y };							//キャラクタ画像のサイズ					//キャラクタ画像のサイズ
	player.offsetSize = { player.size.x+17 ,player.size.y  };	//キャラクタ中央からの左上位置
	player.hitPosS = { 20,16 };								//当たり判定用の左上
	player.hitPosE = { 20,32 };								//当たり判定用の右下
	player.animCnt = 0;							//キャラクタのアニメーション用カウンタ
	player.imgLockCnt = 30;						//キャラクタのイメージ固定用カウンタ
	player.velocity = { 0.0f , 0 };

	player.runFlag = false;						//キャラクタの状態（走っているか？）
	player.shotFlag = false;					//キャラクタの状態（弾撃っているか？）
	player.damageFlag = false;					//キャラクタの状態（ダメージ受けているか？）

	blockPos = { 0,0 };
}


void PlayerControl(void)
{
	bool moveFlag = false;
	player.runFlag = false;
	player.shotFlag = false;
	player.jumpFlag = true;

	XY playerPosCopy = player.pos;
	XY playerPosOffset = playerPosCopy;

	playerPosHit = playerPosCopy;
	playerPosHitUp = player.pos;
	playerPosHitDown = player.pos;

	player.imgLockCnt++;

	// プレイヤーのキー操作
	// 左
	if (keyNew[KEY_ID_LEFT])
	{
		player.moveDir = DIR_LEFT;
		moveFlag = true;
		player.runFlag = true;

	}

	// 右
	if (keyNew[KEY_ID_RIGHT])
	{
		player.moveDir = DIR_RIGHT;
		moveFlag = true;
		player.runFlag = true;
	}

	// 移動処理(X座標)	移動キーを押しているとき
	if (moveFlag)
	{
		if (player.moveDir == DIR_LEFT)
		{
			player.velocity.x = -VELOCITY_X_MAX;
			/*player.velocity.x -= ACC_RUN;*/
		}

		if (player.moveDir == DIR_RIGHT)
		{
			player.velocity.x = VELOCITY_X_MAX;
			/*player.velocity.x += ACC_RUN;*/
		}

	}

	//キーを押していないとき（速度の減速）
	else /*if (moveFlag == false)*/
	{
		if (player.velocity.x > 0)
		{
			player.velocity.x = 0;
		}
		else if (player.velocity.x < 0)
		{
			player.velocity.x = 0;
		}

		//速度がほとんどない場合(誤差)は止める
		if (player.velocity.x < ACC_STOP && player.velocity.x > -ACC_STOP)player.velocity.x = 0;
	}

	//ジャンプ----------------------------------------------------------------------------------------------------
		// ジャンプ中の処理(Y座標)
	if (player.jumpFlag)
	{
		// 速度の計算
		player.velocity.y -= G * (FRAME_TIME * 1.5);

		// 距離の計算
		playerPosCopy.y -= player.velocity.y * (FRAME_TIME / 1.5);
		/*playerPosHit.y = playerPosCopy.y + player.hitPosE.y;*/

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

		// ジャンプの終了を検出
		if (IsPass(playerPosHit)
			&& IsPass(playerPosHitUp)
			&& IsPass(playerPosHitDown))
		{
			player.pos.y = playerPosCopy.y;
		}
		else
		{
			//ジャンプの終了は足元の座標から位置を割り出す
			//ブロックにプレイヤーが乗った
			//プレイヤーの足元の座標 = ブロックの上の面
			blockPos = MapIndexToPos(MapPosToIndex(playerPosHit));
			player.pos.y = blockPos.y - player.hitPosE.y;

			player.jumpFlag = false;
			player.velocity.y = 0;

			// ジャンプ
			if (keyNew[KEY_ID_UP])
			{
				player.jumpFlag = true;
				if (player.velocity.y == 0)player.velocity.y = INIT_VELOCITY;	//初速度が0の時のみ初速度を代入
			}
		}
	}


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

		if (playerPosCopy.y - mapPos.y <= SCROLL_Y_MIN)
		{
			if (player.velocity.y < -VELOCITY_X_MAX)player.velocity.y = -VELOCITY_X_MAX;
			mapPos.y += player.velocity.y;
		}
	}

	else if (player.velocity.x > 0)
	{
		playerPosCopy.x += player.velocity.x;
		playerPosHit.x = playerPosCopy.x + player.hitPosE.x;

		playerPosHitUp = playerPosHit;
		playerPosHitUp.y -= player.hitPosS.y;

		playerPosHitDown = playerPosHit;
		playerPosHitDown.y += player.hitPosE.y - 1;

		//スクロール
		if (playerPosCopy.x - mapPos.x >= SCROLL_X_MAX)
		{
			if (player.velocity.x > VELOCITY_X_MAX)player.velocity.x = VELOCITY_X_MAX;
			mapPos.x += player.velocity.x;

			//スクロール制限　右
			if (player.pos.x - mapPos.x > 200)	//距離を測る
			{
				mapPos.x += player.velocity.x;
			}
			//スクロール制限　左
			if (player.pos.x - mapPos.x < 150)	//距離を測る
			{
				mapPos.x -= player.velocity.x;
			}

			//スクロール制限　上
			if (player.pos.y + CHIP_SIZE_Y)	//距離を測る
			{
				mapPos.y += CHIP_SIZE_Y;
			}
			//スクロール制限　下
			if (player.pos.y - CHIP_SIZE_Y)	//距離を測る
			{
				mapPos.y -= CHIP_SIZE_Y;
			}
		}
	}

	// 壁との当たり判定
	if (IsPass(playerPosHit)
		&& IsPass(playerPosHitUp)
		&& IsPass(playerPosHitDown))
	{
		player.pos.x = playerPosCopy.x;
	}
	else
	{
		player.velocity.x = 0;
	}

	if (mapPos.x < 0)
	{
		mapPos.x = 0;
	}
	if (mapPos.x > (CHIP_SIZE_X * MAP_X) - SCREEN_SIZE_X)
	{
		mapPos.x = (CHIP_SIZE_X * MAP_X) - SCREEN_SIZE_X;
	}

	if (mapPos.y < 0)
	{
		mapPos.y = 0;
	}
	if (mapPos.y > (CHIP_SIZE_Y * MAP_Y) - SCREEN_SIZE_Y)
	{
		mapPos.y = (CHIP_SIZE_Y * MAP_Y) - SCREEN_SIZE_Y;
	}
}

bool PlayerHitCheck(XY sPos, int sSise)
{
	return true;
}

void PlayerDraw(void)
{
	int playerImage;
	int playerShotStatus;

	playerShotStatus = (player.imgLockCnt < SHOT_IMGLOCK) ? SHOT_INDEX : NOMAL_INDEX;

	playerImage = plStopImage[playerShotStatus];

	if (player.runFlag) playerImage = plRunImage[playerShotStatus][player.animCnt / 10 % 4];
	if (player.jumpFlag) playerImage = plJumpImage[playerShotStatus];

	DrawFormatString(0, 32, GetColor(255, 255, 255), "playerPos : (%d , %d)", player.pos);
	DrawFormatString(0, 100, GetColor(255, 255, 255), "mapPos: (%d , %d)", mapPos);

	SetDrawBright(200, 200, 200); //明るく
	if (player.moveDir == DIR_LEFT)
	{
		DrawTurnGraph(player.pos.x - player.offsetSize.x - mapPos.x
			, player.pos.y - player.offsetSize.y - mapPos.y
			, playerImage, true);
	}
	else
	{
		DrawGraph(player.pos.x - player.offsetSize.x - mapPos.x
			, player.pos.y - player.offsetSize.y - mapPos.y
			, playerImage, true);
	}

	// プレイヤーのサイズ枠
	DrawBox(player.pos.x - player.offsetSize.x - mapPos.x
		, player.pos.y - player.offsetSize.y - mapPos.y
		, player.pos.x + player.offsetSize.x - mapPos.x
		, player.pos.y + player.offsetSize.y - mapPos.y
		, GetColor(255, 0, 0)
		, false);

		// プレイヤーの当たり判定枠
		DrawBox(player.pos.x - player.hitPosS.x - mapPos.x
			, player.pos.y - player.hitPosS.y - mapPos.y
			, player.pos.x + player.hitPosE.x - mapPos.x
			, player.pos.y + player.hitPosE.y - mapPos.y
			, GetColor(255, 255, 255)
			, false);

	//DrawFormatString(0, 132, GetColor(0, 0, 0), "playerCounter, %d", playerCounter);
	player.animCnt++;

	SetDrawBright(255, 255, 255); //明るく
	DrawGraph(player.pos.x - player.offsetSize.x - mapPos.x
		, player.pos.y - player.offsetSize.y - mapPos.y
		, rightImage, true);

}