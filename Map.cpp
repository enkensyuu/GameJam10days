#include "Map.h"

void Map::Initialize()
{

}

void Map::Update()
{
#pragma region マップ
	ScrollX = ScrollX + CameraSpeed;

	if (ScrollX > 7680)
	{
		ScrollX = 7680;
	}


	for (int y = 0; y < mapCountY; y++)
	{
		for (int x = 0; x < mapCountX; x++)
		{
			if (map[y][x] == FLOOR)
			{

			}
			if (map[y][x] == SECOND)
			{

			}
			if (map[y][x] == PILLAR)
			{

			}
		}
	}
#pragma endregion
}

void Map::Draw(int floor, int second, int pillar)
{
#pragma region マップ
	for (int y = 0; y < mapCountY; y++)
	{
		for (int x = 0; x < mapCountX; x++)
		{
			if (map[y][x] == FLOOR)
			{
				DrawGraph(x * BLOCK_SIZE - ScrollX, y * BLOCK_SIZE, floor, true);
			}
			if (map[y][x] == SECOND)
			{
				DrawGraph(x * BLOCK_SIZE - ScrollX, y * BLOCK_SIZE, second, true);
			}
			if (map[y][x] == PILLAR)
			{
				DrawGraph(x * BLOCK_SIZE - ScrollX, y * BLOCK_SIZE, pillar, true);
			}
		}
	}
	DrawFormatString(600, 30, GetColor(255, 255, 255), "スクロール座標%d", ScrollX);
#pragma endregion
}
