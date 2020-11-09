#pragma once


void PerlinNoise2D(int nWidth, int nHeight, float *fSeed, int nOctaves, float fBias, float *fOutput);
void PerlinNoise1D(int nCount, float *fSeed, int nOctaves, float fBias, float *fOutput);