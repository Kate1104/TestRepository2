//#pragma once
#define ENEMY_SIZE_X 32
#define ENEMY_SIZE_Y 32
#define ENEMY_ANI_MAX 4

// �v���g�^�C�v�錾
//------------------------------------------------------------------
void EnemySystemInit(void);					//SystemInit�ɑ}��
void EnemyGameInit(void);					//�@InitScene
bool EnemyHitCheck(void);
void EnemyControl(void);					//�@Game
void EnemyDraw(void);						//�@GameDraw