#include "DxLib.h"
#include "main.h"
#include "KeyCheck.h"
#include "player.h"

XY_F playerPos;			// �v���C���[�̈ʒu�i�[�̈�
XY_F velocity0;			// �v���C���[�̏����x�i�[�̈�
XY_F velocity;			// �v���C���[�̑��x�i�[�̈�
POS mapPos;
bool runFlag;			// ���s�t���O
float ptime;			// �v���C���[�̌o�ߎ��Ԋi�[�̈�

void PlayerSystemInit(void)
{
	mapPos.x = 0;
	mapPos.y = 0;
	runFlag = false;

	// ���������^��
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
	// ���������^��
	if (CheckHitKey(KEY_INPUT_UP))
	{
		runFlag = true;
	}

	bool movedFlag = false;

	//�L�[�������Ă���Ƃ�
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

	//�L�[�������Ă��Ȃ��Ƃ��i���x�̌����j
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

		//���x���قƂ�ǂȂ��ꍇ(�덷)�͎~�߂�
		if (velocity.x > -2 && velocity.x < 2)
		{
			velocity.x = 0;
		}
	}

	playerPos.x += velocity.x * FRAME_TIME;

	// ���s
	if (runFlag)
	{
		//�W�����v--------------------------------------------------------------------------------------------
		//���x�̌v�Z
		velocity.y -= G * (FRAME_TIME * 1.5);

		//�����̌v�Z
		playerPos.y -= velocity.y * (FRAME_TIME / 1.5);

		if (playerPos.y > 300)
		{
			runFlag = false;
			velocity.y = velocity0.y;
			playerPos.y = 300;
		}
	}

	//�ړ�
	if (CheckHitKey(KEY_INPUT_LEFT)) playerPos.x -= 4;
	if (CheckHitKey(KEY_INPUT_RIGHT)) playerPos.x += 4;
	/*if (CheckHitKey(KEY_INPUT_UP)) player1Pos.y -= 4;
	if (CheckHitKey(KEY_INPUT_DOWN)) player1Pos.y += 4;*/


}

void PlayerDraw(void)
{
	DrawCircle((-mapPos.x + playerPos.x), (-mapPos.y + playerPos.y) , PLAYER_SIZE_X, GetColor(255, 255, 255), true);
}