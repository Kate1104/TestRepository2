#include "DxLib.h"
#include "main.h"
#include "Effect.h"
#include "KeyCheck.h"
#include "player.h"
#include "stage.h"


// �ϐ�
//-------------------------------------------------------------
// �V�[���Ǘ��p
int gameCounter;		// gameLoop����m�F�p
int sceneCounter;		// �V�[���J�E���^�[
SCENE_ID sceneID;
SCENE_ID preSceneID;

// WinMain�֐�
//-------------------------------------------------------------
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// �V�X�e���̏�����
	if (!SystemInit())
	{
		return -1;
	}

	int Screen = MakeScreen(SCREEN_SIZE_X, SCREEN_SIZE_Y);

	// �Q�[�����[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClsDrawScreen();

		// �V�[���J�E���^�𐧌�
		if (sceneID != preSceneID)
		{
			preSceneID = sceneID;
			sceneCounter = 0;
		}


		// ���͏��̎擾
		KeyCheck();


		// �V�[���I��
		switch (sceneID)
		{
			// �������V�[��
		case SCENE_ID_INIT:
			InitScene();
			break;

			// �^�C�g���V�[��
		case SCENE_ID_TITLE:
			// ��ʐ؂�ւ��G�t�F�N�g
			if (fadeIn)
			{
				if (!FadeInScreen(5))
				{
					// �G�t�F�N�g�I����̏���
				}
			}
			else if (fadeOut)
			{
				if (!FadeOutScreen(5))
				{
					// �G�t�F�N�g�I����̏���
					sceneID = SCENE_ID_GAME;
					fadeIn = true;
					//SetDrawBright(255, 255, 255);
				}
			}
			TitleScene();
			break;

			// �Q�[���V�[��
		case SCENE_ID_GAME:
			// ��ʐ؂�ւ��G�t�F�N�g
			if (fadeIn)
			{
				if (!FadeInScreen(5))
				{
					// �G�t�F�N�g�I����̏���
				}
			}
			else if (fadeOut)
			{
				if (!FadeOutScreen(5))
				{
					// �G�t�F�N�g�I����̏���
					sceneID = SCENE_ID_GAMEOVER;
					fadeIn = true;
					//SetDrawBright(255, 255, 255);
				}
			}
			GameScene();
			break;

			// �Q�[���I�[�o�[�V�[��
		case SCENE_ID_GAMEOVER:
			// ��ʐ؂�ւ��G�t�F�N�g
			if (fadeIn)
			{
				if (!FadeInScreen(5))
				{
					// �G�t�F�N�g�I����̏���
				}
			}
			else if (fadeOut)
			{
				if (!FadeOutScreen(5))
				{
					// �G�t�F�N�g�I����̏���
					sceneID = SCENE_ID_INIT;
					fadeIn = true;
					//SetDrawBright(255, 255, 255);
				}
			}
			GameOverScene();
			break;

			// ���̑�
		default:
			return -1;
			break;
		}


		gameCounter++;
		sceneCounter++;
		//playerCounter++;

		SetDrawScreen(DX_SCREEN_BACK);
		DrawRotaGraph(SCREEN_SIZE_X, SCREEN_SIZE_Y / 2, 2.0f, 0, Screen, FALSE);
		ScreenFlip();
		SetDrawScreen(Screen);
	}

	DxLib_End();		// DX���C�u�����̏I������
	return 0;
}

//�V�X�e���n������
//--------------------------------------------------------------
bool SystemInit(void)
{
	bool retFlag = true;				//�֐��̖߂�l
	// �V�X�e���̏�����
	SetWindowText("shigenari");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1)
	{
		AST();
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);


	// �O���t�B�b�N�̓o�^
	//---------------------------------
	SetTransColor(255, 0, 255);			//�摜�̐F�i�}�[���^�j�̓��ߏ���


	/*titleImage = LoadGraph("image/title.png");*/

	// �ϐ��̏�����
	//---------------------------------
	gameCounter = 0;
	sceneCounter = 0;
	/*playerCounter = 0;*/
	sceneID = SCENE_ID_INIT;
	preSceneID = SCENE_ID_MAX;

	KeyInit();				// �L�[���̏�����

	PlayerSystemInit();
	StageSysteminit();
	return true;
}

// �������V�[��
//--------------------------------------------------------------
void InitScene(void)
{
	fadeIn = true;

	sceneID = SCENE_ID_GAME;

	StageGameInit();
	PlayerGameInit();
}


// �^�C�g���V�[��
//---------------------------------------------------------------
void TitleScene(void)
{
	if (keyUpTrigger[KEY_ID_SPACE])
	{
		fadeOut = true;
	}

	TitleDraw();
}

void TitleDraw(void)
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "TitleScene : %d", sceneCounter);

}


// �Q�[���V�[��
//------------------------------------------------------------------------------------
void GameScene(void)
{
	if (keyUpTrigger[KEY_ID_SPACE])
	{
		fadeOut = true;
	}

	// Pause�@�\
	if (keyDownTrigger[KEY_ID_PAUSE])pauseFlag = !pauseFlag;

	// Pause��
	if (pauseFlag)SetDrawBright(100, 100, 100);

	// �ʏ퓮�쎞
	else
	{
		// �e�폈��
		PlayerControl();
	}

	// ��ʕ`��
	StageGameDraw();
	PlayerDraw();
	GameDraw();

	// Pause���b�Z�[�W��`��
	if (pauseFlag)
	{
		SetDrawBright(255, 255, 255);
		DrawFormatString((SCREEN_SIZE_X - 9 * 8) / 2
			, (SCREEN_SIZE_Y - 16) / 2
			, GetColor(255, 255, 255)
			, "P A U S E");
	}
}

void GameDraw(void)
{
	/*DrawLine(0, 300, SCREEN_SIZE_X, 300, GetColor(255, 255, 255), true);*/
	DrawFormatString(0, 0, GetColor(255, 255, 255), "GameScene : %d", sceneCounter);
}


// �Q�[���I�[�o�[�V�[��
//-----------------------------------------------------------------
void GameOverScene(void)
{
	GameOverDraw();
}

void GameOverDraw(void)
{

	DrawFormatString(0, 0, GetColor(255, 255, 255), "GameOverScene : %d", sceneCounter);
}

