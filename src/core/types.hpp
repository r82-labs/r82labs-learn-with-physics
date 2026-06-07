#pragma once

#include <numbers>
#include <stdexcept>

namespace r82labs::learn_with_physics {

enum class LaunchDirection { right, left };

enum class MassUnit { kilograms, grams, pounds };
enum class LengthUnit { meters, centimeters, millimeters, inches, feet };
enum class TimeUnit { seconds, milliseconds, minutes, hours };

enum class StiffnessUnit {
    newtons_per_meter,
    kilonewtons_per_meter,
    pounds_force_per_inch,
    pounds_force_per_foot
};

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

    static Angle from_degrees(float degrees) {
        if (degrees < -1e-4f || degrees > 90.0f + 1e-4f) {
            throw std::out_of_range("angle must be between 0 and 90 degrees");
        }
        return Angle{degrees};
    }

    [[nodiscard]] float as_radians() const { return value * (std::numbers::pi / 180.0f); }

    [[nodiscard]] float as_degrees() const { return value; }
};

struct LaunchOrientation {
    Angle angle;
    LaunchDirection direction;

    static LaunchOrientation toward_right(Angle a) { return {a, LaunchDirection::right}; }
    static LaunchOrientation toward_left(Angle a) { return {a, LaunchDirection::left}; }

    [[nodiscard]] float as_radians() const {
        if (direction == LaunchDirection::left) return std::numbers::pi - angle.as_radians();
        return angle.as_radians();
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

struct Stiffness {
    float value;
    StiffnessUnit unit;

    static Stiffness from_newtons_per_meter(float stiffness) {
        return Stiffness{stiffness, StiffnessUnit::newtons_per_meter};
    }

    static Stiffness from_kilonewtons_per_meter(float stiffness) {
        return Stiffness{stiffness, StiffnessUnit::kilonewtons_per_meter};
    }

    static Stiffness from_pounds_force_per_inch(float stiffness) {
        return Stiffness{stiffness, StiffnessUnit::pounds_force_per_inch};
    }

    static Stiffness from_pounds_force_per_foot(float stiffness) {
        return Stiffness{stiffness, StiffnessUnit::pounds_force_per_foot};
    }

    [[nodiscard]] float as_newtons_per_meter() const {
        switch (unit) {
            case StiffnessUnit::newtons_per_meter:
                return value;
            case StiffnessUnit::kilonewtons_per_meter:
                return value * 1000.0f;
            case StiffnessUnit::pounds_force_per_inch:
                return value * 175.126771f;
            case StiffnessUnit::pounds_force_per_foot:
                return value * 14.593903f;
        }
        return value;
    }

    [[nodiscard]] float as_kilonewtons_per_meter() const {
        return as_newtons_per_meter() / 1000.0f;
    }

    [[nodiscard]] float as_pounds_force_per_inch() const {
        return as_newtons_per_meter() / 175.126771f;
    }

    [[nodiscard]] float as_pounds_force_per_foot() const {
        return as_newtons_per_meter() / 14.593903f;
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
