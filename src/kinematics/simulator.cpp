#include "simulator.hpp"

#include <cmath>
#include <numbers>

namespace r82labs::learn_with_physics {

Simulator::Simulator(const SimulatorConfig& config)
    : gravity(config.g.as_meters_per_second_squared()),
      projectile(config.projectile),
      x_velocity_factor(0.0f),
      y_velocity_factor(0.0f),
      half_gravity_factor(0.5f * config.g.as_meters_per_second_squared()) {
    const float draw_length_m = config.draw_length.as_meters();
    const float mass_kg = projectile.get_mass().as_kilograms();
    const float efficiency_ratio = config.slingshot.get_efficiency().as_ratio();
    const float stiffness_npm = config.slingshot.get_stiffness().as_newtons_per_meter();
    const float v0 = draw_length_m * std::sqrt((efficiency_ratio * stiffness_npm) / mass_kg);

    const float orientation_radians = config.orientation.as_radians();

    x_velocity_factor = v0 * std::cos(orientation_radians);
    y_velocity_factor = v0 * std::sin(orientation_radians);
}

Point Simulator::get_position_at_time(const TimeRequest& request) const {
    const float time_seconds = request.time.as_seconds();
    return {x_velocity_factor * time_seconds,
            (y_velocity_factor - half_gravity_factor * time_seconds) * time_seconds};
}

PointInTime Simulator::get_apex_point_in_time() const {
    const float apex_time = y_velocity_factor / gravity;
    return PointInTime{get_position_at_time({.time = Time::from_seconds(apex_time)}),
                       Time::from_seconds(apex_time)};
}

Time Simulator::get_time_at_ground() const {
    const float ground_seconds = (2.0f * y_velocity_factor) / gravity;
    return Time::from_seconds(ground_seconds);
}

}  // namespace r82labs::learn_with_physics
