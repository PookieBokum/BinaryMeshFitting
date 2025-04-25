#pragma once

#include <cmath>
#include <random>
#include <vector>
#include <array>

namespace noise {
    class PerlinNoise {
    private:
        std::mt19937 rng;
        std::uniform_real_distribution<float> dist;
        std::array<int, 512> p;
        
        float fade(float t) {
            return t * t * t * (t * (t * 6 - 15) + 10);
        }
        
        float grad(int hash, float x, float y, float z) {
            int h = hash & 15;
            float u = h < 8 ? x : y;
            float v = h < 4 ? y : h == 12 || h == 14 ? x : z;
            return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
        }
        
        void initPermutation() {
            std::vector<int> permutation(256);
            for (int i = 0; i < 256; i++) permutation[i] = i;
            std::shuffle(permutation.begin(), permutation.end(), rng);
            for (int i = 0; i < 512; i++) p[i] = permutation[i & 255];
        }
        
    public:
        PerlinNoise(unsigned int seed = 0) : rng(seed), dist(0.0f, 1.0f) {
            initPermutation();
        }
        
        float noise(float x, float y, float z) {
            int X = (int)std::floor(x) & 255;
            int Y = (int)std::floor(y) & 255;
            int Z = (int)std::floor(z) & 255;
            
            x -= std::floor(x);
            y -= std::floor(y);
            z -= std::floor(z);
            
            float u = fade(x);
            float v = fade(y);
            float w = fade(z);
            
            int A = p[X] + Y;
            int B = p[X + 1] + Y;
            int AA = p[A] + Z;
            int BA = p[B] + Z;
            int AB = p[A + 1] + Z;
            int BB = p[B + 1] + Z;
            
            float res = lerp(w, lerp(v, lerp(u, grad(p[AA], x, y, z), grad(p[BA], x-1, y, z)),
                                       lerp(u, grad(p[AB], x, y-1, z), grad(p[BB], x-1, y-1, z))),
                               lerp(v, lerp(u, grad(p[AA+1], x, y, z-1), grad(p[BA+1], x-1, y, z-1)),
                                       lerp(u, grad(p[AB+1], x, y-1, z-1), grad(p[BB+1], x-1, y-1, z-1))));
            return (res + 1.0f) / 2.0f;
        }
        
        float octaveNoise(float x, float y, float z, int octaves, float persistence) {
            float total = 0;
            float frequency = 1;
            float amplitude = 1;
            float maxValue = 0;
            
            for(int i = 0; i < octaves; i++) {
                total += noise(x * frequency, y * frequency, z * frequency) * amplitude;
                maxValue += amplitude;
                amplitude *= persistence;
                frequency *= 2;
            }
            
            return total / maxValue;
        }
        
        float lerp(float t, float a, float b) {
            return a + t * (b - a);
        }
    };
    
    class WorleyNoise {
    private:
        std::mt19937 rng;
        std::uniform_real_distribution<float> dist;
        
    public:
        WorleyNoise(unsigned int seed = 0) : rng(seed), dist(0.0f, 1.0f) {}
        
        float noise(float x, float y, float z) {
            int X = (int)std::floor(x);
            int Y = (int)std::floor(y);
            int Z = (int)std::floor(z);
            
            float minDist = 1.0f;
            
            for(int i = -1; i <= 1; i++) {
                for(int j = -1; j <= 1; j++) {
                    for(int k = -1; k <= 1; k++) {
                        float px = X + i + dist(rng);
                        float py = Y + j + dist(rng);
                        float pz = Z + k + dist(rng);
                        
                        float dx = px - x;
                        float dy = py - y;
                        float dz = pz - z;
                        
                        float dist = dx*dx + dy*dy + dz*dz;
                        if(dist < minDist) minDist = dist;
                    }
                }
            }
            
            return 1.0f - std::sqrt(minDist);
        }
    };
} 