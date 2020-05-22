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

XY playerPosHit;				//�����̍��W
XY playerPosHitUp;
XY playerPosHitDown;

XY_F velocity0;			// �v���C���[�̏����x�i�[�̈�
XY_F velocity;			// �v���C���[�̑��x�i�[�̈�
float ptime;	// �v���C���[�̌o�ߎ��Ԋi�[�̈�


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

	// ���������^��
	velocity0.x = 0.0f;	// [m/s]
	velocity.x = velocity0.x;

	velocity0.y = 75.0f;	// [m/s]
	velocity.y = velocity0.x;

	ptime = 0;
}

void PlayerGameInit(void)
{
	//�\���̂̏�����
	player.moveDir = DIR_RIGHT;					//�����Ă������
	player.pos.x = { (PLAYER_SIZE_X) };
	player.pos.y = { (SCREEN_SIZE_Y - PLAYER_SIZE_Y) / 2 };
	player.size = { PLAYER_SIZE_X,PLAYER_SIZE_Y };							//�L�����N�^�摜�̃T�C�Y					//�L�����N�^�摜�̃T�C�Y
	player.offsetSize = { player.size.x+17 ,player.size.y  };	//�L�����N�^��������̍���ʒu
	player.hitPosS = { 20,16 };								//�����蔻��p�̍���
	player.hitPosE = { 20,32 };								//�����蔻��p�̉E��
	player.animCnt = 0;							//�L�����N�^�̃A�j���[�V�����p�J�E���^
	player.imgLockCnt = 30;						//�L�����N�^�̃C���[�W�Œ�p�J�E���^
	player.velocity = { 0.0f , 0 };

	player.runFlag = false;						//�L�����N�^�̏�ԁi�����Ă��邩�H�j
	player.shotFlag = false;					//�L�����N�^�̏�ԁi�e�����Ă��邩�H�j
	player.damageFlag = false;					//�L�����N�^�̏�ԁi�_���[�W�󂯂Ă��邩�H�j

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

	// �v���C���[�̃L�[����
	// ��
	if (keyNew[KEY_ID_LEFT])
	{
		player.moveDir = DIR_LEFT;
		moveFlag = true;
		player.runFlag = true;

	}

	// �E
	if (keyNew[KEY_ID_RIGHT])
	{
		player.moveDir = DIR_RIGHT;
		moveFlag = true;
		player.runFlag = true;
	}

	// �ړ�����(X���W)	�ړ��L�[�������Ă���Ƃ�
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

	//�L�[�������Ă��Ȃ��Ƃ��i���x�̌����j
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

		//���x���قƂ�ǂȂ��ꍇ(�덷)�͎~�߂�
		if (player.velocity.x < ACC_STOP && player.velocity.x > -ACC_STOP)player.velocity.x = 0;
	}

	//�W�����v----------------------------------------------------------------------------------------------------
		// �W�����v���̏���(Y���W)
	if (player.jumpFlag)
	{
		// ���x�̌v�Z
		player.velocity.y -= G * (FRAME_TIME * 1.5);

		// �����̌v�Z
		playerPosCopy.y -= player.velocity.y * (FRAME_TIME / 1.5);
		/*playerPosHit.y = playerPosCopy.y + player.hitPosE.y;*/

		//����Ƀu���b�N�����邩���`�F�b�N
		playerPosHit.y = playerPosCopy.y - player.hitPosS.x;
		playerPosHitUp = playerPosHit;
		playerPosHitUp.x -= player.hitPosS.x;
		playerPosHitDown = playerPosHit;
		playerPosHitDown.x += player.hitPosE.x;
		//�u���b�N�̂��肬��܂Ŋ炪�߂Â�
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

		//�����Ƀu���b�N�����邩�H
		playerPosHit.y = playerPosCopy.y + player.hitPosE.y;
		playerPosHitUp = playerPosHit;
		playerPosHitUp.x -= player.hitPosS.x;
		playerPosHitDown = playerPosHit;
		playerPosHitDown.x += player.hitPosE.x;

		// �W�����v�̏I�������o
		if (IsPass(playerPosHit)
			&& IsPass(playerPosHitUp)
			&& IsPass(playerPosHitDown))
		{
			player.pos.y = playerPosCopy.y;
		}
		else
		{
			//�W�����v�̏I���͑����̍��W����ʒu������o��
			//�u���b�N�Ƀv���C���[�������
			//�v���C���[�̑����̍��W = �u���b�N�̏�̖�
			blockPos = MapIndexToPos(MapPosToIndex(playerPosHit));
			player.pos.y = blockPos.y - player.hitPosE.y;

			player.jumpFlag = false;
			player.velocity.y = 0;

			// �W�����v
			if (keyNew[KEY_ID_UP])
			{
				player.jumpFlag = true;
				if (player.velocity.y == 0)player.velocity.y = INIT_VELOCITY;	//�����x��0�̎��̂ݏ����x����
			}
		}
	}


	//������
	playerPosCopy = player.pos;
	playerPosHit = playerPosCopy;

	//���ړ��̓����蔻��---------------------------------------------------------------------------------------------
	//�����蔻��
	if (player.velocity.x < 0)
	{
		playerPosCopy.x += player.velocity.x;
		playerPosHit.x = playerPosCopy.x - player.hitPosE.x;

		playerPosHitUp = playerPosHit;
		playerPosHitUp.y -= player.hitPosS.y;

		playerPosHitDown = playerPosHit;
		playerPosHitDown.y += player.hitPosE.y - 1;

		//�X�N���[��
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

		//�X�N���[��
		if (playerPosCopy.x - mapPos.x >= SCROLL_X_MAX)
		{
			if (player.velocity.x > VELOCITY_X_MAX)player.velocity.x = VELOCITY_X_MAX;
			mapPos.x += player.velocity.x;

			//�X�N���[�������@�E
			if (player.pos.x - mapPos.x > 200)	//�����𑪂�
			{
				mapPos.x += player.velocity.x;
			}
			//�X�N���[�������@��
			if (player.pos.x - mapPos.x < 150)	//�����𑪂�
			{
				mapPos.x -= player.velocity.x;
			}

			//�X�N���[�������@��
			if (player.pos.y + CHIP_SIZE_Y)	//�����𑪂�
			{
				mapPos.y += CHIP_SIZE_Y;
			}
			//�X�N���[�������@��
			if (player.pos.y - CHIP_SIZE_Y)	//�����𑪂�
			{
				mapPos.y -= CHIP_SIZE_Y;
			}
		}
	}

	// �ǂƂ̓����蔻��
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

	SetDrawBright(200, 200, 200); //���邭
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

	// �v���C���[�̃T�C�Y�g
	DrawBox(player.pos.x - player.offsetSize.x - mapPos.x
		, player.pos.y - player.offsetSize.y - mapPos.y
		, player.pos.x + player.offsetSize.x - mapPos.x
		, player.pos.y + player.offsetSize.y - mapPos.y
		, GetColor(255, 0, 0)
		, false);

		// �v���C���[�̓����蔻��g
		DrawBox(player.pos.x - player.hitPosS.x - mapPos.x
			, player.pos.y - player.hitPosS.y - mapPos.y
			, player.pos.x + player.hitPosE.x - mapPos.x
			, player.pos.y + player.hitPosE.y - mapPos.y
			, GetColor(255, 255, 255)
			, false);

	//DrawFormatString(0, 132, GetColor(0, 0, 0), "playerCounter, %d", playerCounter);
	player.animCnt++;

	SetDrawBright(255, 255, 255); //���邭
	DrawGraph(player.pos.x - player.offsetSize.x - mapPos.x
		, player.pos.y - player.offsetSize.y - mapPos.y
		, rightImage, true);

}