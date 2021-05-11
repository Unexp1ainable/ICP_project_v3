#pragma once
constexpr double PI = 3.141592653589793238463;
template<typename T> constexpr auto TO_DEGREES(T x) { return x * (180.0 / PI); }
template<typename T> constexpr auto TO_RADIANS(T x) { return x * PI / 180.0; }

constexpr int DETECTOR_SIZE = 2;
constexpr int SAMPLE_SIZE = 10;
constexpr int LENS_SIZE = 10;
constexpr int SOURCE_SIZE = 1;

constexpr double INIT_RAY_RADIUS = 1.;
constexpr double INIT_RAY_COUNT = 10;
