#include "DxLib.h"
#include "main.h"
#include "KeyCheck.h"
#include "player.h"
#include "stage.h"
#include "enemy.h"

CHARACTER enemyType[ENEMY_TYPE_MAX];
int enemySimage;	
int enemyMimage[1][4];

void EnemySystemInit(void)
{
	enemySimage = LoadGraph("image/estop.png");

	LoadDivGraph("image/emove.png", 4, 4, 1
		, ENEMY_SIZE_X, ENEMY_SIZE_Y
		, enemyMimage[ENEMY_ANI_MAX]);

}

void EnemyGameInit(void)
{
	//構造体の初期化
	enemyType[ENEMY_TYPE_BAT].moveDir = DIR_LEFT;	//向いている方向
	enemyType[ENEMY_TYPE_BAT].cherType = ENEMY_TYPE_BAT;
	enemyType[ENEMY_TYPE_BAT].pos.x = { ENEMY_SIZE_X * 2};
	enemyType[ENEMY_TYPE_BAT].pos.y = {(SCREEN_SIZE_Y - ENEMY_SIZE_Y) / 2};
	enemyType[ENEMY_TYPE_BAT].size = { ENEMY_SIZE_X, ENEMY_SIZE_Y };		//敵画像のサイズ
	enemyType[ENEMY_TYPE_BAT].moveSpeed = 2;
	enemyType[ENEMY_TYPE_BAT].lifeMax = 5;
	enemyType[ENEMY_TYPE_BAT].point = 5;
	enemyType[ENEMY_TYPE_BAT].imgLockCnt = 30;

	enemyType[ENEMY_TYPE_BAT].runFlag = false;
	enemyType[ENEMY_TYPE_BAT].shotFlag = false;
}

bool EnemyHitCheck(void)
{
	return true;
}

void EnemyControl(void)
{
	bool moveFlag;
	moveFlag = false;

	for (int i = 0; i < ENEMY_TYPE_MAX; i++)
	{

		enemyType[i].runFlag = false;
		enemyType[i].shotFlag = false;

		//敵の動き
		if (player.pos.x - enemyType[i].pos.x > 100)
		{
			enemyType[i].moveDir = DIR_LEFT;
			moveFlag = true;
			enemyType[i].runFlag = true;
		}

	}
}

void EnemyDraw(void)
{
	for (int i = 0; i < ENEMY_TYPE_MAX; i++)
	{
		enemyType[i].animCnt++;

		if (player.pos.x - enemyType[i].pos.x > 100)
		{
			/*DrawGraph(enemyType[i].pos.x - enemyType[i].offsetSize.x - mapPos.x
				, enemyType[i].pos.y - enemyType[i].offsetSize.y - mapPos.y
				, enemyMimage[enemyType[ENEMY_TYPE_BAT].cherType][(enemyType[ENEMY_TYPE_BAT].animCnt / 10) % 4], true);*/

			DrawGraph(550 - mapPos.x
				, SCREEN_SIZE_Y / 2 - 64 - mapPos.y
				, enemyMimage[enemyType[ENEMY_TYPE_BAT].cherType][(enemyType[ENEMY_TYPE_BAT].animCnt / 10) % 4], true);
		}
		else
		{
			DrawGraph(350 - mapPos.x, SCREEN_SIZE_Y / 2 - 64 - mapPos.y, enemySimage, true);
		}
	}

	// プレイヤーのサイズ枠
	DrawBox(enemyType[ENEMY_TYPE_BAT].pos.x - enemyType[ENEMY_TYPE_BAT].offsetSize.x - mapPos.x
		, enemyType[ENEMY_TYPE_BAT].pos.y - enemyType[ENEMY_TYPE_BAT].offsetSize.y - mapPos.y
		, enemyType[ENEMY_TYPE_BAT].pos.x + enemyType[ENEMY_TYPE_BAT].offsetSize.x - mapPos.x
		, enemyType[ENEMY_TYPE_BAT].pos.y + enemyType[ENEMY_TYPE_BAT].offsetSize.y - mapPos.y
		, GetColor(255, 0, 0)
		, false);

	// プレイヤーの当たり判定枠
	DrawBox(enemyType[ENEMY_TYPE_BAT].pos.x - enemyType[ENEMY_TYPE_BAT].hitPosS.x - mapPos.x
		, enemyType[ENEMY_TYPE_BAT].pos.y - enemyType[ENEMY_TYPE_BAT].hitPosS.y - mapPos.y
		, enemyType[ENEMY_TYPE_BAT].pos.x + enemyType[ENEMY_TYPE_BAT].hitPosE.x - mapPos.x
		, enemyType[ENEMY_TYPE_BAT].pos.y + enemyType[ENEMY_TYPE_BAT].hitPosE.y - mapPos.y
		, GetColor(255, 255, 255)
		, false);

	DrawFormatString(0, 64, GetColor(255, 255, 255), "enemyPos : (%d , %d)", enemyType[ENEMY_TYPE_BAT].pos);
}