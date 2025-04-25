#pragma once

#include "noise.hpp"
#include <memory>
#include <vector>

class ColorMapper
{
private:
	std::unique_ptr<noise::PerlinNoise> noise;
	std::vector<float> color_map;

public:
	ColorMapper();
	~ColorMapper();

	void generateColorMap(int count, float* out);
	float getColor(float value) const;
};
