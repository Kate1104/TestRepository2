//��`---------------------
#define MAP_X		48	//ϯ�߉摜�̉�����
#define MAP_Y		15			//ϯ�߉摜�̏c����
#define CHIP_SIZE_X	32				//ϯ�����߉摜�̉�����
#define CHIP_SIZE_Y	32				//ϯ�����߉摜�̏c����
#define SCROLL_X_MIN 400
#define SCROLL_X_MAX 200
extern XY mapPos;
extern int mapData[MAP_Y][MAP_X];

//�v���g�^�C�v�錾---------
void StageSysteminit(void);			//�ð�ޏ��̏�����
void StageGameInit(void);			//
void StageGameDraw(void);			//�ްщ�ʂ̕\������
XY MapPosToIndex(XY pos);				//�s�N�Z�����W�n����}�b�v���W�n�ɕϊ�
XY MapIndexToPos(XY index);
bool IsPass(XY pos);				//�w�肳�ꂽ���W���ʉ߉\���ǂ���
void ResultMap(void);
