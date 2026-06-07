#pragma once

namespace r82labs::learn_with_physics {

enum class AngleUnit { radians, degrees };
enum class LaunchDirection { right, left };

struct Point {
    float x;
    float y;
};

struct PointInTime {
    Point position;
    float time;
};

struct TimeRequest {
    float time = 0.0f;
};

}  // namespace r82labs::learn_with_physics
