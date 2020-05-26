#include "DxLib.h"
#include "main.h"
#include "KeyCheck.h"
#include "player.h"
#include "stage.h"
#include "enemy.h"

CHARACTER enemy;
int enemySimage;	
int enemyMimage[4];

void EnemySystemInit(void)
{
	enemySimage = LoadGraph("image/estop.png");

	LoadDivGraph("image/emove.png", 4, 4, 1
			, ENEMY_SIZE_X, ENEMY_SIZE_Y
			, enemyMimage[0]);
}

void EnemyGameInit(void)
{
	//構造体の初期化
	enemy.moveDir = DIR_RIGHT;					//向いている方向
	enemy.pos.x = { (PLAYER_SIZE_X) };
	enemy.pos.y = { (SCREEN_SIZE_Y - PLAYER_SIZE_Y) / 2 };
	enemy.size = { PLAYER_SIZE_X,PLAYER_SIZE_Y };							//敵画像のサイズ					//敵画像のサイズ
	enemy.offsetSize = { enemy.size.x ,enemy.size.y - 11 };	//敵中央からの左上位置
	enemy.hitPosS = { 20,32 };								//当たり判定用の左上
	enemy.hitPosE = { 20,32 };								//当たり判定用の右下
	enemy.animCnt = 0;							//キャラクタのアニメーション用カウンタ
	enemy.imgLockCnt = 30;						//キャラクタのイメージ固定用カウンタ
	enemy.velocity = { 0.0f , 0 };

	enemy.runFlag = false;						//キャラクタの状態（走っているか？）
	enemy.shotFlag = false;					//キャラクタの状態（弾撃っているか？）
	enemy.damageFlag = false;					//キャラクタの状態（ダメージ受けているか？）

}

bool EnemyHitCheck(void)
{

}

void EnemyControl(void)
{

}

void EnemyDraw(void)
{

}