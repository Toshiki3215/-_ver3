#include "DxLib.h"
#include"main.h"

// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "LC1A_20_�n�g�E�g�V�L: �^�C�g��";

// �E�B���h�E����
const int WIN_WIDTH = 640;

// �E�B���h�E�c��
const int WIN_HEIGHT = 580;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
                   _In_ int nCmdShow) {
	// �E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(TRUE);

	// �E�B���h�E�T�C�Y���蓮�ł͕ύX�������A
	// ���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// �^�C�g����ύX
	SetMainWindowText(TITLE);

	// ��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�(���j�^�[�̉𑜓x�ɍ��킹��)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// ��ʃT�C�Y��ݒ�(�𑜓x�Ƃ̔䗦�Őݒ�)
	SetWindowSizeExtendRate(1.0);

	// ��ʂ̔w�i�F��ݒ肷��
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���
	int block = LoadGraph("Block.png");
	int block_2 = LoadGraph("Block_2.png");
	int tex_circle = LoadGraph("Circle.png");

	// �Q�[�����[�v�Ŏg���ϐ��̐錾
	cr = GetColor(255, 255, 255);

	int map[mapSizeY][mapSizeX] =
	{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char oldkeys[256] = {0};

	// �Q�[�����[�v
	while (true) {
		// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
		// �ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		// �X�V����
		if (keys[KEY_INPUT_UP] && circle.y - circle.r > 0)
		{
			circle.y -= circle.speed;
		}
		if (keys[KEY_INPUT_DOWN] && circle.y + circle.r < end.y)
		{
			circle.y += circle.speed;
		}
		if (keys[KEY_INPUT_LEFT] && circle.x - circle.r > 0)
		{
			circle.x -= circle.speed;
		}
		if (keys[KEY_INPUT_RIGHT] && circle.x + circle.r < end.x)
		{
			circle.x += circle.speed;
		}

		/*int uy = circle.y - circle.r;
		int ux = circle.x - circle.r;
		int ly = circle.y + circle.r;
		int lx = circle.x + circle.r;*/

		int uy = circle.y;
		int ux = circle.x;

		map[uy / blockSize][ux / blockSize] = 2;
		/*map[uy / blockSize][lx / blockSize] = 2;
		map[ly / blockSize][ux / blockSize] = 2;
		map[ly / blockSize][lx / blockSize] = 2;*/

		// �`�揈��
		for (int y = 0; y < mapSizeY; y++)
		{
			for (int x = 0; x < mapSizeX; x++)
			{
				if (map[y][x] == BLOCK)
				{
					DrawGraph(x * blockSize, y * blockSize, block, TRUE);
				}
				/*DrawLine(x * blockSize, 0, x * blockSize, end.y, cr, TRUE);
				DrawLine(0, y * blockSize, end.x, y * blockSize, cr, TRUE);*/
			}
		}
		for (int y = 0; y < mapSizeY; y++)
		{
			for (int x = 0; x < mapSizeX; x++)
			{
				if (map[y][x] == BLOCK2)
				{
					DrawGraph(x * blockSize, y * blockSize, block_2, TRUE);
				}
				/*DrawLine(x * blockSize, 0, x * blockSize, end.y, cr, TRUE);
				DrawLine(0, y * blockSize, end.x, y * blockSize, cr, TRUE);*/
			}
		}

		DrawGraph(circle.x - circle.r, circle.y - circle.r, tex_circle, TRUE);


		//---------  �����܂łɃv���O�������L�q  ---------//
		// (�_�u���o�b�t�@)����
		ScreenFlip();

		// 20�~���b�ҋ@(�^��60FPS)
		WaitTimer(20);

		// Windows�V�X�e�����炭�������������
		if (ProcessMessage() == -1) {
			break;
		}

		// ESC�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}

	DeleteGraph(block);
	DeleteGraph(block_2);
	DeleteGraph(tex_circle);

	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}
