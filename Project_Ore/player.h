

#define PLAYER_SIZE_X 32
#define PLAYER_SIZE_Y 64

extern CHARACTER player;

// プロトタイプ宣言
//------------------------------------------------------------------
void PlayerSystemInit(void);				// システム系初期化 / SystemInitに挿入
void PlayerGameInit(void);					//　InitScene
bool PlayerHitCheck(void/*XY sPos, int sSise*/);
void PlayerControl(void);					//　Game
void PlayerDraw(void);						//　GameDraw