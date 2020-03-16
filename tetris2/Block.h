#pragma once
#include<DirectXmath.h>

enum Type
{
	OBJ_SPACE,
	OBJ_WALL,
	OBJ_BLOCK

};


class Block
{
public:
	Block();
	~Block();




private:

	static constexpr int blockHeight = 4;
	static constexpr int blockWidth = 4;
	static constexpr int blockNum = 4;



public:

	Type blocks[blockNum][blockHeight][blockWidth] =
	{
		{
			{OBJ_SPACE,OBJ_SPACE,OBJ_SPACE,OBJ_SPACE},
			{OBJ_SPACE,OBJ_BLOCK,OBJ_BLOCK,OBJ_SPACE},
			{OBJ_SPACE,OBJ_BLOCK,OBJ_BLOCK,OBJ_SPACE},
			{OBJ_SPACE,OBJ_SPACE,OBJ_SPACE,OBJ_SPACE}
		},

		{
			{OBJ_SPACE, OBJ_SPACE, OBJ_SPACE, OBJ_SPACE},
			{OBJ_SPACE, OBJ_SPACE, OBJ_BLOCK, OBJ_SPACE},
			{OBJ_SPACE, OBJ_BLOCK, OBJ_BLOCK, OBJ_BLOCK},
			{OBJ_SPACE, OBJ_SPACE, OBJ_SPACE, OBJ_SPACE}

		},

		{
			{OBJ_SPACE, OBJ_BLOCK, OBJ_SPACE, OBJ_SPACE},
			{OBJ_SPACE, OBJ_BLOCK, OBJ_SPACE, OBJ_SPACE},
			{OBJ_SPACE, OBJ_BLOCK, OBJ_SPACE, OBJ_SPACE},
			{OBJ_SPACE, OBJ_BLOCK, OBJ_SPACE, OBJ_SPACE},

		},

		{
			{OBJ_SPACE,OBJ_SPACE,OBJ_SPACE,OBJ_SPACE},
			{OBJ_SPACE,OBJ_SPACE,OBJ_SPACE,OBJ_BLOCK},
			{OBJ_BLOCK, OBJ_BLOCK, OBJ_BLOCK, OBJ_BLOCK},
			{OBJ_SPACE,OBJ_SPACE,OBJ_SPACE,OBJ_SPACE}

		},



	};

	DirectX::XMFLOAT4 Colors[blockNum + 1] =
	{
		{1.0f, 0.0f, 0.0f, 1.0f},
		{0.0f, 1.0f, 0.0f, 1.0f},
		{0.0f, 0.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 0.0f, 1.0f},
		{0.0f, 0.0f, 0.0f, 1.0f},
	};


};