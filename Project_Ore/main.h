//�A�T�[�g�̒�`
#ifdef _DEBUG
#define AST() {\
	CHAR ast_msg[256];\
	wsprintf(ast_msg, "%s %d�s��\0", __FILE__, __LINE__);\
	MessageBox(0, ast_msg, "�A�T�[�g�\��", MB_OK);\
	}
#else
#define AST()
#endif

#define G	 9.8f					// [m/s2]
#define A	10.0f					// [m/s2]
#define FRAME_TIME	0.3f	// [s]

// �萔
//------------------------------------------------------------------
#define SCREEN_SIZE_X 800		// ��ʃT�C�Y��
#define SCREEN_SIZE_Y 500		// ��ʃT�C�Y�c

// �񋓌^
//------------------------------------------------------------------
// �V�[���Ǘ��p
enum SCENE_ID {
	SCENE_ID_INIT,		// �������V�[��
	SCENE_ID_TITLE,		// �^�C�g���V�[��
	SCENE_ID_GAME,		// �Q�[���V�[��
	SCENE_ID_GAMEOVER,	// �Q�[���I�[�o�[�V�[��
	SCENE_ID_MAX
};

// �\����
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

// �v���g�^�C�v�錾
//------------------------------------------------------------------
bool SystemInit(void);				// �V�X�e���n������

void InitScene(void);				// �������V�[���p
void TitleScene(void);				// �^�C�g���V�[���p
void TitleDraw(void);				// �^�C�g���V�[���`��
void GameScene(void);				// �Q�[���V�[���p
void GameDraw(void);				// �Q�[���V�[���`��
void GameOverScene(void);			// �Q�[���I�[�o�[�V�[���p
void GameOverDraw(void);			// �Q�[���I�[�o�[�V�[���`��