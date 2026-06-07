#include "simulator.hpp"

#include <cmath>
#include <limits>
#include <numbers>

namespace r82labs::learn_with_physics {

namespace {
float to_radians(const float angle, const AngleUnit unit) {
    if (unit == AngleUnit::radians) {
        return angle;
    }
    return angle * (std::numbers::pi_v<float> / 180.0f);
}
}  // namespace

Simulator::Simulator(const SimulatorConfig& config)
    : gravity(config.g),
      projectile(config.projectile),
      x_velocity_factor(0.0f),
      y_velocity_factor(0.0f),
      half_gravity_factor(0.5f * config.g) {
    const float angle_radians = to_radians(config.angle, config.unit);

    constexpr float epsilon = std::numeric_limits<float>::epsilon();
    if (angle_radians < -epsilon || angle_radians > (std::numbers::pi_v<float> / 2.0f + epsilon)) {
        throw std::out_of_range("Launch angle must be between 0 and 90 degrees.");
    }

    const float mass_kg = projectile.get_mass().as_kilograms();
    const float v0 =
        config.draw_length *
        std::sqrt((config.slingshot.get_efficiency() * config.slingshot.get_stiffness()) /
                  mass_kg);
    const float dir_multiplier = (config.direction == LaunchDirection::right) ? 1.0f : -1.0f;

    x_velocity_factor = v0 * std::cos(angle_radians) * dir_multiplier;
    y_velocity_factor = v0 * std::sin(angle_radians);
}

Point Simulator::get_position_at_time(const TimeRequest& request) const {
    return {x_velocity_factor * request.time,
            (y_velocity_factor - half_gravity_factor * request.time) * request.time};
}

PointInTime Simulator::get_apex_point_in_time() const {
    const float apex_time = y_velocity_factor / gravity;
    return PointInTime{get_position_at_time({.time = apex_time}), apex_time};
}

float Simulator::get_time_at_ground() const {
    return (2.0f * y_velocity_factor) / gravity;
}

}  // namespace r82labs::learn_with_physics
