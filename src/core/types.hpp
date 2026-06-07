#pragma once

#include <stdexcept>

namespace r82labs::learn_with_physics {

enum class AngleUnit { radians, degrees };
enum class LaunchDirection { right, left };

enum class MassUnit { kilograms, grams, pounds };
enum class LengthUnit { meters, centimeters, millimeters, inches, feet };
enum class TimeUnit { seconds, milliseconds, minutes, hours };

struct Mass {
    float value;
    MassUnit unit;

    explicit Mass(float mass, MassUnit unit) : value(mass), unit(unit) {
        if (mass <= 0.0f) {
            throw std::invalid_argument("mass must be positive");
        }
    }

    static Mass from_kilograms(float kilograms) { return Mass(kilograms, MassUnit::kilograms); }

    static Mass from_grams(float grams) { return Mass(grams, MassUnit::grams); }

    static Mass from_pounds(float pounds) { return Mass(pounds, MassUnit::pounds); }

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

    explicit Length(float length, LengthUnit unit) : value(length), unit(unit) {
        if (length <= 0.0f) {
            throw std::invalid_argument("length must be positive");
        }
    }

    static Length from_meters(float meters) { return Length(meters, LengthUnit::meters); }

    static Length from_centimeters(float centimeters) {
        return Length{centimeters, LengthUnit::centimeters};
    }

    static Length from_millimeters(float millimeters) {
        return Length{millimeters, LengthUnit::millimeters};
    }

    static Length from_inches(float inches) { return Length{inches, LengthUnit::inches}; }

    static Length from_feet(float feet) { return Length{feet, LengthUnit::feet}; }

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

    explicit Time(float t, TimeUnit unit) : value(t), unit(unit) {
        if (t < 0.0f) {
            throw std::invalid_argument("time cannot be negative");
        }
    }

    static Time from_seconds(float seconds) { return Time(seconds, TimeUnit::seconds); }

    static Time from_milliseconds(float milliseconds) {
        return Time(milliseconds, TimeUnit::milliseconds);
    }

    static Time from_minutes(float minutes) { return Time(minutes, TimeUnit::minutes); }

    static Time from_hours(float hours) { return Time(hours, TimeUnit::hours); }

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

struct Angle {
    float value;
    AngleUnit unit;

    static Angle from_radians(float radians) {
        if (radians < -1e-6f || radians > 1.57079632679f + 1e-6f) {
            throw std::out_of_range("angle must be between 0 and 90 degrees");
        }
        return Angle{radians, AngleUnit::radians};
    }

    static Angle from_degrees(float degrees) {
        if (degrees < -1e-4f || degrees > 90.0f + 1e-4f) {
            throw std::out_of_range("angle must be between 0 and 90 degrees");
        }
        return Angle{degrees, AngleUnit::degrees};
    }

    [[nodiscard]] float as_radians() const {
        switch (unit) {
            case AngleUnit::radians:
                return value;
            case AngleUnit::degrees:
                return value * (3.14159265358979323846f / 180.0f);
        }
        return value;
    }

    [[nodiscard]] float as_degrees() const {
        switch (unit) {
            case AngleUnit::radians:
                return value * (180.0f / 3.14159265358979323846f);
            case AngleUnit::degrees:
                return value;
        }
        return value;
    }
};

struct LaunchOrientation {
    Angle angle;
    LaunchDirection direction;

    static LaunchOrientation toward_right(Angle a) { return {a, LaunchDirection::right}; }
    static LaunchOrientation toward_left(Angle a) { return {a, LaunchDirection::left}; }

    [[nodiscard]] float as_radians() const {
        switch (unit) {
            case AngleUnit::radians:
                return value;
            case AngleUnit::degrees:
                return value * (3.14159265358979323846f / 180.0f);
        }
        return value;
    }

    [[nodiscard]] float as_degrees() const {
        switch (unit) {
            case AngleUnit::radians:
                return value * (180.0f / 3.14159265358979323846f);
            case AngleUnit::degrees:
                return value;
        }
        return value;
    }
};

enum class AccelerationUnit { meters_per_second_squared };

struct Acceleration {
    float value;
    AccelerationUnit unit;

    static Acceleration from_meters_per_second_squared(float mpss) {
        return Acceleration{mpss, AccelerationUnit::meters_per_second_squared};
    }

    [[nodiscard]] float as_meters_per_second_squared() const {
        switch (unit) {
            case AccelerationUnit::meters_per_second_squared:
                return value;
        }
        return value;
    }
};

struct Efficiency {
    float value;

    static Efficiency from_ratio(float ratio) {
        if (ratio < 0.0f || ratio > 1.0f) {
            throw std::invalid_argument("efficiency ratio must be between 0 and 1");
        }
        return Efficiency{ratio};
    }

    [[nodiscard]] float as_ratio() const { return value; }
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
