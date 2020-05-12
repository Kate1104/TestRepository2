#include "DxLib.h"
#include "main.h"
#include "KeyCheck.h"
#include "player.h"

XY playerPos;
POS mapPos;

void PlayerSystemInit(void)
{
	mapPos.x = 0;
	mapPos.y = 0;
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
	//ˆÚ“®
	if (CheckHitKey(KEY_INPUT_LEFT)) playerPos.x -= 4;
	if (CheckHitKey(KEY_INPUT_RIGHT)) playerPos.x += 4;
	/*if (CheckHitKey(KEY_INPUT_UP)) player1Pos.y -= 4;
	if (CheckHitKey(KEY_INPUT_DOWN)) player1Pos.y += 4;*/

}

void PlayerDraw(void)
{
	DrawCircle((-mapPos.x + playerPos.x), (-mapPos.y + playerPos.y), PLAYER_SIZE_X / 2, GetColor(255, 255, 255), true);
}