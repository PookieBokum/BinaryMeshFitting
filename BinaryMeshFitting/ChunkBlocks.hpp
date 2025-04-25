#pragma once

#include "PCH.h"

struct ChunkBlock {
	math::vec3f position;
	float value;
	math::vec3f color;
	
	ChunkBlock() : position(0, 0, 0), value(0), color(0, 0, 0) {}
	ChunkBlock(const math::vec3f& pos, float val, const math::vec3f& col) 
		: position(pos), value(val), color(col) {}
};
