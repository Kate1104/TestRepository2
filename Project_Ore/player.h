

#define PLAYER_SIZE_X 32
#define PLAYER_SIZE_Y 64

extern CHARACTER player;

// �v���g�^�C�v�錾
//------------------------------------------------------------------
void PlayerSystemInit(void);				// �V�X�e���n������ / SystemInit�ɑ}��
void PlayerGameInit(void);					//�@InitScene
bool PlayerHitCheck(void/*XY sPos, int sSise*/);
void PlayerControl(void);					//�@Game
void PlayerDraw(void);						//�@GameDraw