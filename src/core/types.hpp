#pragma once

#include <numbers>
#include <stdexcept>

namespace r82labs::learn_with_physics {

enum class LaunchDirection { right, left };

struct Mass {
    double kilograms;

    explicit Mass(double kilograms) : kilograms(kilograms) {
        if (kilograms <= 0.0) {
            throw std::invalid_argument("mass must be positive");
        }
    }

    static Mass from_kilograms(double kilograms) { return Mass(kilograms); }

    static Mass from_grams(double grams) { return Mass(grams / 1000.0); }

    static Mass from_pounds(double pounds) { return Mass(pounds * 0.45359237); }

    [[nodiscard]] double get_kilograms() const { return kilograms; }
};

struct Length {
    double meters;

    explicit Length(double meters) : meters(meters) {
        if (meters <= 0.0) {
            throw std::invalid_argument("length must be positive");
        }
    }

    static Length from_meters(double meters) { return Length(meters); }

    static Length from_centimeters(double centimeters) { return Length{centimeters / 100.0}; }

    static Length from_millimeters(double millimeters) { return Length{millimeters / 1000.0}; }

    static Length from_inches(double inches) { return Length{inches * 0.0254}; }

    static Length from_feet(double feet) { return Length{feet * 0.3048}; }

    [[nodiscard]] double get_meters() const { return meters; }
};

struct Time {
    double seconds;

    explicit Time(double seconds) : seconds(seconds) {
        if (seconds < 0.0) {
            throw std::invalid_argument("time cannot be negative");
        }
    }

    static Time from_seconds(double seconds) { return Time(seconds); }

    static Time from_milliseconds(double milliseconds) { return Time(milliseconds / 1000.0); }

    static Time from_minutes(double minutes) { return Time(minutes * 60.0); }

    static Time from_hours(double hours) { return Time(hours * 3600.0); }

    [[nodiscard]] double get_seconds() const { return seconds; }
};

struct Angle {
    double radians;

    explicit Angle(double radians) : radians(radians) {}

    static Angle from_degrees(double degrees) {
        if (degrees < -1e-4 || degrees > 90.0 + 1e-4) {
            throw std::out_of_range("angle must be between 0 and 90 degrees");
        }
        return Angle{degrees * (std::numbers::pi / 180.0)};
    }

    [[nodiscard]] double get_radians() const { return radians; }
};

struct LaunchOrientation {
    Angle angle;
    LaunchDirection direction;

    static LaunchOrientation toward_right(Angle a) { return {a, LaunchDirection::right}; }
    static LaunchOrientation toward_left(Angle a) { return {a, LaunchDirection::left}; }

    [[nodiscard]] double get_radians() const {
        if (direction == LaunchDirection::left) return std::numbers::pi - angle.get_radians();
        return angle.get_radians();
    }
};

struct Acceleration {
    double meters_per_second_squared;

    static Acceleration from_meters_per_second_squared(double mpss) { return Acceleration{mpss}; }

    [[nodiscard]] double get_meters_per_second_squared() const { return meters_per_second_squared; }
};

struct Stiffness {
    double newtons_per_meter;

    static Stiffness from_newtons_per_meter(double stiffness) { return Stiffness{stiffness}; }

    static Stiffness from_kilonewtons_per_meter(double stiffness) {
        return Stiffness{stiffness * 1000.0};
    }

    static Stiffness from_pounds_force_per_inch(double stiffness) {
        return Stiffness{stiffness * 175.126771};
    }

    static Stiffness from_pounds_force_per_foot(double stiffness) {
        return Stiffness{stiffness * 14.593903};
    }

    [[nodiscard]] double get_newtons_per_meter() const { return newtons_per_meter; }
};

struct Efficiency {
    double ratio;

    static Efficiency from_ratio(double ratio) {
        if (ratio < 0.0 || ratio > 1.0) {
            throw std::invalid_argument("efficiency ratio must be between 0 and 1");
        }
        return Efficiency{ratio};
    }

    [[nodiscard]] double get_ratio() const { return ratio; }
};

struct Point {
    double x;
    double y;
};

struct PointInTime {
    Point position;
    Time time;
};

struct TimeRequest {
    Time time = Time::from_seconds(0.0);
};

}  // namespace r82labs::learn_with_physics
