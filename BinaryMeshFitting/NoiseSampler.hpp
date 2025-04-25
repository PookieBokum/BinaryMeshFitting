#pragma once

#include "noise.hpp"
#include <memory>
#include <vector>
#include <thread>
#include <mutex>

class NoiseSampler {
private:
	std::vector<std::unique_ptr<noise::PerlinNoise>> perlin_noise;
	std::vector<std::unique_ptr<noise::WorleyNoise>> worley_noise;
	std::mutex mutex;
	
public:
	NoiseSampler(int num_threads = std::thread::hardware_concurrency()) {
		for(int i = 0; i < num_threads; i++) {
			perlin_noise.push_back(std::make_unique<noise::PerlinNoise>(i));
			worley_noise.push_back(std::make_unique<noise::WorleyNoise>(i));
		}
	}
	
	float samplePerlin(int thread_index, float x, float y, float z, int octaves = 4, float persistence = 0.5f) {
		std::lock_guard<std::mutex> lock(mutex);
		return perlin_noise[thread_index]->octaveNoise(x, y, z, octaves, persistence);
	}
	
	float sampleWorley(int thread_index, float x, float y, float z) {
		std::lock_guard<std::mutex> lock(mutex);
		return worley_noise[thread_index]->noise(x, y, z);
	}
	
	float sampleCombined(int thread_index, float x, float y, float z) {
		float perlin = samplePerlin(thread_index, x, y, z);
		float worley = sampleWorley(thread_index, x, y, z);
		return (perlin + worley) * 0.5f;
	}
};
