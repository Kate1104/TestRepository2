#include "DxLib.h"
#include "main.h"
#include "Effect.h"
#include "KeyCheck.h"
#include "player.h"
#include "stage.h"


// 変数
//-------------------------------------------------------------
// シーン管理用
int gameCounter;		// gameLoop動作確認用
int sceneCounter;		// シーンカウンター
SCENE_ID sceneID;
SCENE_ID preSceneID;

// WinMain関数
//-------------------------------------------------------------
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// システムの初期化
	if (!SystemInit())
	{
		return -1;
	}

	int Screen = MakeScreen(SCREEN_SIZE_X, SCREEN_SIZE_Y);

	// ゲームループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClsDrawScreen();

		// シーンカウンタを制御
		if (sceneID != preSceneID)
		{
			preSceneID = sceneID;
			sceneCounter = 0;
		}


		// 入力情報の取得
		KeyCheck();


		// シーン選択
		switch (sceneID)
		{
			// 初期化シーン
		case SCENE_ID_INIT:
			InitScene();
			break;

			// タイトルシーン
		case SCENE_ID_TITLE:
			// 画面切り替えエフェクト
			if (fadeIn)
			{
				if (!FadeInScreen(5))
				{
					// エフェクト終了後の処理
				}
			}
			else if (fadeOut)
			{
				if (!FadeOutScreen(5))
				{
					// エフェクト終了後の処理
					sceneID = SCENE_ID_GAME;
					fadeIn = true;
					//SetDrawBright(255, 255, 255);
				}
			}
			TitleScene();
			break;

			// ゲームシーン
		case SCENE_ID_GAME:
			// 画面切り替えエフェクト
			if (fadeIn)
			{
				if (!FadeInScreen(5))
				{
					// エフェクト終了後の処理
				}
			}
			else if (fadeOut)
			{
				if (!FadeOutScreen(5))
				{
					// エフェクト終了後の処理
					sceneID = SCENE_ID_GAMEOVER;
					fadeIn = true;
					//SetDrawBright(255, 255, 255);
				}
			}
			GameScene();
			break;

			// ゲームオーバーシーン
		case SCENE_ID_GAMEOVER:
			// 画面切り替えエフェクト
			if (fadeIn)
			{
				if (!FadeInScreen(5))
				{
					// エフェクト終了後の処理
				}
			}
			else if (fadeOut)
			{
				if (!FadeOutScreen(5))
				{
					// エフェクト終了後の処理
					sceneID = SCENE_ID_INIT;
					fadeIn = true;
					//SetDrawBright(255, 255, 255);
				}
			}
			GameOverScene();
			break;

			// その他
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

	DxLib_End();		// DXライブラリの終了処理
	return 0;
}

//システム系初期化
//--------------------------------------------------------------
bool SystemInit(void)
{
	bool retFlag = true;				//関数の戻り値
	// システムの初期化
	SetWindowText("shigenari");
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1)
	{
		AST();
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);


	// グラフィックの登録
	//---------------------------------
	SetTransColor(255, 0, 255);			//画像の色（マゼンタ）の透過処理


	/*titleImage = LoadGraph("image/title.png");*/

	// 変数の初期化
	//---------------------------------
	gameCounter = 0;
	sceneCounter = 0;
	/*playerCounter = 0;*/
	sceneID = SCENE_ID_INIT;
	preSceneID = SCENE_ID_MAX;

	KeyInit();				// キー情報の初期化

	PlayerSystemInit();
	StageSysteminit();
	return true;
}

// 初期化シーン
//--------------------------------------------------------------
void InitScene(void)
{
	fadeIn = true;

	sceneID = SCENE_ID_GAME;

	StageGameInit();
	PlayerGameInit();
}


// タイトルシーン
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


// ゲームシーン
//------------------------------------------------------------------------------------
void GameScene(void)
{
	if (keyUpTrigger[KEY_ID_SPACE])
	{
		fadeOut = true;
	}

	// Pause機能
	if (keyDownTrigger[KEY_ID_PAUSE])pauseFlag = !pauseFlag;

	// Pause時
	if (pauseFlag)SetDrawBright(100, 100, 100);

	// 通常動作時
	else
	{
		// 各種処理
		PlayerControl();
	}

	// 画面描画
	StageGameDraw();
	PlayerDraw();
	GameDraw();

	// Pauseメッセージを描画
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


// ゲームオーバーシーン
//-----------------------------------------------------------------
void GameOverScene(void)
{
	GameOverDraw();
}

void GameOverDraw(void)
{

	DrawFormatString(0, 0, GetColor(255, 255, 255), "GameOverScene : %d", sceneCounter);
}

