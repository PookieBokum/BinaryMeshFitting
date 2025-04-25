#pragma once

#include <functional>
#include <glm/glm.hpp>

using SamplerValueFunction = std::function<float(float, const glm::vec3&)>;
using SamplerGradientFunction = std::function<glm::vec3(float, const glm::vec3&, float)>;
using SamplerBlockFunction = std::function<void(float, const glm::vec3&, const glm::ivec3&, float, void**, float*, int, int, void*)>;

struct SamplerProperties {
	int octaves;
	float persistence;
	float lacunarity;
	float scale;
};

struct Sampler {
	SamplerValueFunction value_function;
	SamplerGradientFunction gradient_function;
	SamplerBlockFunction block_function;
	SamplerProperties properties;
};

inline std::string get_simd_text()
{
	switch (FastNoiseSIMD::GetSIMDLevel())
	{
	case 1:
		return "SSE2";
	case 2:
		return "SSE4.1";
	case 3:
		return "AVX2/FMA3";
	case 4:
		return "AVX512";
	case 5:
		return "ARM NEON";
	default:
		return "None";
	}
}
