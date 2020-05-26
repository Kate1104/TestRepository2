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
	//�\���̂̏�����
	enemy.moveDir = DIR_RIGHT;					//�����Ă������
	enemy.pos.x = { (PLAYER_SIZE_X) };
	enemy.pos.y = { (SCREEN_SIZE_Y - PLAYER_SIZE_Y) / 2 };
	enemy.size = { PLAYER_SIZE_X,PLAYER_SIZE_Y };							//�G�摜�̃T�C�Y					//�G�摜�̃T�C�Y
	enemy.offsetSize = { enemy.size.x ,enemy.size.y - 11 };	//�G��������̍���ʒu
	enemy.hitPosS = { 20,32 };								//�����蔻��p�̍���
	enemy.hitPosE = { 20,32 };								//�����蔻��p�̉E��
	enemy.animCnt = 0;							//�L�����N�^�̃A�j���[�V�����p�J�E���^
	enemy.imgLockCnt = 30;						//�L�����N�^�̃C���[�W�Œ�p�J�E���^
	enemy.velocity = { 0.0f , 0 };

	enemy.runFlag = false;						//�L�����N�^�̏�ԁi�����Ă��邩�H�j
	enemy.shotFlag = false;					//�L�����N�^�̏�ԁi�e�����Ă��邩�H�j
	enemy.damageFlag = false;					//�L�����N�^�̏�ԁi�_���[�W�󂯂Ă��邩�H�j

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