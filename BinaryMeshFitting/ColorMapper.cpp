#include "PCH.h"
#include "ColorMapper.hpp"
#include <algorithm>

using namespace glm;

ColorMapper::ColorMapper() : noise(std::make_unique<noise::PerlinNoise>()) {
	color_map.resize(256);
}

ColorMapper::~ColorMapper() = default;

void ColorMapper::generate_colors(SmartContainer<DualVertex>& verts)
{
	if (!verts.count)
		return;

	float* noise = 0;
	get_noise(verts, &noise);
	map_noise(verts, noise);

	FastNoiseSIMD::FreeNoiseSet(noise);
}

void ColorMapper::get_noise(SmartContainer<DualVertex>& verts, float** out)
{
	int count = (int)verts.count;

	FastNoiseVectorSet vectors;
	vectors.SetSize(count);

	const float scale = 1.0f;

	for (int i = 0; i < count; i++)
	{
		vectors.xSet[i] = verts[i].p.x * scale;
		vectors.ySet[i] = verts[i].p.y * scale;
		vectors.zSet[i] = verts[i].p.z * scale;
	}

	*out = FastNoiseSIMD::GetEmptySet(count, 1, 1);

	noise_context->SetNoiseType(FastNoiseSIMD::NoiseType::SimplexFractal);
	noise_context->SetFractalOctaves(4);
	noise_context->SetFractalType(FastNoiseSIMD::FractalType::FBM);
	noise_context->FillNoiseSet(*out, &vectors);
}

void ColorMapper::map_noise(SmartContainer<DualVertex>& verts, float* noise)
{
	int count = (int)verts.count;

	for (int i = 0; i < count; i++)
	{
		float n = noise[i] * 4.0f;
		verts[i].color = get_color(verts[i].p, n);
	}
}

math::vec3f ColorMapper::get_color(const math::vec3f& pos, float value)
{
	// Generate noise value for color variation
	float noise = noise_context.noise(pos.x * 0.1f, pos.y * 0.1f, pos.z * 0.1f);
	
	// Map value to color using noise for variation
	float h = (value + noise) * 0.5f; // Hue based on value and noise
	float s = 0.8f; // Saturation
	float l = 0.6f; // Lightness
	
	// Convert HSL to RGB
	float c = (1.0f - std::abs(2.0f * l - 1.0f)) * s;
	float x = c * (1.0f - std::abs(std::fmod(h * 6.0f, 2.0f) - 1.0f));
	float m = l - c * 0.5f;
	
	math::vec3f rgb;
	if (h < 1.0f/6.0f) {
		rgb = math::vec3f(c, x, 0.0f);
	} else if (h < 2.0f/6.0f) {
		rgb = math::vec3f(x, c, 0.0f);
	} else if (h < 3.0f/6.0f) {
		rgb = math::vec3f(0.0f, c, x);
	} else if (h < 4.0f/6.0f) {
		rgb = math::vec3f(0.0f, x, c);
	} else if (h < 5.0f/6.0f) {
		rgb = math::vec3f(x, 0.0f, c);
	} else {
		rgb = math::vec3f(c, 0.0f, x);
	}
	
	return rgb + math::vec3f(m, m, m);
}

void ColorMapper::generateColorMap(int count, float* out) {
	for(int i = 0; i < count; i++) {
		float t = static_cast<float>(i) / count;
		float noise_value = noise->octaveNoise(t * 10.0f, 0.0f, 0.0f, 4, 0.5f);
		out[i] = noise_value;
	}
}

float ColorMapper::getColor(float value) const {
	int index = static_cast<int>(value * (color_map.size() - 1));
	index = std::clamp(index, 0, static_cast<int>(color_map.size() - 1));
	return color_map[index];
}
