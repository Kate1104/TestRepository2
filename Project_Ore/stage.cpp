#include "DxLib.h"
#include "main.h"
#include "player.h"
#include "stage.h"

int chipImage[13];			//ﾏｯﾌﾟﾁｯﾌﾟ画像


//ﾏｯﾌﾟ関連
int mapData[MAP_Y][MAP_X] = {
	4,4,4,4,4,4,4,4, 4,4,4,4,4,4,4,4,	4,4,4,4,4,4,4,4, 4,4,4,4,4,4,4,4,	4,4,4,4,4,4,4,4, 4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4, 4,4,4,4,4,4,4,4,	4,4,4,4,4,4,4,4, 4,4,4,6,6,6,4,4,	4,4,4,4,4,4,4,6, 6,6,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4, 4,4,4,4,4,4,4,4,	4,4,4,4,4,4,4,4, 4,6,6,6,4,4,6,4,	4,4,4,4,4,4,6,4, 4,6,6,6,4,4,4,4,
	4,4,4,4,4,4,4,4, 4,4,4,4,4,4,4,4,	4,4,4,4,4,4,4,4, 6,1,1,1,6,4,4,11,	4,4,4,4,4,11,4,4, 11,5,5,5,6,4,4,4,
	4,4,4,4,4,4,4,4, 4,4,4,4,4,4,4,4,	4,4,4,4,4,4,4,6, 1,1,1,1,1,11,11,11,	11,4,4,4,11,11,11,11, 5,5,5,5,5,6,4,4,

	4,4,4,4,4,4,4,4, 4,4,4,4,4,4,4,4,	4,4,4,4,4,4,4,4, 1,1,1,1,1,11,4,4,	1,4,4,4,5,4,4,11, 5,5,5,5,5,4,4,4,
	4,4,4,4,4,4,4,4, 4,4,4,4,4,4,4,4,	4,4,4,4,4,4,4,4, 1,1,1,1,1,1,4,4,	1,4,4,4,5,4,4,5, 5,5,5,5,5,4,4,4,
	5,5,5,5,5,6,6,5, 5,5,5,6,5,6,5,5,	5,6,5,6,5,5,4,5, 1,1,2,3,3,3,1,1,	3,4,4,4,3,4,4,3, 3,3,2,5,5,4,4,4,
	5,5,5,5,5,6,6,5, 5,5,5,6,5,5,5,5,	5,6,5,6,5,5,5,5, 1,2,3,3,4,4,2,4,	3,4,4,4,3,4,2,4, 4,3,3,2,4,4,4,4,
	4,4,4,4,4,4,4,4, 4,4,4,4,4,4,4,4,	4,4,4,4,4,4,4,4, 1,2,3,3,6,6,2,6,	3,6,4,6,3,6,2,6, 6,3,3,2,5,6,4,4,

	4,4,4,4,4,4,4,4, 4,4,4,4,4,4,4,4,	4,4,4,4,4,4,4,6, 1,2,2,3,3,3,2,3,	2,6,4,6,2,3,2,3, 3,3,2,2,5,6,4,4,
	4,4,4,4,4,4,4,4, 4,4,4,4,4,4,4,4,	4,4,4,4,4,4,4,4, 11,1,2,6,6,6,6,2,	6,4,4,4,6,2,6,6, 6,6,2,5,6,4,4,4,
	4,4,4,4,4,4,4,4, 4,4,4,4,4,4,4,4,	4,4,4,4,4,4,4,4, 4,11,2,2,2,2,2,6,	4,4,4,4,4,6,2,2, 2,2,2,6,4,4,4,4,
	4,4,4,4,4,4,4,4, 4,4,4,4,4,4,4,4,	4,4,4,4,4,4,4,4, 4,4,6,6,6,6,6,4,	4,4,4,4,4,4,6,6, 6,6,6,4,4,4,4,4,
	4,4,4,4,4,4,4,4, 4,4,4,4,4,4,4,4,	4,4,4,4,4,4,4,4, 4,4,4,4,4,4,4,4,	4,4,4,4,4,4,4,4, 4,4,4,4,4,4,4,4,
};
XY mapPos;			//マップのオフセット

//ｽﾃｰｼﾞ情報の初期化
void StageSysteminit(void)
{
	//ﾏｯﾌﾟﾁｯﾌﾟの画像を読み込む
	LoadDivGraph("image/haikei.png"
		, 7, 7, 1
		, CHIP_SIZE_X, CHIP_SIZE_Y
		, chipImage);

	mapPos.x = 0;
	mapPos.y = 0;
}


void StageGameInit(void)
{
	mapPos.x = 0;
	mapPos.y = 0;
}

//ｹﾞｰﾑ画面の表示処理
void StageGameDraw(void)
{
	/*SetDrawBright(50, 50, 50);*/

	for (int y = 0; y < MAP_Y; y++)
	{
		for (int x = 0; x < MAP_X; x++)
		{
			DrawGraph(x * CHIP_SIZE_X - mapPos.x
				, y * CHIP_SIZE_Y - mapPos.y
				, chipImage[mapData[y][x]], true);
		}
	}
}

//ピクセル座標系からマップ座標系に変換
XY MapPosToIndex(XY pos)
{
	XY tmp;

	tmp.x = pos.x / CHIP_SIZE_X;
	tmp.y = pos.y / CHIP_SIZE_Y;

	return tmp;		//変換した値を返す
}

//マップ配列座標系からピクセル座標系（左上）に変換する
XY MapIndexToPos(XY index)
{
	XY tmp;

	tmp.x = index.x * CHIP_SIZE_X;
	tmp.y = index.y * CHIP_SIZE_Y;

	return tmp;		//変換した値を返す
}

//指定された座標が通過可能かどうか
bool IsPass(XY pos)
{
	XY indexPos;

	indexPos = MapPosToIndex(pos);

	switch (mapData[indexPos.y][indexPos.x])
	{

	case 5:
	

		return false;	//通れない
		break;
	}

	{
		return true;	//通れる
	}
}
