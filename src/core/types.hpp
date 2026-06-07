#pragma once

namespace r82labs::learn_with_physics {

enum class AngleUnit { radians, degrees };
enum class LaunchDirection { right, left };

enum class MassUnit { kilograms, grams, pounds };
enum class LengthUnit { meters, centimeters, millimeters, inches, feet };
enum class TimeUnit { seconds, milliseconds, minutes, hours };

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

struct Length {
    float value;
    LengthUnit unit;

    static Length from_meters(float meters) {
        return Length{meters, LengthUnit::meters};
    }

    static Length from_centimeters(float centimeters) {
        return Length{centimeters, LengthUnit::centimeters};
    }

    static Length from_millimeters(float millimeters) {
        return Length{millimeters, LengthUnit::millimeters};
    }

    static Length from_inches(float inches) {
        return Length{inches, LengthUnit::inches};
    }

    static Length from_feet(float feet) {
        return Length{feet, LengthUnit::feet};
    }

    [[nodiscard]] float as_meters() const {
        switch (unit) {
            case LengthUnit::meters:
                return value;
            case LengthUnit::centimeters:
                return value / 100.0f;
            case LengthUnit::millimeters:
                return value / 1000.0f;
            case LengthUnit::inches:
                return value * 0.0254f;
            case LengthUnit::feet:
                return value * 0.3048f;
        }
        return value;
    }
};

struct Time {
    float value;
    TimeUnit unit;

    static Time from_seconds(float seconds) {
        return Time{seconds, TimeUnit::seconds};
    }

    static Time from_milliseconds(float milliseconds) {
        return Time{milliseconds, TimeUnit::milliseconds};
    }

    static Time from_minutes(float minutes) {
        return Time{minutes, TimeUnit::minutes};
    }

    static Time from_hours(float hours) {
        return Time{hours, TimeUnit::hours};
    }

    [[nodiscard]] float as_seconds() const {
        switch (unit) {
            case TimeUnit::seconds:
                return value;
            case TimeUnit::milliseconds:
                return value / 1000.0f;
            case TimeUnit::minutes:
                return value * 60.0f;
            case TimeUnit::hours:
                return value * 3600.0f;
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
    Time time;
};

struct TimeRequest {
    Time time = Time::from_seconds(0.0f);
};

}  // namespace r82labs::learn_with_physics
