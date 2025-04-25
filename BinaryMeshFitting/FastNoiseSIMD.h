#pragma once

#include <vector>
#include <cmath>
#include <random>

class FastNoiseSIMD {
public:
    enum NoiseType {
        Value,
        ValueFractal,
        Perlin,
        PerlinFractal,
        Simplex,
        SimplexFractal,
        WhiteNoise,
        Cellular
    };

    FastNoiseSIMD() : seed(1337), frequency(0.01f), noiseType(Perlin) {
        std::mt19937 gen(seed);
        std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
        for(int i = 0; i < 256; ++i) {
            perm[i] = i;
        }
        for(int i = 0; i < 256; ++i) {
            int j = gen() % 256;
            std::swap(perm[i], perm[j]);
        }
    }

    void SetSeed(int seed) { this->seed = seed; }
    void SetFrequency(float frequency) { this->frequency = frequency; }
    void SetNoiseType(NoiseType noiseType) { this->noiseType = noiseType; }

    float* GetNoiseSet(float x, float y, float z, int sizeX, int sizeY, int sizeZ) {
        float* noise = new float[sizeX * sizeY * sizeZ];
        for(int i = 0; i < sizeX; ++i) {
            for(int j = 0; j < sizeY; ++j) {
                for(int k = 0; k < sizeZ; ++k) {
                    float nx = x + i * frequency;
                    float ny = y + j * frequency;
                    float nz = z + k * frequency;
                    noise[i + j * sizeX + k * sizeX * sizeY] = GetNoise(nx, ny, nz);
                }
            }
        }
        return noise;
    }

    void FreeNoiseSet(float* noise) {
        delete[] noise;
    }

private:
    float GetNoise(float x, float y, float z) {
        switch(noiseType) {
            case Value:
                return ValueNoise(x, y, z);
            case Perlin:
                return PerlinNoise(x, y, z);
            case Simplex:
                return SimplexNoise(x, y, z);
            case WhiteNoise:
                return WhiteNoise(x, y, z);
            default:
                return 0.0f;
        }
    }

    float ValueNoise(float x, float y, float z) {
        int X = (int)std::floor(x) & 255;
        int Y = (int)std::floor(y) & 255;
        int Z = (int)std::floor(z) & 255;
        x -= std::floor(x);
        y -= std::floor(y);
        z -= std::floor(z);
        float u = Fade(x);
        float v = Fade(y);
        float w = Fade(z);
        
        int A = perm[X] + Y;
        int AA = perm[A] + Z;
        int B = perm[X + 1] + Y;
        int BA = perm[B] + Z;
        
        return Lerp(w, Lerp(v, Lerp(u, Grad(perm[AA], x, y, z),
                                      Grad(perm[BA], x-1, y, z)),
                              Lerp(u, Grad(perm[AA+1], x, y-1, z),
                                      Grad(perm[BA+1], x-1, y-1, z))),
                      Lerp(v, Lerp(u, Grad(perm[AA+256], x, y, z-1),
                                      Grad(perm[BA+256], x-1, y, z-1)),
                              Lerp(u, Grad(perm[AA+257], x, y-1, z-1),
                                      Grad(perm[BA+257], x-1, y-1, z-1))));
    }

    float PerlinNoise(float x, float y, float z) {
        return ValueNoise(x, y, z);
    }

    float SimplexNoise(float x, float y, float z) {
        return ValueNoise(x, y, z);
    }

    float WhiteNoise(float x, float y, float z) {
        std::mt19937 gen(seed + (int)x + (int)y * 256 + (int)z * 65536);
        std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
        return dist(gen);
    }

    float Fade(float t) { return t * t * t * (t * (t * 6 - 15) + 10); }
    float Lerp(float t, float a, float b) { return a + t * (b - a); }
    float Grad(int hash, float x, float y, float z) {
        int h = hash & 15;
        float u = h < 8 ? x : y;
        float v = h < 4 ? y : h == 12 || h == 14 ? x : z;
        return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
    }

    int seed;
    float frequency;
    NoiseType noiseType;
    int perm[256];
}; 