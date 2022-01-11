#include "DxLib.h"
#include"main.h"

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "LC1A_20_ハトウトシキ: タイトル";

// ウィンドウ横幅
const int WIN_WIDTH = 640;

// ウィンドウ縦幅
const int WIN_HEIGHT = 580;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
                   _In_ int nCmdShow) {
	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);

	// ウィンドウサイズを手動では変更させず、
	// かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// タイトルを変更
	SetMainWindowText(TITLE);

	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(1.0);

	// 画面の背景色を設定する
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 画像などのリソースデータの変数宣言と読み込み
	int block = LoadGraph("Block.png");
	int block_2 = LoadGraph("Block_2.png");
	int tex_circle = LoadGraph("Circle.png");

	// ゲームループで使う変数の宣言
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

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = {0};

	// ゲームループ
	while (true) {
		// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
		// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys);

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		// 更新処理
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

		// 描画処理
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


		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();

		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);

		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1) {
			break;
		}

		// ESCキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}

	DeleteGraph(block);
	DeleteGraph(block_2);
	DeleteGraph(tex_circle);

	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}
