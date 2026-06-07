#include "simulator.hpp"

#include <cmath>
#include <numbers>

namespace r82labs::learn_with_physics {

Simulator::Simulator(const SimulatorConfig& config)
    : gravity(config.g.get_meters_per_second_squared()),
      projectile(config.projectile),
      x_velocity_factor(0.0),
      y_velocity_factor(0.0),
      half_gravity_factor(0.5 * config.g.get_meters_per_second_squared()) {
    const double draw_length_m = config.draw_length.get_meters();
    const double mass_kg = projectile.get_mass().get_kilograms();
    const double efficiency_ratio = config.slingshot.get_efficiency().get_ratio();
    const double stiffness_npm = config.slingshot.get_stiffness().get_newtons_per_meter();
    const double v0 = draw_length_m * std::sqrt((efficiency_ratio * stiffness_npm) / mass_kg);

    const double orientation_radians = config.orientation.get_radians();

    x_velocity_factor = v0 * std::cos(orientation_radians);
    y_velocity_factor = v0 * std::sin(orientation_radians);
}

Point Simulator::get_position_at_time(const TimeRequest& request) const {
    const double time_seconds = request.time.get_seconds();
    return {x_velocity_factor * time_seconds,
            (y_velocity_factor - half_gravity_factor * time_seconds) * time_seconds};
}

PointInTime Simulator::get_apex_point_in_time() const {
    const double apex_time = y_velocity_factor / gravity;
    return PointInTime{get_position_at_time({.time = Time::from_seconds(apex_time)}),
                       Time::from_seconds(apex_time)};
}

Time Simulator::get_time_at_ground() const {
    const double ground_seconds = (2.0 * y_velocity_factor) / gravity;
    return Time::from_seconds(ground_seconds);
}

}  // namespace r82labs::learn_with_physics
