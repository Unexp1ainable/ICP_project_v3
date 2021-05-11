#pragma once
/**
 * @file macros.h
 * @author Leopold Nemček
 * @author Samuel Repka
 * @date 11/05/2021
 * @brief File containing macros used throughout the program
 */


constexpr double PI = 3.141592653589793238463;
template<typename T> constexpr auto TO_DEGREES(T x) { return x * (180.0 / PI); }
template<typename T> constexpr auto TO_RADIANS(T x) { return x * PI / 180.0; }

constexpr int DETECTOR_SIZE = 2;
constexpr int SAMPLE_SIZE = 10;
constexpr int LENS_SIZE = 10;
constexpr int SOURCE_SIZE = 1;


#define MIN_DISTANCE 0.11
#define EDGE_DISTANCE 50
constexpr double INIT_RAY_RADIUS = 1.;
constexpr double INIT_RAY_COUNT = 10;
