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

	for (int i = 0; i < ENEMY_TYPE_MAX; i++)
	{

		enemyType[i].runFlag = false;
		enemyType[i].shotFlag = false;

		enemyType[i].imgLockCnt++;

		//敵の動き
		if (player.pos.x - enemyType[i].pos.x < 100)
		{
			enemyType[i].moveDir = DIR_LEFT;
			moveFlag = true;
			enemyType[i].runFlag = true;
		}

	}
}

void EnemyGameDrawOrder(int index)
{
	enemyType[index].animCnt++;

	if (enemyType[index].runFlag)
	{
		DrawGraph(enemyType[index].pos.x - enemyType[index].offsetSize.x - mapPos.x
			, enemyType[index].pos.y - enemyType[index].offsetSize.y - mapPos.y
			, enemyMimage[1][index], true);
	}
	else
	{
		DrawGraph(232, SCREEN_SIZE_Y / 2 - 64, enemySimage, true);
	}
}

void EnemyDraw(void)
{
	
}