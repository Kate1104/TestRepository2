//アサートの定義
#ifdef _DEBUG
#define AST() {\
	CHAR ast_msg[256];\
	wsprintf(ast_msg, "%s %d行目\0", __FILE__, __LINE__);\
	MessageBox(0, ast_msg, "アサート表示", MB_OK);\
	}
#else
#define AST()
#endif

#define G	 9.8f					// [m/s2]
#define A	10.0f					// [m/s2]
#define FRAME_TIME	0.3f	// [s]

// 定数
//------------------------------------------------------------------
#define SCREEN_SIZE_X 800		// 画面サイズ横
#define SCREEN_SIZE_Y 500		// 画面サイズ縦

// 列挙型
//------------------------------------------------------------------
// シーン管理用
enum SCENE_ID {
	SCENE_ID_INIT,		// 初期化シーン
	SCENE_ID_TITLE,		// タイトルシーン
	SCENE_ID_GAME,		// ゲームシーン
	SCENE_ID_GAMEOVER,	// ゲームオーバーシーン
	SCENE_ID_MAX
};

// 構造体
//------------------------------------------------------------------
struct XY
{
	int x;
	int y;
};

struct POS
{
	int playerPos;
	int mapPos;
	int x;
	int y;
};

// プロトタイプ宣言
//------------------------------------------------------------------
bool SystemInit(void);				// システム系初期化

void InitScene(void);				// 初期化シーン用
void TitleScene(void);				// タイトルシーン用
void TitleDraw(void);				// タイトルシーン描画
void GameScene(void);				// ゲームシーン用
void GameDraw(void);				// ゲームシーン描画
void GameOverScene(void);			// ゲームオーバーシーン用
void GameOverDraw(void);			// ゲームオーバーシーン描画