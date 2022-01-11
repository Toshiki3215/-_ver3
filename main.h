#pragma once

bool box_collision(int ax, int ay, int aw, int ah, int bx, int by, int bw, int bh)
{
	return bx < ax + aw && ax < bx + bw && by < ay + ah && ay < by + bh;
}

enum MapInfo
{
	NUNE,
	BLOCK,
	BLOCK2
};

enum BlockInfo
{
	NUNEHIT,
	HIT
};

typedef struct Circle
{
	int x;
	int y;
	int r;
	int speed;
}Circle;

typedef struct Map
{
	int x;
	int y;
}Map;

typedef struct Corner
{
	int x;
	int y;
}Corner;


const int blockSize = 32;
const int mapSizeX = 20;
const int mapSizeY = 10;
int cr;

Circle circle =
{
	16,
	16,
	16,
	4
};

Map end =
{
	640,
	320
};

// 最新のキーボード情報用
char keys[256] = { 0 };