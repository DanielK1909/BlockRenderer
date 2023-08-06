#pragma once

#define CHUNK_SIZE 16
#define WORLD_HEIGHT 256

struct Block {
	static enum BlockType {
		GRASS,
		DIRT,
		STONE
	};

	BlockType type_;
};

struct Chunk {
	Block blocks_[CHUNK_SIZE * CHUNK_SIZE * WORLD_HEIGHT];
};