#pragma once

namespace r82labs::learn_with_physics {

enum class AngleUnit { radians, degrees };
enum class LaunchDirection { right, left };

enum class MassUnit { kilograms, grams, pounds };

struct Mass {
    float value;
    MassUnit unit;

    static Mass from_kilograms(float kilograms) {
        return Mass{kilograms, MassUnit::kilograms};
    }

    static Mass from_grams(float grams) {
        return Mass{grams, MassUnit::grams};
    }

    static Mass from_pounds(float pounds) {
        return Mass{pounds, MassUnit::pounds};
    }

    [[nodiscard]] float as_kilograms() const {
        switch (unit) {
            case MassUnit::kilograms:
                return value;
            case MassUnit::grams:
                return value / 1000.0f;
            case MassUnit::pounds:
                return value * 0.45359237f;
        }
        return value;
    }
};

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
