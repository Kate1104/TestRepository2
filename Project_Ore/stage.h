//定義---------------------
#define MAP_X		48	//ﾏｯﾌﾟ画像の横ｻｲｽﾞ
#define MAP_Y		15			//ﾏｯﾌﾟ画像の縦ｻｲｽﾞ
#define CHIP_SIZE_X	32				//ﾏｯﾌﾟﾁｯﾌﾟ画像の横ｻｲｽﾞ
#define CHIP_SIZE_Y	32				//ﾏｯﾌﾟﾁｯﾌﾟ画像の縦ｻｲｽﾞ
#define SCROLL_X_MIN 400
#define SCROLL_X_MAX 200
extern XY mapPos;
extern int mapData[MAP_Y][MAP_X];

//プロトタイプ宣言---------
void StageSysteminit(void);			//ｽﾃｰｼﾞ情報の初期化
void StageGameInit(void);			//
void StageGameDraw(void);			//ｹﾞｰﾑ画面の表示処理
XY MapPosToIndex(XY pos);				//ピクセル座標系からマップ座標系に変換
XY MapIndexToPos(XY index);
bool IsPass(XY pos);				//指定された座標が通過可能かどうか
void ResultMap(void);
