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
#define VELOCITY_X_MAX 5.0

// �萔
//------------------------------------------------------------------
#define SCREEN_SIZE_X 1000		// ��ʃT�C�Y��
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

enum DIR
{
	DIR_RIGHT,
	DIR_LEFT,
	DIR_MAX
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
	int x;
	int y;
};

struct XY_F {
	float x;
	float y;
};

struct CHARACTER {
	DIR moveDir;				//�����Ă������
	XY pos;						//�L�����N�^�̈ʒu�i���S�j
	XY size;					//�L�����N�^�摜�̃T�C�Y
	XY offsetSize;				//�L�����N�^��������̍���ʒu
	XY hitPosS;					//�����蔻��p�̍���
	XY hitPosE;					//�����蔻��p�̉E��
	bool runFlag;				//�L�����N�^�̏�ԁi�����Ă��邩�H�j
	bool jumpFlag;				//�L�����N�^�̏�ԁi�W�����v���Ă��邩�H�j
	bool shotFlag;				//�L�����N�^�̏�ԁi�e�����Ă��邩�H�j
	bool damageFlag;			//�L�����N�^�̏�ԁi�_���[�W�󂯂Ă��邩�H�j
	XY_F velocity;
	int moveSpeed;				//�L�����N�^�̈ړ���
	int life;					//�L�����N�^�̗̑�
	int lifeMax;				//�L�����N�^�̗͍̑ő�
	int animCnt;				//�L�����N�^�̃A�j���[�V�����p�J�E���^
	int imgLockCnt;				//�L�����N�^�̃C���[�W�Œ�p�J�E���^
	bool visible;				//true�F�\������	false�F�\������Ȃ�
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